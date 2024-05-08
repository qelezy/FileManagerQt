#include "treeview.h"

TreeView::TreeView(QWidget *parent) : QTreeView(parent) { setMouseTracking(true); }

void TreeView::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor() != Qt::ArrowCursor) {
        setCursor(Qt::ArrowCursor);
    }
    QTreeView::mouseMoveEvent(event);
}
