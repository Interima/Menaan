#ifndef CONTENTINFOMODEL_H
#define CONTENTINFOMODEL_H

#include <QtCore/QtGlobal>
#include <QtCore/QAbstractListModel>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>


class ContentInfoModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString currentPath READ getCurrentPath() NOTIFY pathChanged())
public:

    enum ContentItemRoles
    {
        ItemNameRole = Qt::UserRole+1,
        ItemTypeRole
    };

    explicit ContentInfoModel(QObject* parent=0);

    QVariant data(const QModelIndex &index, int role) const;

    int rowCount(const QModelIndex &parent) const;

    QHash <int,QByteArray> roleNames() const;

private:

    QStringList _data;
    QString currentPath;

    bool onlyFiles;
    bool onlyDirs;
    bool onlyBase;

    static QFileInfo typer;


public slots:

    void setOnlyFiles(bool onlyFilesState);
    void setOnlyDirs(bool onlyDirsState);
    void setOnlyBase(bool onlyBaseState);

    void changePath(QString path);

    void cdUp();
    void cdDown(QString path);

    void refresh();

    QString getCurrentPath();

signals:

    void pathChanged();
};

#endif // CONTENTINFOMODEL_H
