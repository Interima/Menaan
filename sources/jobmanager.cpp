#include <QFileInfo>
#include <QDebug>
#include <QThread>

#include "jobmanager.h"
#include "menaan.h"

const int JobManager::DEFAULT_PRIORITY;
const int JobManager::MAX_PRIORITY;
const int JobManager::MIN_PRIORITY;


JobManager::JobManager(JobInfoModel *jim, ConfigData *cfg, QObject *parent):
    QObject(parent),jobInfoModelPointer(jim), config(cfg), maxThreadCount(1), curTicket(0)
{
    // check multi thread enabled
    if (config->getMultiThread())
    {
        // determine thread count
        maxThreadCount =  QThread::idealThreadCount();
        qDebug()<<"[JobManager say:] Multithread on and thread count: "<<maxThreadCount;
    }
}

quint32 JobManager::generateTicket()
{
    return curTicket++;
}

void JobManager::createJob(QString in, QString out, QString key,
                           QString args, JobTypes::JobType type, PluginInterface * pi)
{

    qDebug()<<"[JobManager say:] Start job creating";

    Worker* newWorker = new Worker;

    // get unique ticket
    quint32 ticket = generateTicket();

    qDebug()<<"[JobManager say:] Job ticket: "<<ticket;


    // check Ext option and add if need file ext
    if (config->getExt())
    {
        QString ext;
        QString _out;
        QFileInfo fi(out);

        switch(type)
        {
            case JobTypes::ECB_ENC : ext = "/ecb_enc_"; break;
            case JobTypes::ECB_DEC : ext = "/ecb_dec_"; break;
            case JobTypes::CBC_ENC : ext = "/cbc_enc_"; break;
            case JobTypes::CBC_DEC : ext = "/cbc_dec_"; break;
        }

        _out = fi.path()+ext+fi.fileName();

        if (in==_out) _out = fi.path()+ext+"_"+fi.fileName();

        out = _out;
    }

    // check Use Rewrite option
    if ((QFileInfo(out).exists())&&(!config->getRewrite()))
        out = Menaan::generateUnique(out);



    // create job
    JobInfo newJobInfo(ticket,
                       in,
                       out,
                       pi->name(),
                       JobStates::Stopped,
                       0,
                       DEFAULT_PRIORITY);

    qDebug()<<"[JobManager say:] JobInfo created. ["<<ticket<<"]";

    // init worker
    newWorker->init(ticket,
                    in,
                    out,
                    key,
                    args,
                    pi,
                    type);


    qDebug()<<"[JobManager say:] Worker created. ["<<ticket<<"]";

    // connect signals
    connect(newWorker, SIGNAL(error(quint32,Worker::WorkerErrors)),this,SLOT(errorHandler(quint32,Worker::WorkerErrors)));
    connect(newWorker, SIGNAL(stateChanged(quint32,JobStates::JobState)),this,SLOT(stateHandler(quint32,JobStates::JobState)));
    connect(newWorker, SIGNAL(progressChange(quint32,quint8)),this, SLOT(progressHandler(quint32,quint8)));

    // insert job info to model
    jobInfoModelPointer->insertJob(newJobInfo);

    // append worker to worker list
    workerList.append(newWorker);

    tryStartWorker();

    qDebug()<<"[JobManager say:] End job creating. ["<<ticket<<"]";
}


