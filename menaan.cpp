#include "menaan.h"
#include <QHBoxLayout>
#include <QtDeclarative/QDeclarativeContext>
#include <QApplication>
#include <QPluginLoader>
#include <QtXml/QXmlSimpleReader>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QTimer>
#include <QFileDialog>
#include <QSplashScreen>
#include <QTranslator>

#include "configdata.h"
#include "droparea.h"
#include "jobstates.h"
#include "jobtypes.h"


void Menaan::splashRunner()
{
    // create splash
    QSplashScreen * splash = new QSplashScreen(QPixmap(":/splash/MainSplash"));

    // set show/close timers
    QTimer* splashCloser = new QTimer(this);
    QTimer* splashShower = new QTimer(this);

    // configure timers
    splashShower->setSingleShot(true);
    // !!! the second timers need because splashscreen have a bug
    splashShower->setInterval(0);

    splashCloser->setSingleShot(true);
    splashCloser->setInterval(2000);

    connect(splashCloser,SIGNAL(timeout()),this,SLOT(show()));
    connect(splashCloser,SIGNAL(timeout()),splash,SLOT(close()));
    connect(splashShower,SIGNAL(timeout()),splash,SLOT(show()));

    splashCloser->start();
    splashShower->start();
}

Menaan::Menaan(ConfigData * cfg, QWidget *parent) :
        QWidget(parent),configData(cfg)
{
    qDebug()<<"[Menaan say:] Constructor started";
    qDebug()<<"[Menaan say:] Run splash";

    splashRunner();

    // hide close button
    Qt::WindowFlags flags =  this->windowFlags();
    flags &= ~Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);

    // set new cursor with hot spot
    QCursor * cur = new QCursor(QPixmap(":/cursors/MainCursor"),2,2);
    this->setCursor(*cur);

    // register type in metaobject system
    // it's need for QThread signal/slot connections
    qRegisterMetaType<JobStates::JobState>("JobStates::JobState");
    qRegisterMetaType<JobTypes::JobType>("JobTypes::JobType");
    qRegisterMetaType<Worker::WorkerErrors>("Worker::WorkerErrors");

    // load plugins
    pluginLibraryLoader();

    pluginInfoModel = new PluginInfoModel(&pluginInfoList,this);
    jobInfoModel = new JobInfoModel(&jobInfoList,this);
    jobManager = new JobManager(jobInfoModel, configData, this);
    connect(jobManager,SIGNAL(raiseError(quint32,Worker::WorkerErrors)),
            this,SLOT(errorDispatch(quint32,Worker::WorkerErrors)));

    view = new QDeclarativeView();
    QDeclarativeContext* context = view->rootContext();
    context->setContextProperty("pluginInfoModel",pluginInfoModel);
    context->setContextProperty("jobInfoModel",jobInfoModel);
    context->setContextProperty("menaan",this);

    qmlRegisterType<DropArea>("ix2.interima.droparea", 1, 0, "DropArea");
    qmlRegisterUncreatableType<JobStates>("ix2.interima.jobstates", 1, 0,"JobStates","Error");
    qmlRegisterUncreatableType<JobTypes>("ix2.interima.jobtypes", 1, 0,"JobTypes","Error");

    view->setSource(QUrl::fromLocalFile("qml/Menaan/main.qml"));
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);


    emit configDataUpdated(configData->getLanguage(),
                           configData->getMultiThread(),
                           configData->getAutoFinishedDelete(),
                           configData->getExt(),
                           configData->getRewrite());


    QHBoxLayout * lay = new QHBoxLayout();
    lay->addWidget(view);
    lay->setMargin(0);
    this->setMinimumSize(800,400);
    this->setLayout(lay);
}


