#include "activeworkerinfo.h"

ActiveWorkerInfo::ActiveWorkerInfo()
{

}

ActiveWorkerInfo::ActiveWorkerInfo(quint16 tckt, QString src, QString dst)
    : ticket(tckt),source(src),destination(dst)
{

}

bool ActiveWorkerInfo::isConflict(const ActiveWorkerInfo& val) const
{
    if ((this->getSource()==val.getDestination())||
            (this->getDestination()==val.getSource())||
            (this->getDestination()==val.getDestination()))

       return true;

    else return false;

}

quint16 ActiveWorkerInfo::getTicket() const
{
    return this->ticket;
}

QString ActiveWorkerInfo::getSource() const
{
    return this->source;
}

QString ActiveWorkerInfo::getDestination() const
{
    return this->destination;
}


void ActiveWorkerInfo::setTicket(const quint16 tckt)
{
    this->ticket = tckt;
}

void ActiveWorkerInfo::setSource(const QString src)
{
    this->source = src;
}

void ActiveWorkerInfo::setDestination(const QString dst)
{
    this->destination = dst;
}