void JobManager::tryStartWorker()
{
    qDebug()<<"[JobManager say:] Try to start worker";

    // if max thread already was run - fail
    if (activeWorkerHash.count()>=maxThreadCount) return;

    qDebug()<<"[JobManager say:] Finding job with max priority";

    quint32 jobsCount = jobInfoModelPointer->rowCount(QModelIndex());
    quint32 ticket = 0;
    ActiveWorkerInfo tempAWI;
    int priority = MIN_PRIORITY-1;
    bool finded = false;

    for(quint32 i=0; i<jobsCount; i++)
    {
        QModelIndex mInd = jobInfoModelPointer->index(i);

        if ((jobInfoModelPointer->data(mInd,JobInfoModel::StateRole)
           .value<quint8>() == JobStates::Stopped) &&

           (jobInfoModelPointer->data
            (mInd,JobInfoModel::PriorityRole).value<int>() > priority))
        {
            qDebug()<<"[JobManager say:] Stopped job was found";

            ticket = jobInfoModelPointer->data(mInd,JobInfoModel::TicketRole).value<quint32>();

            tempAWI.setTicket(ticket);
            tempAWI.setSource(jobInfoModelPointer->data(mInd,JobInfoModel::SourceRole)
                                                      .value<QString>());
            tempAWI.setDestination(jobInfoModelPointer->data(mInd,JobInfoModel::DestinationRole)
                                                      .value<QString>());
            int k;
            // check conflict with other running jobs
            for (k=0; k<activeWorkerHash.count(); k++)
                if (activeWorkerHash.at(k).isConflict(tempAWI)) break;

            // if we have conflict, skip this job
            if ((k!= activeWorkerHash.count())&&(activeWorkerHash.count()!=0)) continue;

            qDebug()<<"[JobManager say:] Stopped job hasn't conflict. ["<<ticket<<"]";

            priority = jobInfoModelPointer->data(mInd,JobInfoModel::PriorityRole).value<int>();

            finded = true;
            // if it max priority return immediately
            if (priority==JobManager::MAX_PRIORITY) break;

        }
    }

    if (finded)
    {
        // find worker with _ticket and run it
        for (int j=0; j<workerList.count(); j++)
            if (workerList.at(j)->isTicket(ticket))
            {
                // append new job info ro hash
                activeWorkerHash.append(tempAWI);

                // start worker
                workerList.at(j)->start();

                return;
            }
    }

    // if we there so we can't find any job to start...
    qDebug()<<"[JobManager say:] There is not avaible jobs to start";
}


void JobManager::deleteAllJobs()
{
    qDebug()<<"[JobManager say:] Deleting all jobs";

    for(int i=0; i<workerList.count();i++)
    {
        workerList.value(i)->stop();
        workerList.value(i)->quit();
    }

    qDebug()<<"[JobManager say:] Time to die";
}

void JobManager::deleteJob(int index)
{
    // get model index for job and its ticket
    QModelIndex mInd = jobInfoModelPointer->index(index);
    quint16 ticket = jobInfoModelPointer->data(mInd,JobInfoModel::TicketRole).toUInt();

    // find and delete worker
    for(int i=0; i<workerList.count();i++)
        if (workerList.at(i)->isTicket(ticket))
        {
            qDebug()<<"[JobManager say:] Send stop signal to worker. ["<<ticket<<"]";
            workerList.value(i)->stop();

            qDebug()<<"[JobManager say:] Job deleting start. ["<<ticket<<"]";
            // break worker event loop
            workerList.value(i)->quit();


            // WARNING !!!
            // WAIT BEFORE THREAD RECEIVE 'QUIT'
            workerList.value(i)->wait();
            // EXPLICIT DESTRUCTOR CALL
            workerList.value(i)->~Worker();

            // delete it
            workerList.removeAt(i);

            qDebug()<<"[JobManager say:] Some job was deleted, try to start new";

        }

    // remove job
    jobInfoModelPointer->removeJob(index);

    // start new (if removed jobs was not runned, has no effect)
    for (int i=0; i<activeWorkerHash.count(); i++)
        if (activeWorkerHash.at(i).getTicket()==ticket)
        {
            activeWorkerHash.removeAt(i);
            tryStartWorker();
        }

}

/*************************************************************/

void JobManager::controlJob(int index, JobManager::JobCommands command)
{
    switch (command)
    {
        case JobManager::Freeze: this->jobFreeze(index); break;
        case JobManager::UnFreeze: this->jobUnfreeze(index); break;
        case JobManager::Up: this->jobUp(index); break;
        case JobManager::Down: this->jobDown(index); break;
        default:;
    }
}

