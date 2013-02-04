#include "driveinfo.h"

DriveInfo::DriveInfo()
{
    this->label = "";
    this->mount = "";

    this->totalSize = -1;
    this->freeSize = -1;
}


void DriveInfo::setLabel(const QString val)
{
    this->label = val;
}

void DriveInfo::setMount(const QString val)
{
    this->mount = val;
}

void DriveInfo::setTotalSize(const qreal val)
{
    this->totalSize = val;
}

void DriveInfo::setFreeSize(const qreal val)
{
    this->freeSize = val;
}

QString DriveInfo::getLabel() const
{
    return this->label;
}

QString DriveInfo::getMount() const
{
    return this->mount;
}

qreal DriveInfo::getTotalSize() const
{
    return this->totalSize;
}

qreal DriveInfo::getFreeSize() const
{
    return this->freeSize;
}


