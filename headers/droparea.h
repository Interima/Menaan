#ifndef DROPAREA_H
#define DROPAREA_H

#include <QtDeclarative/QDeclarativeItem>

class DropArea : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(bool acceptingDrops READ isAcceptingDrops WRITE setAcceptingDrops NOTIFY acceptingDropsChanged)

public:
    DropArea(QDeclarativeItem *parent=0);
    bool isAcceptingDrops() const { return accepting; }
    void setAcceptingDrops(bool accepting);

signals:
    void textDrop(QString textData);
    void acceptingDropsChanged();

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
    bool accepting;
};

#endif // DROPAREA_H
