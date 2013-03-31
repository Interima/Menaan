#include "contentinfomodel.h"
#include "contenttypes.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

QFileInfo ContentInfoModel::typer;

ContentInfoModel::ContentInfoModel(QObject *parent) :
    QAbstractListModel(parent)
{
    currentPath.clear();

    onlyBase=onlyDirs=onlyFiles=false;
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

            typer.setFile(currentPath+"/"+_data.at(index.row()));

            if (typer.isDir()) return ContentTypes::Dir;

            else if (typer.isFile()) return ContentTypes::File;

            else if (typer.isSymLink()) return ContentTypes::Symlink;

            else return ContentTypes::Unknown; break;

       default: return QVariant();
    }
}

// View settings

void ContentInfoModel::setOnlyDirs(bool onlyDirsState)
{
    onlyDirs = onlyDirsState;
    refresh();
}

void ContentInfoModel::setOnlyFiles(bool onlyFilesState)
{
    onlyFiles = onlyFilesState;
    refresh();
}

void ContentInfoModel::setOnlyBase(bool onlyBaseState)
{
    onlyBase = onlyBaseState;
    refresh();
}


// Path control

QString ContentInfoModel::getCurrentPath()
{
    return currentPath;
}

void ContentInfoModel::changePath(QString path)
{
    currentPath = path;

    refresh();

    emit pathChanged();

    qDebug()<<currentPath;
}

void ContentInfoModel::cdDown(QString path)
{
    QDir dir(currentPath);
    if (!dir.cd(path)) return;

    changePath(dir.absolutePath());
}

void ContentInfoModel::cdUp()
{
    QDir dir(currentPath);

    if (!dir.cdUp()) return;

    changePath(dir.absolutePath());
}

void ContentInfoModel::refresh()
{
    beginResetModel();

    QDir::Filters filters=QDir::NoDotAndDotDot;

    if (onlyDirs) filters|=QDir::Dirs;
    if (onlyFiles) filters|=QDir::Files;

    if (onlyDirs || onlyBase || onlyFiles)
    {

        if (onlyBase)
            _data = QDir(currentPath).entryList(QStringList("*.mdbase"),filters);
        else
            _data = QDir(currentPath).entryList(filters);
    }

    else
            _data = QDir(currentPath).entryList(QDir::AllEntries | QDir::NoDotAndDotDot);

    endResetModel();
}
