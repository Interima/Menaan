#include "driveinfomodel.h"
#include "driveinfo.h"

#include <QtCore/QDir>
#include <QDebug>

DriveInfoModel::DriveInfoModel(QObject *parent) :
    QAbstractListModel(parent)
{
    // nothing to do
}

QHash <int,QByteArray> DriveInfoModel::roleNames() const
{
    QHash <int, QByteArray> roles;

    roles.insert(LabelRole, QByteArray("label"));
    roles.insert(MountRole, QByteArray("mount"));
    roles.insert(TotalSizeRole, QByteArray("totalSize"));
    roles.insert(FreeSizeRole, QByteArray("freeSize"));

    return roles;

}

int DriveInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(&parent);

    return _data.count();
}

QVariant DriveInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    switch (role)
    {
        case LabelRole:
            return QVariant::fromValue(_data.at(index.row()).getLabel());

        case MountRole :
            return QVariant::fromValue(_data.at(index.row()).getMount());

        case TotalSizeRole:
            return QVariant::fromValue(_data.at(index.row()).getTotalSize());

        case FreeSizeRole :
            return QVariant::fromValue(_data.at(index.row()).getFreeSize());

        default: return QVariant();
    }
}


void DriveInfoModel::inflate()
{

#ifdef Q_OS_WIN32
    this->winInflate();
#endif

#ifdef Q_OS_LINUX
    this->nixInflate();
#endif

}


#ifdef Q_OS_WIN32

#define DATA_BIT_COUNT 26

quint8 ExDriveInfo::winGetDiskInfo()
{
    int   dState;
    bool  dFlag;
    DWORD dMask;
    WORD  dErrorMode;
    UINT  dDriveType;
    bool  dReady;

    QString iChar;
    QString iType;
    quint64 iFreeBytesAvailable;
    quint64 iTotalNumberOfBytes;
    quint64 iTotalNumberOfFreeBytes;
    DWORD   iDriveSn;

    // get local drives mask
    dMask = GetLogicalDrives();

    // check all bits of drives mask
    for(quint8 i=0;i<DATA_BIT_COUNT;i++)
    {
       // get state of disk i
       dState = ((dMask>>i)&0x01);

       if(dState)
       {
           // create exdrive
           ExDrive * tmpExDrive =new ExDrive();

           // get char of disk (from ascii)
           iChar = QChar((char)(65+i)) + QString(":\\");

           // set disk char
           tmpExDrive->setChar(iChar);

           // disable critical errors
           dErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS);
           // get disk ready state (checkn if root directory of disk is exists)
           dReady = QDir(iChar).exists();
           // restore error mode
           SetErrorMode(dErrorMode);

           if (dReady)
           {
               // get drive type
               dDriveType = GetDriveType(iChar.toStdWString().c_str());

               // get type of disk
               if (dDriveType == DRIVE_REMOVABLE)           iType = QString("REMOVABLE");
                     else if (dDriveType == DRIVE_FIXED)    iType = QString("FIXED");
                     else if (dDriveType == DRIVE_REMOTE)   iType = QString("REMOTE");
                     else if (dDriveType == DRIVE_CDROM)    iType = QString("CD-ROM");
                     else if (dDriveType == DRIVE_RAMDISK)  iType = QString("RAMDISK");
                     else                                   iType = QString("UNDEFINED");

               // set disk type
               tmpExDrive->setType(iType);

                     // if drive is fixed or removable get it extended info
                     if ((dDriveType == DRIVE_REMOVABLE)||(dDriveType == DRIVE_FIXED))
                     {
                            WCHAR   dDriveLabel[30];
                            WCHAR   dDriveFs[30];
                            DWORD   dDriveNameSize = sizeof(dDriveLabel);

                            // get info about disk spaces
                            dFlag = GetDiskFreeSpaceEx(iChar.toStdWString().c_str(),
                                                       (PULARGE_INTEGER)&iFreeBytesAvailable,
                                                       (PULARGE_INTEGER)&iTotalNumberOfBytes,
                                                       (PULARGE_INTEGER)&iTotalNumberOfFreeBytes
                                                       );


                            if (!dFlag) continue;

                            // set disk space parameters
                            tmpExDrive->setFreeSpace(iFreeBytesAvailable);
                            tmpExDrive->setTotalSize(iTotalNumberOfBytes);

                            // get label, serial , file system
                            dFlag = GetVolumeInformation(iChar.toStdWString().c_str(),
                                                       dDriveLabel,
                                                       sizeof(dDriveLabel),
                                                       &iDriveSn,
                                                       &dDriveNameSize,
                                                       NULL,
                                                       dDriveFs,
                                                       sizeof(dDriveFs)
                                                       );
                            if (dFlag)
                            {
                                tmpExDrive->setLabel(QString::fromWCharArray((WCHAR*) dDriveLabel));
                                tmpExDrive->setSerial(QString::number(iDriveSn));
                                tmpExDrive->setFileSystem(QString::fromWCharArray((WCHAR*) dDriveFs));
                            }
                            else continue;
                     }
              }
              else
              {
                  continue;
              }
       }
    }

    return 0x00;
}
#endif

#ifdef Q_OS_LINUX

void DriveInfoModel::nixInflate()
{
    // WARNING NON-PORTABLE CODE

    // mtab - mounted file system description file
    // usually located in /etc
    // open mtab for reading by setmntent
    FILE* mounts = setmntent("/etc/mtab", "r");

    // mtab entry structure
    mntent *ent;

    // read line by line by getmntent
    while ( (ent = getmntent(mounts)) != NULL )
    {
        // virtual file system statistical structure
        struct statvfs stfs;

        // name of mounted file system
        QString str = QString::fromLocal8Bit(ent->mnt_fsname);

        // exclude systems in dev/
        if(str.indexOf("dev/")==-1) continue;

        // init instance of  statvfs by mount path
        if (statvfs(ent->mnt_dir,&stfs)!=0) continue;

        // get disk sizes
        qreal available =((quint64)stfs.f_bavail*(quint64)stfs.f_frsize)/(1024*1024);
        qreal total =  ((quint64)stfs.f_blocks*(quint64)stfs.f_frsize)/(1024*1024);

        // create and inflate drive info
        DriveInfo tmpDrive;

        tmpDrive.setTotalSize(total);
        tmpDrive.setFreeSize(available);
        tmpDrive.setMount(ent->mnt_dir);
        tmpDrive.setLabel("/"+QDir(ent->mnt_dir).dirName());

        _data.append(tmpDrive);

        qDebug()<<tmpDrive.getLabel();
        qDebug()<<tmpDrive.getMount();
        qDebug()<<tmpDrive.getFreeSize();
        qDebug()<<tmpDrive.getTotalSize();

    }

    endmntent(mounts);
}
#endif
