#ifndef PLUGININFOMODEL_H
#define PLUGININFOMODEL_H

#include <QAbstractListModel>
#include "plugininfo.h"

class PluginInfoModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum
    {
        NameRole = Qt::UserRole+1,
        AuthorRole,KeyLengthRole,BlockLengthRole,SafetyLevelRole,SpeedLevelRole
    };

    explicit PluginInfoModel(QList<PluginInfo>* dataList, QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &__parent) const;
    QHash <int, QByteArray> roleNames() const;

private:
    QList<PluginInfo> * _data;
    
};

#endif // PLUGININFOMODEL_H
