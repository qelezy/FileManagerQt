#include "stackedwidget.h"

StackedWidget::StackedWidget(QWidget *parent) : QStackedWidget(parent)
{
    setMouseTracking(true);

    listView = new QListView(this);
    listView->setViewMode(QListView::IconMode);
    listView->setFlow(QListView::LeftToRight);

    listView->setSelectionBehavior(QAbstractItemView::SelectItems);
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    treeView = new QTreeView(this);
    treeView->setSortingEnabled(true);
    treeView->setItemsExpandable(false);
    treeView->sortByColumn(0, Qt::AscendingOrder);

    treeView->header()->setDefaultSectionSize(100);
    treeView->header()->setStretchLastSection(false);

    treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    addWidget(listView);
    addWidget(treeView);

    createMenus();
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
        if (currentWidget() == listView) {
            if (listView->indexAt(event->pos()).isValid()) {
                this->selectedItemMenu->exec(event->globalPos());
            } else {
                this->folderMenu->exec(event->globalPos());
            }
        } else if (currentWidget() == treeView) {
            if (treeView->indexAt(event->pos()).isValid()) {
                this->selectedItemMenu->exec(event->globalPos());
            } else {
                this->folderMenu->exec(event->globalPos());
            }
        }
    }
}

void StackedWidget::createMenus()
{
    // Создание меню для невыделенных элементов
    folderMenu = new QMenu(this);
    folderMenu->setWindowFlag(Qt::FramelessWindowHint);
    folderMenu->setAttribute(Qt::WA_TranslucentBackground);
    folderMenu->setWindowFlag(Qt::NoDropShadowWindowHint);
    folderMenu->setStyleSheet("QMenu { border: 1px solid rgb(67, 70, 80); border-radius: 5px; background-color: rgb(48, 51, 61); padding: 5px; } QMenu::item { color: white; border-radius: 5px; padding: 5px; margin: 2px; } QMenu::item:selected { background-color: rgb(68, 71, 81); } QMenu::item:checked { background-color: rgb(68, 71, 81); } QMenu::icon { padding-right: 10px; } QMenu::separator { height: 1px; margin-top: 5px; margin-bottom: 5px; background-color: rgb(67, 70, 80); }");
    folderMenu->setMinimumSize(200, 100);

    // Содержимое контекстного меню
    QMenu *viewMenu = new QMenu(folderMenu);
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
    iconMode->setIcon(QIcon(":/icons/iconmode.svg"));
    iconMode->setText("Значки");
    QShortcut *icon = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_I), this);
    iconMode->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_I));
    connect(icon, &QShortcut::activated, this, [=] {
        setCurrentWidget(listView);
        listMode->setChecked(false);
        iconMode->setChecked(true);
    });
    connect(iconMode, &QAction::triggered, this, [=]{
        setCurrentWidget(listView);
        listMode->setChecked(false);
    });

    listMode->setIcon(QIcon(":/icons/listmode.svg"));
    listMode->setText("Список");
    QShortcut *list = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_L), this);
    listMode->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
    connect(list, &QShortcut::activated, this, [=] {
        setCurrentWidget(treeView);
        iconMode->setChecked(false);
        listMode->setChecked(true);
    });
    connect(listMode, &QAction::triggered, this, [=]{
        setCurrentWidget(treeView);
        iconMode->setChecked(false);
    });

    // События для контекстного меню
    QAction *createFolder = new QAction(folderMenu),
        *createFile = new QAction(folderMenu),
        *paste = new QAction(folderMenu),
        *properties = new QAction(folderMenu);
    createFolder->setIcon(QIcon(":/icons/createfolder.svg"));
    createFolder->setText("Создать папку");
    QShortcut *folder = new QShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_N), this);
    connect(folder, &QShortcut::activated, this, [=] {
        emit createFolderSignal();
    });
    createFolder->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_N));
    connect(createFolder, &QAction::triggered, this, [=]{
        emit createFolderSignal();
    });

    createFile->setIcon(QIcon(":/icons/createfile.svg"));
    createFile->setText("Создать файл");
    QShortcut *file = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_N), this);
    connect(file, &QShortcut::activated, this, [=] {
        emit createFileSignal();
    });
    createFile->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    connect(createFile, &QAction::triggered, this, [=]{
        emit createFileSignal();
    });

    paste->setIcon(QIcon(":/icons/paste.svg"));
    paste->setText("Вставить");
    paste->setEnabled(false);
    connect(paste, &QAction::triggered, this, [=]{
        if (paste->isEnabled()) {
            emit pasteSignal();
        }
    });

    properties->setIcon(QIcon(":/icons/properties.svg"));
    properties->setText("Свойства");
    connect(properties, &QAction::triggered, this, [=]{
        emit propertiesSignal();
    });

    viewMenu->addAction(iconMode);
    viewMenu->addAction(listMode);
    folderMenu->addMenu(viewMenu);
    folderMenu->addSeparator();
    folderMenu->addAction(createFolder);
    folderMenu->addAction(createFile);
    folderMenu->addSeparator();
    folderMenu->addAction(paste);
    folderMenu->addSeparator();
    folderMenu->addAction(properties);

    // Создание меню для выделенных элементов
    selectedItemMenu = new QMenu(this);
    selectedItemMenu->setWindowFlag(Qt::FramelessWindowHint);
    selectedItemMenu->setAttribute(Qt::WA_TranslucentBackground);
    selectedItemMenu->setWindowFlag(Qt::NoDropShadowWindowHint);
    selectedItemMenu->setStyleSheet("QMenu { border: 1px solid rgb(67, 70, 80); border-radius: 5px; background-color: rgb(48, 51, 61); padding: 5px; } QMenu::item { color: white; border-radius: 5px; padding: 5px; margin: 2px; } QMenu::item:selected { background-color: rgb(68, 71, 81); } QMenu::item:checked { background-color: rgb(68, 71, 81); } QMenu::icon { padding-right: 10px; } QMenu::separator { height: 1px; margin-top: 5px; margin-bottom: 5px; background-color: rgb(67, 70, 80); }");
    selectedItemMenu->setMinimumSize(200, 100);

    // Содержимое контекстного меню
    QAction *rename = new QAction(selectedItemMenu),
            *copy = new QAction(selectedItemMenu),
                *cut = new QAction(selectedItemMenu),
                *deleteAction = new QAction(selectedItemMenu),
                    *properties2 = new QAction(selectedItemMenu);

    rename->setIcon(QIcon(":/icons/rename.svg"));
    rename->setText("Переименовать");
    rename->setShortcut(QKeySequence(Qt::Key_F2));
    connect(rename, &QAction::triggered, this, [=]{
        if (currentWidget() == listView) {
            listView->edit(listView->currentIndex());
        } else if (currentWidget() == treeView) {
            treeView->edit(treeView->currentIndex());
        }
    });

    copy->setIcon(QIcon(":/icons/copy.svg"));
    copy->setText("Копировать");
    connect(copy, &QAction::triggered, this, [=]{
        emit copySignal();
        paste->setEnabled(true);
    });

    cut->setIcon(QIcon(":/icons/cut.svg"));
    cut->setText("Вырезать");
    connect(cut, &QAction::triggered, this, [=]{
        emit cutSignal();
        paste->setEnabled(true);
    });

    deleteAction->setIcon(QIcon(":/icons/delete.svg"));
    deleteAction->setText("Удалить");
    QShortcut *deleteShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    connect(deleteShortcut, &QShortcut::activated, this, [=] {
        emit deleteSignal();
    });
    deleteAction->setShortcut(QKeySequence(Qt::Key_Delete));
    connect(deleteAction, &QAction::triggered, this, [=]{
        emit deleteSignal();
    });

    properties2->setIcon(QIcon(":/icons/properties.svg"));
    properties2->setText("Свойства");
    connect(properties2, &QAction::triggered, this, [=]{
        emit propertiesSignal();
    });

    selectedItemMenu->addAction(rename);
    selectedItemMenu->addSeparator();
    selectedItemMenu->addAction(copy);
    selectedItemMenu->addAction(cut);
    selectedItemMenu->addSeparator();
    selectedItemMenu->addAction(deleteAction);
    selectedItemMenu->addSeparator();
    selectedItemMenu->addAction(properties);
}
