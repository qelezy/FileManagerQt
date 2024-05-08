#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treeviewitemdelegate.h"
#include "listviewitemdelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 3);

    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(QDir::rootPath());
    ui->treeView->setModel(dirModel);

    // Скрыть все колонки кроме названия
    ui->treeView->setColumnHidden(1, true);
    ui->treeView->setColumnHidden(2, true);
    ui->treeView->setColumnHidden(3, true);

    ui->treeView->setItemDelegate(new TreeViewItemDelegate(ui->treeView));

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    fileModel->setRootPath(QDir::rootPath());

    ui->listView->setModel(fileModel);
    ui->listView->setViewMode(QListView::IconMode);

    ui->listView->setItemDelegate(new ListViewItemDelegate(ui->listView));

    //ui->listView->setDragEnabled(false);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);


    //menu->setMinimumSize(ui->treeView->width(), 0);
    //toolBar->setStyleSheet("QMenu { border-top-left-radius: 5px; border-top-right-radius: 5px; background-color: rgb(28, 31, 41); } QMenu::item { color: white; } QMenu::item:selected { background-color: rgb(235, 235, 235); } QMenu::icon { padding: 10px; } QMenu::separator { height: 1px; background-color: rgb(200, 200, 200); } QFrame { border: none; } QPushButton { border: none; border-radius: 5px; } QPushButton::hover::!pressed { margin: 1px; border-radius: 9px; } QPushButton::pressed { margin: 3px; border-radius: 7px; }");

    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->desktopButton);
    buttonGroup->addButton(ui->downloadsButton);
    buttonGroup->addButton(ui->documentsButton);
    buttonGroup->addButton(ui->picturesButton);
    buttonGroup->addButton(ui->musicButton);
    buttonGroup->addButton(ui->videoButton);
    connect(buttonGroup, &QButtonGroup::idClicked, this, [=](int id) {
        buttonGroup->button(id)->setChecked(true);
        for (auto *button : buttonGroup->buttons()) {
            if (button->isChecked() && button->objectName() != QString::number(id)) {
                button->setChecked(false);
            }
        }
    });

    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(onTreeViewItem(QModelIndex)));

    connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onListViewItemDoubleClicked(QModelIndex)));

    connect(ui->currentPath, SIGNAL(returnPressed()), this, SLOT(currentPathChanged()));

    connectButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonMaximize()
{
    QIcon icon;
    if (window()->isMaximized()) {
        showNormal();
        icon.addFile(":/icons/fullscreen_icon.svg", QSize(18, 18));
        ui->maximizeButton->setIcon(icon);
        ui->window->setStyleSheet("QFrame {background-color: rgb(28, 31, 41); color: white; border: 1px solid rgb(47, 50, 60); border-radius: 10px;}");
    } else {
        showMaximized();
        icon.addFile(":/icons/fullscreen_exit_icon.svg", QSize(18, 18));
        ui->maximizeButton->setIcon(icon);
        ui->window->setStyleSheet("QFrame {background-color: rgb(28, 31, 41); color: white;}");
    }
}

void MainWindow::onTreeViewItem(QModelIndex index)
{
    if (buttonGroup->checkedButton()) {
        buttonGroup->checkedButton()->setChecked(false);
        buttonGroup->checkedButton()->setStyleSheet("QPushButton {padding-left: 22px;text-align: left;background-color: rgb(28, 31, 41);color: white;border-radius: 5px;}QPushButton:hover {background-color: rgb(57, 60, 70);}");
    }

    QString path = dirModel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(fileModel->setRootPath(path));

    backPaths.append(ui->currentPath->text());
    forwardPaths.clear();

    ui->currentPath->setText(path);
}

void MainWindow::currentPathChanged()
{
    fileModel->setRootPath(ui->currentPath->text());
    ui->listView->setRootIndex(fileModel->index(ui->currentPath->text()));
    ui->treeView->setCurrentIndex(dirModel->index(ui->currentPath->text()));
}

