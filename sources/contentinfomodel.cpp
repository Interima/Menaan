#include "contentinfomodel.h"
#include "contenttypes.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

QFileInfo ContentInfoModel::typer;

ContentInfoModel::ContentInfoModel(QObject *parent) :
    QAbstractListModel(parent)
{
    currentPath.clear();
}

QHash <int,QByteArray> ContentInfoModel::roleNames() const
{
    QHash <int, QByteArray> roles;

    roles.insert(ItemNameRole, QByteArray("itemName"));
    roles.insert(ItemTypeRole,QByteArray("itemType"));

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

        case ItemTypeRole:

            typer.setFile(currentPath+_data.at(index.row()));
            if (typer.isDir()) return ContentTypes::Dir;
            else if (typer.isFile()) return ContentTypes::File;
            else if (typer.isSymLink()) return ContentTypes::Symlink;
            else return ContentTypes::Unknown;

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

void ContentInfoModel::setOnlyBase(bool onlyBaseState)
{
    onlyBase = onlyBaseState;
}

void ContentInfoModel::changePath(QString path)
{
    currentPath = path;

    refresh();

    emit pathChanged();
}

void ContentInfoModel::cdDown(QString path)
{
    QDir dir(currentPath);
    if (!dir.cd(path)) return;

    currentPath= dir.absolutePath();

    refresh();

    emit pathChanged();
}

void ContentInfoModel::cdUp()
{
    QDir dir(currentPath);

    if (!dir.cdUp()) return;

    currentPath = dir.absolutePath();

    refresh();

    emit pathChanged();
}

void ContentInfoModel::refresh()
{
    beginResetModel();

    if (onlyDirs) _data = QDir(currentPath).entryList(QDir::Dirs|
                                                      QDir::NoDotAndDotDot);
    else if (onlyBase) _data = QDir(currentPath).entryList(
                QStringList("*.mdbase"),
                QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    else _data = QDir(currentPath).entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

    endResetModel();
}
