#ifndef DROPAREA_H
#define DROPAREA_H

#include <QtQuick/QQuickItem>

class DropArea : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool acceptingDrops READ isAcceptingDrops WRITE setAcceptingDrops NOTIFY acceptingDropsChanged)

public:

    DropArea(QQuickItem * parent=0);
    bool isAcceptingDrops() const { return accepting; }
    void setAcceptingDrops(bool accepting);

signals:

    void textDrop(QString textData);
    void acceptingDropsChanged();

protected:

    void dragEnterEvent(QDragEnterEvent * event);
    void dragLeaveEvent(QDragLeaveEvent * event);
    void dropEvent(QDropEvent *event);

private:

    bool accepting;
};

#endif // DROPAREA_H
