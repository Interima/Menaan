#include "plugininfomodel.h"

PluginInfoModel::PluginInfoModel(QList<PluginInfo> *dataList, QObject *parent):
    QAbstractListModel(parent),_data(dataList)
{
}

QHash <int, QByteArray> PluginInfoModel::roleNames() const
{
    QHash<int,QByteArray> roles;

    roles.insert(NameRole,QByteArray("name"));
    roles.insert(AuthorRole,QByteArray("author"));
    roles.insert(KeyLengthRole,QByteArray("keyLength"));
    roles.insert(BlockLengthRole,QByteArray("blockLength"));
    roles.insert(SafetyLevelRole,QByteArray("safetyLevel"));
    roles.insert(SpeedLevelRole,QByteArray("speedLevel"));

    return roles;

}

int PluginInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _data->count();
}

QVariant PluginInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    switch (role)
    {
        case NameRole: return QVariant::fromValue(_data->at(index.row()).getName());
        case AuthorRole: return QVariant::fromValue(_data->at(index.row()).getAuthor());
        case KeyLengthRole: return QVariant::fromValue(_data->at(index.row()).getKeyLength());
        case BlockLengthRole: return QVariant::fromValue(_data->at(index.row()).getBlockLength());
        case SafetyLevelRole: return QVariant::fromValue(_data->at(index.row()).getSafetyLevel());
        case SpeedLevelRole: return QVariant::fromValue(_data->at(index.row()).getSpeedLevel());
    }

    return QVariant();
}
