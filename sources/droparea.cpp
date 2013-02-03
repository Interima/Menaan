
#include <QMimeData>
#include <QCursor>
#include "droparea.h"

DropArea::DropArea(QQuickItem *parent)
        : QQuickItem(parent), accepting(true)
{
    this->setAcceptHoverEvents((accepting));
}

void DropArea::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
    setCursor(QCursor(Qt::DragMoveCursor));
}

void DropArea::dragLeaveEvent(QDragLeaveEvent *event)
{
    Q_UNUSED(event)
    unsetCursor();
}

void DropArea::dropEvent(QDropEvent *event)
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

    this->setAcceptHoverEvents(true);

    //setAcceptDrops(accepting);
    emit acceptingDropsChanged();
}


