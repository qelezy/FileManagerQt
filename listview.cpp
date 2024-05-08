#include "listview.h"

ListView::ListView(QWidget *parent) : QListView(parent) { setMouseTracking(true); }

void ListView::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor() != Qt::ArrowCursor) {
        setCursor(Qt::ArrowCursor);
    }
    QListView::mouseMoveEvent(event);
}
