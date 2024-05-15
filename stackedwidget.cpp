#include "stackedwidget.h"

StackedWidget::StackedWidget(QWidget *parent) : QStackedWidget(parent)
{
    setMouseTracking(true);
    listView = new QListView(this);
    listView->setViewMode(QListView::IconMode);
    listView->setFlow(QListView::LeftToRight);
    treeView = new QTreeView(this);
    treeView->setSortingEnabled(true);
    treeView->setItemsExpandable(false);
    treeView->sortByColumn(0, Qt::AscendingOrder);

    treeView->header()->setDefaultSectionSize(100);
    treeView->header()->setStretchLastSection(false);

    addWidget(listView);
    addWidget(treeView);

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
        setCurrentWidget(listView);
        listMode->setChecked(false);
    });

    listMode->setIcon(QIcon(":/icons/listmode.svg"));
    listMode->setText("Список");
    connect(listMode, &QAction::triggered, this, [=]{
        setCurrentWidget(treeView);
        iconMode->setChecked(false);
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

void StackedWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor() != Qt::ArrowCursor) {
        setCursor(Qt::ArrowCursor);
    }
    QStackedWidget::mouseMoveEvent(event);
}

void StackedWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if (event->reason() == QContextMenuEvent::Mouse) {
        contextMenu->exec(event->globalPos());
    }
}
