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
    //ui->treeView->setCurrentIndex(dirModel->index(ui->currentPath->text()));
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

        //ui->treeView->setCurrentIndex(dirModel->index(path));
    } else {
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
}

void MainWindow::onUpButton()
{
    if (!ui->currentPath->text().isEmpty()) {
        QDir dir(ui->currentPath->text());
        dir.cdUp();
        ui->currentPath->setText(dir.absolutePath());
        currentPathChanged();
    }
}

void MainWindow::onBackButton()
{
    qDebug() << backPaths << forwardPaths;
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
    qDebug() << backPaths << forwardPaths;
    if (!forwardPaths.isEmpty() && ui->currentPath->text() != forwardPaths.last()) {
        backPaths.append(ui->currentPath->text()); // Сохраняем текущий путь для возможности вернуться назад

        QString forwardPath = forwardPaths.takeFirst();
        fileModel->setRootPath(forwardPath);
        ui->listView->setRootIndex(fileModel->index(forwardPath));
        ui->currentPath->setText(forwardPath);
    }
}

void MainWindow::connectButtons()
{
    // Кнопки окна приложения
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->minimizeButton, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(ui->maximizeButton, SIGNAL(clicked()), this, SLOT(onButtonMaximize()));

    connect(ui->upButton, SIGNAL(clicked()), this, SLOT(onUpButton()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(onBackButton()));
    connect(ui->forwardButton, SIGNAL(clicked()), this, SLOT(onForwardButton()));
}