void Menaan::pluginLibraryLoader()
{
    qDebug()<<"[Menaan say:] Start plugins loading";
    QDir PluginsDirectory = QDir(QCoreApplication::applicationDirPath());
    PluginsDirectory.cd("plugins");
    qDebug()<<"[Menaan say:] Plugins directory: "<<PluginsDirectory.absolutePath();

    foreach (QString fileName, PluginsDirectory.entryList(QDir::Files))
    {
        qDebug()<<"[Menaan say:] Checking file: "<<fileName;
        QPluginLoader loader(PluginsDirectory.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin!=0)
        {
            qDebug()<<"[Menaan say:] Load complete for: "<<fileName;
            PluginInfo plgInf(plugin);
            pluginInfoList.append(plgInf);
        }
        else
        {
            qDebug()<<"[Menaan say:] Loading error for: "<<fileName;
            qDebug()<<"[Menaan say:] Error message: "<<loader.errorString();
        }
    }
}

/*****************************************************************************/

void Menaan::createJob(QString in, QString out, QString key, QString args,
                       /*JobTypes::JobType*/ quint8 type, int plgIn)
{
    QFileInfo fileInfo, fileInfo2;

    // This is the Qt bug, it can't send enum as parameter
    // and Qml use java function Number to cast and set it to us
    // there we recast it to original enum type
    JobTypes::JobType _type = static_cast<JobTypes::JobType>(type);

    if (in.right(1)=="/") in.chop(1);
    if (out.right(1)=="/") out.chop(1);

    // if input is database file
    if (in.left(4)=="db::")
    {
        in.remove("db::");
        QFile dbFile(in);

        if (!dbFile.exists())
        {
            emit error(tr("Database file not exists."));
            qDebug()<<"[Menaan say:] Database file is not exists:"<<in;
            return;
        }

        if (!(QDir(out).exists()))
        {
            emit error(tr("Output directory not exists."));
            qDebug()<<"[Menaan say:] Output dir is not exists:"<<in;
            return;
        }

        if (!dbFile.open(QIODevice::ReadOnly))
        {
            emit error(tr("Can't open database file."));
            qDebug()<<"[Menaan say:] Can't open database file:"<<in;
            return;
        }

        QTextStream st(&dbFile);

        // read database file content
        while (!st.atEnd())
        {
            QString str = st.readLine();

            QFile inFile(str);
            QFile outFile(out+"/"+QFileInfo(str).fileName());

            this->createJob(inFile.fileName(), outFile.fileName(),
                            key, args, type, plgIn);
        }

        return;
    }

    // to get info of in and out
    fileInfo.setFile(in);
    fileInfo2.setFile(out);

    // if input or output is directory
    if (fileInfo.isDir()||fileInfo2.isDir())
    {
        QDir inDir(in);
        QDir outDir(out);

        if (!inDir.exists())
        {
            emit error(tr("Input directory not exists."));

            qDebug()<<"[Menaan say:] Input dir is not exists:"<<in;

            return;
        }

        if (!outDir.exists())
        {
            if (!outDir.mkpath(outDir.absolutePath()))
            {
                emit error(tr("Output directory not exists."));

                qDebug()<<"[Menaan say:] Output dir not exists";

                return;
            }
        }

        if  ((outDir == inDir)&&(!configData->getExt()))
        {
            emit error(tr("Output directory can't be input directory.\n"
                          "Please enable 'Use Special Ext' option."));

            qDebug()<<"[Menaan say:] Output dir equ input dir";

            return;
        }

        // recursive call
        foreach (QString element, inDir.entryList(QDir::Files|QDir::Dirs))
        {
            if ((element==".")||(element=="..")) continue;
            this->createJob(QString(inDir.path()+"/"+element),
                            QString(outDir.path()+"/"+element),
                            key, args, type, plgIn);
        }

        return;
    }

    if (!fileInfo.exists())
    {
        emit error(tr("Input file not exists."));

        qDebug()<<"[Menaan say:] Input file is not exists:"<<in;

        return;
    }

    if ((in == out)&&(!configData->getExt()))
    {
        emit error(tr("Output file can't be input file.\n"
                      "Please enable 'Use Special Ext' option."));

        qDebug()<<"[Menaan say:] Output file equ input file";

        return;
    }

    PluginInterface * oldInstance = pluginInfoList[plgIn].getPlugin();
    qDebug()<<"[Menaan say:] Clone plugin instance";
    PluginInterface * newInstance = oldInstance->clone();

    // create job
    jobManager->createJob(in,out,key,args,_type,newInstance);
}

