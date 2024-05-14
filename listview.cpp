#include "listview.h"

ListView::ListView(QWidget *parent) : QListView(parent)
{
    setMouseTracking(true);
    contextMenu = new QMenu(this);
    //contextMenu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contextMenu->setWindowFlag(Qt::FramelessWindowHint);
    contextMenu->setAttribute(Qt::WA_TranslucentBackground);
    contextMenu->setWindowFlag(Qt::NoDropShadowWindowHint);
    contextMenu->setStyleSheet("QMenu { border: 1px solid rgb(67, 70, 80); border-radius: 5px; background-color: rgb(48, 51, 61); padding: 5px; } QMenu::item { color: white; border-radius: 5px; padding: 5px; margin: 2px; } QMenu::item:selected { background-color: rgb(68, 71, 81); } QMenu::item:checked { background-color: rgb(68, 71, 81); } QMenu::icon { padding-right: 10px; } QMenu::separator { height: 1px; margin-top: 5px; margin-bottom: 5px; background-color: rgb(67, 70, 80); }");
    contextMenu->setMinimumSize(200, 100);

    // Содержимое контекстного меню
    QMenu *viewMenu = new QMenu(contextMenu);
    viewMenu->setWindowFlag(Qt::FramelessWindowHint);
    viewMenu->setAttribute(Qt::WA_TranslucentBackground);
    viewMenu->setWindowFlag(Qt::NoDropShadowWindowHint);
    viewMenu->setMinimumSize(100, 50);
    viewMenu->setTitle("Вид");
    viewMenu->setIcon(QIcon(":/icons/viewmenu.svg"));

    // События для меню "Вид"
    QAction *iconMode = new QAction(viewMenu), *listMode = new QAction(viewMenu);
    iconMode->setCheckable(true);
    iconMode->setChecked(true);
    listMode->setCheckable(true);
    //viewMenu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    iconMode->setIcon(QIcon(":/icons/iconmode.svg"));
    iconMode->setText("Значки");
    connect(iconMode, &QAction::triggered, this, [=]{
        setViewMode(QListView::IconMode);
        setWrapping(true);
        setFlow(QListView::LeftToRight);
    });

    listMode->setIcon(QIcon(":/icons/listmode.svg"));
    listMode->setText("Список");
    connect(listMode, &QAction::triggered, this, [=]{
        setViewMode(QListView::ListMode);
        setWrapping(false);
        setFlow(QListView::TopToBottom);
    });

    // События для контекстного меню
    QAction *createFolder = new QAction(contextMenu), *createFile = new QAction(contextMenu), *properties = new QAction(contextMenu);
    createFolder->setIcon(QIcon(":/icons/createfolder.svg"));
    createFolder->setText("Создать папку");
    createFile->setIcon(QIcon(":/icons/createfile.svg"));
    createFile->setText("Создать файл");
    properties->setIcon(QIcon(":/icons/properties.svg"));
    properties->setText("Свойства");

    viewMenu->addAction(iconMode);
    viewMenu->addAction(listMode);
    contextMenu->addMenu(viewMenu);
    contextMenu->addSeparator();
    contextMenu->addAction(createFolder);
    contextMenu->addAction(createFile);
    contextMenu->addSeparator();
    contextMenu->addAction(properties);
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
