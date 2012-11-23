#include "jobinfo.h"

/******************     Constructors     ****************/
JobInfo::JobInfo()
{

}

JobInfo::JobInfo(int t, QString s, QString d,
                 QString a, JobStates::JobState st,
                 int p, int pr):
    ticket(t),source(s),destination(d),algorithm(a),
    state(st),progress(p),priority(pr)
{

}

/******************     Property Reader     ****************/

quint16 JobInfo::getTicket() const
{
    return this->ticket;
}

QString JobInfo::getSource() const
{
    return this->source;
}

QString JobInfo::getDestination() const
{
    return this->destination;
}

QString JobInfo::getAlgorithm() const
{
    return this->algorithm;
}

JobStates::JobState JobInfo::getState() const
{
    return this->state;
}

int JobInfo::getProgress() const
{
    return this->progress;
}

int JobInfo::getPriority() const
{
    return this->priority;
}

/******************     Property Setters     ****************/

void JobInfo::setTicket(const quint16 val)
{
    this->ticket = val;
}

void JobInfo::setSource(const QString val)
{
    this->source = val;
}

void JobInfo::setDestination(const QString val)
{
    this->destination = val;
}

void JobInfo::setAlgorithm(const QString val)
{
    this->algorithm = val;
}

void JobInfo::setState(const JobStates::JobState val)
{
    this->state = val;
}

void JobInfo::setProgress(const int val)
{
    this->progress = val;
}

void JobInfo::setPriority(const int val)
{
    this->priority = val;
}