void Menaan::deleteJob(int index)
{
    jobManager->deleteJob(index);
}

void Menaan::freezeJob(int index)
{
    jobManager->controlJob(index,JobManager::Freeze);
}

void Menaan::unfreezeJob(int index)
{
    jobManager->controlJob(index,JobManager::UnFreeze);
}

void Menaan::upJob(int index)
{
    jobManager->controlJob(index,JobManager::Up);
}

void Menaan::downJob(int index)
{
    jobManager->controlJob(index,JobManager::Down);
}

/*****************************************************************************/
bool Menaan::configDataRecovery()
{
    qDebug()<<"[Menaan say:] Start config recovery";

    QString directory = QApplication::applicationDirPath();

    //! remove old config file
    QFile file(directory+"/config.xml");
    bool res = file.remove();

    qDebug()<<"[Menaan say:] Remove old config: "<<res;

    //! copy default config
    res = QFile::copy(directory+"/default.xml",directory+"/config.xml");

    qDebug()<<"[Menaan say:] Recovery default config: "<<res;

    return res;
}


bool Menaan::configDataSave(int l, int mt, int afd, int e, int r)
{
    qDebug()<<"[Menaan say:] Saving new config";

    ConfigData data(l,mt,afd,e,r);
    data.saveTo(QApplication::applicationDirPath()+"/config.xml");

    return true;
}


bool Menaan::configDataImport(QString path)
{
    QString directory = QApplication::applicationDirPath();

    // remove old config file
    QFile file(directory+"/config.xml");
    file.remove();

    return QFile::copy(path,directory+"/config.xml");
}

bool Menaan::configDataExport(QString path)
{
    QString directory = QApplication::applicationDirPath();
    return QFile::copy(directory+"/config.xml",path);
}

QString Menaan::generateUnique(QString path)
{
    QFileInfo fi(path);
    QString temp;

    do
    {
        temp.clear();
        temp = fi.path() + "/" + QString::number(qrand()) + "_" + fi.fileName();
        fi.setFile(temp);
    } while (fi.exists());

    return fi.absoluteFilePath();
}

/*****************************************************************************/

void Menaan::errorDispatch(quint32 ticket, Worker::WorkerErrors err)
{
    QString msg;
    switch (err)
    {
        case Worker::InputFileOpenError :
            msg = tr("Can't open input file."); break;

        case Worker::OutputFileOpenError :
            msg = tr("Can't open output file."); break;

        case Worker::InputFileReadError :
            msg = tr("Can't read from input file."); break;

        case Worker::OutputFileWriteError :
            msg = tr("Can't write in output file."); break;

        case Worker::PluginInitError :
            msg = tr("Can't init plugin.\nCheck special parameters."); break;

        case Worker::MagicNumberError :
        msg = tr("Can't read magic number.\nMay be the file wasn't encoded by Mena'an."); break;
    }

    msg = tr("An error occured.\n")+msg+tr("\nJob ticket: %1").arg(QString::number(ticket));

    emit this->error(msg);
}

/*****************************************************************************/

void Menaan::openFile(QString sender)
{
    QString fileName;

    fileName = QFileDialog::getOpenFileName(this,tr("Open file"),QDir::homePath());

    if (fileName.isEmpty()) return;

    emit dialogAnswer(sender,fileName);

}

void Menaan::openDirectory(QString sender)
{
    QString dirName;

    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;

    dirName = QFileDialog::getExistingDirectory(this,tr("Open directory"),QDir::homePath(),options);

    if (dirName.isEmpty()) return;

    emit dialogAnswer(sender,dirName);
}

void Menaan::openDatabase(QString sender)
{
    QString dBase;

    dBase = QFileDialog::getOpenFileName(this,tr("Open database"),QDir::homePath(),tr("Mena'an Database Files (*.mdbase)"));

    if (dBase.isEmpty()) return;

    emit dialogAnswer(sender,"db::"+dBase);
}

/*****************************************************************************/

void Menaan::exitRequired()
{
    jobManager->deleteAllJobs();
    this->close();
}


