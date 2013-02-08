#include "contentinfomodel.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

ContentInfoModel::ContentInfoModel(QObject *parent) :
    QAbstractListModel(parent)
{
    _data = QDir(QCoreApplication::applicationDirPath()).entryList();
}

QHash <int,QByteArray> ContentInfoModel::roleNames() const
{
    QHash <int, QByteArray> roles;

    roles.insert(ItemNameRole, QByteArray("itemName"));

    return roles;
}

int ContentInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(&parent);

    return _data.count();
}

QVariant ContentInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    switch (role)
    {
        case ItemNameRole:
            return QVariant::fromValue(_data.at(index.row()));

       default: return QVariant();
    }
}

QString ContentInfoModel::getCurrentPath()
{
    return currentPath;
}

void ContentInfoModel::setOnlyDirs(bool onlyDirsState)
{
    onlyDirs = onlyDirsState;
}

void ContentInfoModel::setOnlyFiles(bool onlyFilesState)
{
    onlyFiles = onlyFilesState;
}

void ContentInfoModel::changePath(QString path)
{
    currentPath = path;

    refresh();

    emit pathChanged();
}

void ContentInfoModel::back()
{
    QDir dir(currentPath);

    dir.cdUp();

    currentPath = dir.absolutePath();

    refresh();

    emit pathChanged();
}

void ContentInfoModel::refresh()
{
    beginResetModel();

    _data = QDir(currentPath).entryList();

    endResetModel();
}
