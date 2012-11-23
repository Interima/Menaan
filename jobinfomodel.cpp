#include "jobinfomodel.h"
#include <QDebug>

JobInfoModel::JobInfoModel(QList<JobInfo> *dt, QObject *parent):
    QAbstractListModel(parent),_data(dt)
{
    QHash<int,QByteArray> roles = this->roleNames();

    roles.insert(TicketRole,QByteArray("ticket"));
    roles.insert(SourceRole,QByteArray("source"));
    roles.insert(DestinationRole,QByteArray("destination"));
    roles.insert(AlgorithmRole,QByteArray("algorithm"));
    roles.insert(StateRole,QByteArray("state"));
    roles.insert(ProgressRole,QByteArray("progress"));
    roles.insert(PriorityRole,QByteArray("priority"));
    this->setRoleNames(roles);

}

int JobInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return _data->count();
}

QVariant JobInfoModel::data(const QModelIndex &index, int role) const
{
    // There is amazing bug from Qt
    // Qml don't understand JobStates::JobState enum!!!
    // We need convert it to quint8
    // So badly..

    if (!index.isValid()) return QVariant();

    switch (role)
    {
        case TicketRole: return QVariant::fromValue(_data->at(index.row()).getTicket());
        case SourceRole: return QVariant::fromValue(_data->at(index.row()).getSource());
        case DestinationRole: return QVariant::fromValue(_data->at(index.row()).getDestination());
        case AlgorithmRole: return QVariant::fromValue(_data->at(index.row()).getAlgorithm());
        case StateRole: return QVariant::fromValue(static_cast<quint8>(_data->at(index.row()).getState()));
        case ProgressRole: return QVariant::fromValue(_data->at(index.row()).getProgress());
        case PriorityRole: return QVariant::fromValue(_data->at(index.row()).getPriority());
    }

    return QVariant();
}

bool JobInfoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) return false;

    // Amazing!
    // Qt QList can't provide functions same [at], without returning constant object
    // [value] functions return copy of object!!!
    // May be const_cast? No,no,no...
    // Hmm... Use our old friend... operator[]
    switch (role)
    {
        case TicketRole: (*_data)[index.row()].setTicket(value.toInt());
                          emit dataChanged(index,index); return true;

        case SourceRole: (*_data)[index.row()].setSource(value.toString());
                          emit dataChanged(index,index); return true;

        case DestinationRole: (*_data)[index.row()].setDestination(value.toString());
                               emit dataChanged(index,index); return true;

        case AlgorithmRole: (*_data)[index.row()].setAlgorithm(value.toString());
                             emit dataChanged(index,index); return true;

        case StateRole: (*_data)[index.row()].setState(value.value<JobStates::JobState>());
                         emit dataChanged(index,index); return true;

        case ProgressRole: (*_data)[index.row()].setProgress(value.toInt());
                            emit dataChanged(index,index);return true;

        case PriorityRole: (*_data)[index.row()].setPriority(value.toInt());
                            emit dataChanged(index,index);return true;

    }

    return false;
}

void JobInfoModel::insertJob(const JobInfo &job)
{
    beginInsertRows(QModelIndex(),rowCount(QModelIndex()),rowCount(QModelIndex()));
    _data->append(job);
    endInsertRows();
}

void JobInfoModel::removeJob(const int jobIndex)
{
    beginRemoveRows(QModelIndex(),jobIndex,jobIndex);
    _data->removeAt(jobIndex);
    endRemoveRows();
}

// !!! this function is very slow to large data
QModelIndex JobInfoModel::ticketToIndex(quint32 ticket)
{
    JobInfo job;
    // !!! may be race condition
    for (qint32 i=0; i<_data->count(); i++)
    {
        if (_data->at(i).getTicket() == ticket)
            return this->index(i);
    }

    return QModelIndex();
}
