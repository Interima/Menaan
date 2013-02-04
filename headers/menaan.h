#ifndef MENAAN_H
#define MENAAN_H

#include <QtQuick/QQuickView>
#include "plugininfo.h"
#include "plugininfomodel.h"
#include "configdata.h"
#include "confighandler.h"
#include "jobinfomodel.h"
#include "jobmanager.h"
#include "jobtypes.h"

class Menaan : public QQuickView
{
    Q_OBJECT
public:

    Menaan(ConfigData * cfg, QWindow *parent = 0);

private:

    void pluginLibraryLoader();

    QList<PluginInfo> pluginInfoList;
    QList<JobInfo> jobInfoList;
    PluginInfoModel * pluginInfoModel;
    JobInfoModel * jobInfoModel;
    JobManager * jobManager;
    ConfigData * configData;


public slots:

    void createJob(QString in, QString out, QString key, QString args,
                   /*JobTypes::JobType*/quint8 type, int plInd);
    void deleteJob(int index);
    void freezeJob(int index);

    void unfreezeJob(int index);
    void upJob(int index);
    void downJob(int index);

    void openFile(QString sender);
    void openDirectory(QString sender);
    void openDatabase(QString sender);

    void errorDispatch(quint32 ticket, Worker::WorkerErrors err);

    void exitRequired();

    static bool configDataSave(int l, int mt, int afd, int e, int r);
    static bool configDataExport(QString path);
    static bool configDataImport(QString path);

    static QString generateUnique(QString path);

signals:

    void configDataUpdated(int l, int mt, int afd, int e, int r);

    void error(QString error);

    void dialogAnswer(QString sender, QString path);

};

#endif // MENAAN_H