void JobManager::jobFreeze(int index)
{
    QModelIndex mInd = jobInfoModelPointer->index(index);

    jobInfoModelPointer->setData(mInd,QVariant::fromValue(JobStates::Frozen),
                                 JobInfoModel::StateRole);
}

void JobManager::jobUnfreeze(int index)
{
    QModelIndex mInd = jobInfoModelPointer->index(index);

    jobInfoModelPointer->setData(mInd,QVariant::fromValue(JobStates::Stopped),
                                 JobInfoModel::StateRole);

    tryStartWorker();

}

void JobManager::jobUp(int index)
{
    QModelIndex mInd = jobInfoModelPointer->index(index);

    int curPriority = jobInfoModelPointer->data(mInd,JobInfoModel::PriorityRole).value<int>();

    ++curPriority;

    if (curPriority!=JobManager::MAX_PRIORITY)
       jobInfoModelPointer->setData(mInd,QVariant::fromValue(curPriority),
                                     JobInfoModel::PriorityRole);


}

void JobManager::jobDown(int index)
{
    QModelIndex mInd = jobInfoModelPointer->index(index);

    int curPriority = jobInfoModelPointer->data(mInd,JobInfoModel::PriorityRole).value<int>();

    --curPriority;

    if (curPriority!=JobManager::MIN_PRIORITY)
        jobInfoModelPointer->setData(mInd,QVariant::fromValue(curPriority),
                                     JobInfoModel::PriorityRole);
}

/*************************************************************/

void JobManager::progressHandler(quint32 ticket, quint8 progress)
{
    // get model index by ticket
    QModelIndex mInd = jobInfoModelPointer->ticketToIndex(ticket);

    // set progress for job
    if (mInd.isValid())
    jobInfoModelPointer->setData(mInd,QVariant::fromValue(progress),JobInfoModel::ProgressRole);
}

void JobManager::stateHandler(quint32 ticket, JobStates::JobState state)
{
    // get model index by ticket
    QModelIndex mInd = jobInfoModelPointer->ticketToIndex(ticket);

    // set state for job
    if (mInd.isValid())
    jobInfoModelPointer->setData(mInd,QVariant::fromValue(state),JobInfoModel::StateRole);

    // if job finished we need delete it from hash
    // and try to start new
    if ((state == JobStates::Finished) && (!config->getAutoFinishedDelete()))
    {
        qDebug()<<"[JobManager say:] Some job was finished, try to start new";

        for (int i=0; i<activeWorkerHash.count(); i++)
            if (activeWorkerHash.at(i).getTicket()==ticket)
            {
                activeWorkerHash.removeAt(i);
                tryStartWorker();
                return;
            }

        qDebug()<<"[JobManager say:] ############### Problem #################";
    }
    // if finished jobs auto delete enabled
    else if ((state == JobStates::Finished) && (config->getAutoFinishedDelete())) deleteJob(mInd.row());

}

void JobManager::errorHandler(quint32 ticket, Worker::WorkerErrors err)
{
    // get model index by ticket
    QModelIndex mInd = jobInfoModelPointer->ticketToIndex(ticket);

    // set state for job
    if (mInd.isValid())
    jobInfoModelPointer->setData(mInd,QVariant::fromValue(JobStates::Error),JobInfoModel::StateRole);

    // raise error to interface
    emit raiseError(ticket,err);


    qDebug()<<"[JobManager say:] Some job has error, try to start new";

    for (int i=0; i<activeWorkerHash.count(); i++)
        if (activeWorkerHash.at(i).getTicket()==ticket)
        {
            activeWorkerHash.removeAt(i);
            tryStartWorker();
            return;
        }

    qDebug()<<"[JobManager say:] ############### Problem #################";
}
