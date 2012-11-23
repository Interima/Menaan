#ifndef JOBMANAGER_H
#define JOBMANAGER_H

/*!
    @file jobinfomodel.h
    Contains JobManager class description.
    includes files: QObject.h, jobinfomodel.h, worker.h
                    configdata.h, activeworkerinfo.h, jobtypes.h

    @author Interima.ix2
    @author Interima.Inmay
*/

#include <QObject>

#include "jobinfomodel.h"
#include "worker.h"
#include "configdata.h"
#include "activeworkerinfo.h"
#include "jobtypes.h"

//! JobManager class is manager of all jobs
/*!
    This is class using as model for job's
*/
class JobManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(JobCommands)

public:

    //! JobCommands enum
    /*!
        The enum describes commands which can apply to jobs
    */
    enum JobCommands
    {
        Freeze = 1, /*!< value for freeze command */
        UnFreeze,   /*!< value for unfreeze command */
        Up,         /*!< value for up command */
        Down,       /*!< value for down command */
        ToTop,      /*!< value for totop command */
        ToBottom    /*!< value for tobottom command */
    };

    //! Static const value holds job's default priority
    //! This value sets for all new created jobs
    static const int DEFAULT_PRIORITY = 0;

    //! Static const value holds job's maximum priority value
    static const int MAX_PRIORITY = 10;

    //! Static const value holds job's minimum priority value
    static const int MIN_PRIORITY = -10;

    //! Constructor for JobInfoModel class
    /*!
        \param dt - non null pointer to model data
        \param parent - parent object
    */
    explicit JobManager(JobInfoModel* jim, ConfigData * cfg, QObject *parent = 0);


private:

    //! This property holds pointer to JobInfoModel object
    JobInfoModel* jobInfoModelPointer;

    /*! [Note] Qt can't copy QObject instances so we nees use pointers
        This property holds QList of all Worker objects
        Every worker that will be created, added to this list
    */
    QList<Worker*> workerList;

    /*! This property holds QList of ActiveWorkerInfo
        Only active jobs can be added to this list
        and removes from there after lost it's active state
        active - means Running state for jobs
        So this property holds info about jobs that currently runned.
    */
    QList<ActiveWorkerInfo> activeWorkerHash;

    //! This property holds pointer to ConfigData object
    //! that contains application settings
    ConfigData * config;

    //! This property holds maximum thread count for this platform
    qint8 maxThreadCount;

    //! This property holds ticket generator current value
    //! All jobs must have unique ticket
    //! \sa generateTicket()
    quint32 curTicket;

    //! Try to start avaible stopped job's worker
    void tryStartWorker();

    //! Generates ticket and return it
    quint32 generateTicket();

    //! Freezes job
    /*!
        Job must be in Stopped state
        \param index - index of job in model
        \sa jobUnfreeze();
    */
    void jobFreeze(int index);


    //! UnFreezes job
    /*!
        Job must be in Frozen state
        \param index - index of job in model
        \sa jobFreeze();
    */
    void jobUnfreeze(int index);

    //! Increase job's priority
    /*!
        Job must be in Stopped state
        \param index - index of job in model
        \sa jobDown()
    */
    void jobUp(int index);

    //! Decrease job's priority
    /*!
        Job must be in Stopped state
        \param index - index of job in model
        \sa jobUp()
    */
    void jobDown(int index);

signals:

    //! [Signal] Indicated about error in job
    /*!
        \param ticket - ticket of job which has an error
        \param errno - error type
    */
    void raiseError(quint32 ticket, Worker::WorkerErrors errno);
    
public slots:

    //! [Slot] Create a job and it's worker
    /*!
        \param in   - path to source data
        \param out  - path to destination data
        \param key  - user keyword
        \param args - special agrs to algorithm
        \param type - type of job
        \param pi   - pointer to plugin
        \sa deleteJob(), deleteAllJobs()
    */
    void createJob(QString in, QString out, QString key,
                   QString args, JobTypes::JobType type, PluginInterface * pi);

    //! [Slot] Delete a job and it's worker
    /*!
        \param index - index of job in model
        \sa createJob(), deleteAllJobs()
    */
    void deleteJob(int index);

    //! [Slot] Delete all jobs and its' workers
    /*!
        \sa createJob(), deleteAllJobs()
    */
    void deleteAllJobs();

    //! [Slot] Wrapper for job control functions
    /*!
        \param index - index of job in model
        \param command - command over job
        \sa jobFreeze(), jobUnfreeze(), jobUp(), jobDown()
    */
    void controlJob(int index, JobManager::JobCommands command);

    //! [Slot] Handler of job's progress changes
    /*!
        \param ticket - job ticket
        \param progress - job's progress value
    */
    void progressHandler(quint32 ticket, quint8 progress);

    //! [Slot] Handler of job's state to Error change
    /*!
        \param ticket - job ticket
        \param err - job's error type
    */
    void errorHandler(quint32 ticket, Worker::WorkerErrors err);

    //! [Slot] Handler of job's state changes
    /*!
        \param ticket - job ticket
        \param state - job's state
    */
    void stateHandler(quint32 ticket, JobStates::JobState state);
    
};

#endif // JOBMANAGER_H