void MainWindow::onListViewItemDoubleClicked(QModelIndex index)
{
    QString path = fileModel->filePath(index);

    QFileInfo fileInfo(path);
    if (fileInfo.isDir()) {
        fileModel->setRootPath(path);
        ui->listView->setRootIndex(index);

        backPaths.append(ui->currentPath->text());
        forwardPaths.clear();

        ui->currentPath->setText(path);

        ui->treeView->setCurrentIndex(dirModel->index(path));
    } else {
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
}

void MainWindow::onUpButton()
{
    QString path = ui->currentPath->text();
    if (!path.isEmpty()) {
        QDir dir(path);
        if (dir.isRoot()) {
            ui->currentPath->setText("");
        } else {
            dir.cdUp();
            ui->currentPath->setText(dir.absolutePath());
        }
        backPaths.append(path);
        forwardPaths.clear();

        currentPathChanged();
    }
}

void MainWindow::onBackButton()
{
    if (!backPaths.isEmpty() && ui->currentPath->text() != backPaths.first()) {
        forwardPaths.prepend(ui->currentPath->text()); // Сохраняем текущий путь для возможности вернуться

        QString backPath = backPaths.takeLast();
        fileModel->setRootPath(backPath);
        ui->listView->setRootIndex(fileModel->index(backPath));
        ui->currentPath->setText(backPath);
    }
}

void MainWindow::onForwardButton()
{
    if (!forwardPaths.isEmpty() && ui->currentPath->text() != forwardPaths.last()) {
        backPaths.append(ui->currentPath->text()); // Сохраняем текущий путь для возможности вернуться назад

        QString forwardPath = forwardPaths.takeFirst();
        fileModel->setRootPath(forwardPath);
        ui->listView->setRootIndex(fileModel->index(forwardPath));
        ui->currentPath->setText(forwardPath);
    }
}

void MainWindow::onFastMenuButton()
{
    ui->treeView->clearSelection();
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    button->setStyleSheet("QPushButton {padding-left: 22px;text-align: left;background-color: rgb(28, 31, 41);color: white;border-radius: 5px;}QPushButton:hover {background-color: rgb(57, 60, 70);}QPushButton:checked {background-color: rgb(77, 80, 90);}");
    QString path;
    if (button->objectName().contains("desktop")) {
        path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    } else if (button->objectName().contains("downloads")) {
        path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    } else if (button->objectName().contains("documents")) {
        path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    } else if (button->objectName().contains("pictures")) {
        path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    } else if (button->objectName().contains("music")) {
        path = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    } else if (button->objectName().contains("video")) {
        path = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);
    }
    fileModel->setRootPath(path);
    ui->listView->setRootIndex(fileModel->index(path));

    backPaths.append(ui->currentPath->text());
    forwardPaths.clear();

    ui->currentPath->setText(path);
}


void MainWindow::connectButtons()
{
    // Кнопки окна приложения
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->minimizeButton, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(ui->maximizeButton, SIGNAL(clicked()), this, SLOT(onButtonMaximize()));

    // Кнопки панели инструментов
    connect(ui->upButton, SIGNAL(clicked()), this, SLOT(onUpButton()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(onBackButton()));
    connect(ui->forwardButton, SIGNAL(clicked()), this, SLOT(onForwardButton()));

    // Кнопки быстрого доступа
    connect(ui->desktopButton, SIGNAL(clicked()), this, SLOT(onFastMenuButton()));
    connect(ui->downloadsButton, SIGNAL(clicked()), this, SLOT(onFastMenuButton()));
    connect(ui->documentsButton, SIGNAL(clicked()), this, SLOT(onFastMenuButton()));
    connect(ui->picturesButton, SIGNAL(clicked()), this, SLOT(onFastMenuButton()));
    connect(ui->musicButton, SIGNAL(clicked()), this, SLOT(onFastMenuButton()));
    connect(ui->videoButton, SIGNAL(clicked()), this, SLOT(onFastMenuButton()));
}
