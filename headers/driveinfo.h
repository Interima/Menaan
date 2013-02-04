#ifndef DRIVEINFO_H
#define DRIVEINFO_H

#include <QtCore/QString>

class DriveInfo
{
public:

    DriveInfo();

    void setChar(const QString val);
    void setLabel(const QString val);
    void setMount(const QString val);

    void setTotalSize(const qreal val);
    void setFreeSize(const qreal val);

    QString getLabel() const;
    QString getMount() const;

    qreal getTotalSize() const;
    qreal getFreeSize() const;


private:

    QString label;
    QString mount;

    qreal totalSize;
    qreal freeSize;

};

#endif // DRIVEINFO_H
