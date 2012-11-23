#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include "droparea.h"

DropArea::DropArea(QDeclarativeItem *parent)
        : QDeclarativeItem(parent), accepting(true)
{
    setAcceptDrops(accepting);
}

void DropArea::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    event->acceptProposedAction();
    setCursor(Qt::DragMoveCursor);
}

void DropArea::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event)
    unsetCursor();
}

void DropArea::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    // if no text in mime
    if (!event->mimeData()->hasText()) return;

    QString text = event->mimeData()->text();
    // remove header if exists
    text.remove("file://");

    emit textDrop(text);
    unsetCursor();
}

void DropArea::setAcceptingDrops(bool _accepting)
{
    if (accepting == _accepting) return;

    accepting = _accepting;
    setAcceptDrops(accepting);
    emit acceptingDropsChanged();
}


