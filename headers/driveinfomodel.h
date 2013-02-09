#ifndef DRIVEINFOMODEL_H
#define DRIVEINFOMODEL_H

#include "driveinfomodel.h"
#include "driveinfo.h"

#include <QtCore/QtGlobal>
#include <QtCore/QAbstractListModel>


#ifdef Q_OS_WIN32
    #include "windows.h"
#endif

#ifdef Q_OS_LINUX
    #include "mntent.h"
    #include "sys/statvfs.h"
#endif


class DriveInfoModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum DriveRoles
    {
        LabelRole = Qt::UserRole+1,
        MountRole,
        TotalSizeRole,
        FreeSizeRole
    };

    explicit DriveInfoModel(QObject* parent=0);

    QVariant data(const QModelIndex &index, int role) const;

    int rowCount(const QModelIndex &parent) const;

    QHash <int,QByteArray> roleNames() const;

    void inflate();

private:

    QList<DriveInfo> _data;

#ifdef Q_OS_WIN32
    void winInflate();
#endif

#ifdef Q_OS_LINUX
    void nixInflate();
#endif

public slots:

    void refresh();

};

#endif // DRIVEINFOMODEL_H
