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
    //ui->listView->setTextElideMode(Qt::ElideNone);

    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(onTreeViewItem(QModelIndex)));

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
}

void MainWindow::connectButtons()
{
    // Кнопки окна приложения
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->minimizeButton, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(ui->maximizeButton, SIGNAL(clicked()), this, SLOT(onButtonMaximize()));
}
