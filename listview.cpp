#include "listview.h"

ListView::ListView(QWidget *parent) : QListView(parent)
{
    setMouseTracking(true);
    contextMenu = new QMenu(this);
    contextMenu->setWindowFlag(Qt::FramelessWindowHint);
    contextMenu->setAttribute(Qt::WA_TranslucentBackground);
    contextMenu->setWindowFlag(Qt::NoDropShadowWindowHint);
    contextMenu->setStyleSheet("QMenu { border: 1px solid rgb(67, 70, 80); border-radius: 5px; background-color: rgb(48, 51, 61); padding: 5px; } QMenu::item { color: white; border-radius: 5px; padding: 5px; } QMenu::item:selected { background-color: rgb(68, 71, 81); } QMenu::icon { padding: 10px; } QMenu::separator { height: 1px; margin-top: 5px; margin-bottom: 5px; background-color: rgb(67, 70, 80); }");
    contextMenu->setMinimumSize(200, 100);

    // Содержимое контекстного меню
    QMenu *viewMenu = new QMenu(contextMenu);
    viewMenu->setWindowFlag(Qt::FramelessWindowHint);
    viewMenu->setAttribute(Qt::WA_TranslucentBackground);
    viewMenu->setWindowFlag(Qt::NoDropShadowWindowHint);
    viewMenu->setMinimumSize(100, 50);

    viewMenu->setTitle("Вид");
    viewMenu->addAction("Значки");
    viewMenu->addAction("Список");
    contextMenu->addMenu(viewMenu);
    contextMenu->addSeparator();
    contextMenu->addAction("Создать папку");
    contextMenu->addAction("Создать файл");
    contextMenu->addSeparator();
    contextMenu->addAction("Свойства");
}

void ListView::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor() != Qt::ArrowCursor) {
        setCursor(Qt::ArrowCursor);
    }
    QListView::mouseMoveEvent(event);
}

void ListView::contextMenuEvent(QContextMenuEvent *event)
{
    if (event->reason() == QContextMenuEvent::Mouse) {
        contextMenu->exec(event->globalPos());
    }
}
