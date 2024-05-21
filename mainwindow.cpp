#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treeviewitemdelegate.h"
#include "fileviewitemdelegate.h"
#include "filesystemmodel.h"

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

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

    fileModel = new FileSystemModel(this);
    fileModel->setReadOnly(false);

    ui->stackedWidget->listView->setModel(fileModel);

    ui->stackedWidget->treeView->setModel(fileModel);

    ui->stackedWidget->listView->setItemDelegate(new FileViewItemDelegate(ui->stackedWidget->listView));
    ui->stackedWidget->treeView->setItemDelegate(new FileViewItemDelegate(ui->stackedWidget->treeView));

    ui->stackedWidget->treeView->setEditTriggers(QAbstractItemView::EditKeyPressed);

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

    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(onDirViewItem(QModelIndex)));

    connect(ui->stackedWidget->listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onFileViewItemDoubleClicked(QModelIndex)));
    connect(ui->stackedWidget->treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onFileViewItemDoubleClicked(QModelIndex)));

    connect(ui->currentPath, SIGNAL(returnPressed()), this, SLOT(currentPathChanged()));

    connect(ui->stackedWidget->contextMenu->actions().last(), SIGNAL(triggered()), this, SLOT(onProperties()));

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

void MainWindow::onDirViewItem(QModelIndex index)
{
    if (buttonGroup->checkedButton()) {
        buttonGroup->checkedButton()->setChecked(false);
        buttonGroup->checkedButton()->setStyleSheet("QPushButton {padding-left: 22px;text-align: left;background-color: rgb(28, 31, 41);color: white;border-radius: 5px;}QPushButton:hover {background-color: rgb(57, 60, 70);}");
    }

    QString path = dirModel->fileInfo(index).absoluteFilePath();
    ui->stackedWidget->listView->setRootIndex(fileModel->setRootPath(path));
    ui->stackedWidget->treeView->setRootIndex(fileModel->setRootPath(path));

    backPaths.append(ui->currentPath->text());
    forwardPaths.clear();

    ui->currentPath->setText(path);
}

void MainWindow::currentPathChanged()
{
    fileModel->setRootPath(ui->currentPath->text());
    ui->stackedWidget->listView->setRootIndex(fileModel->index(ui->currentPath->text()));
    ui->stackedWidget->treeView->setRootIndex(fileModel->index(ui->currentPath->text()));
    ui->treeView->setCurrentIndex(dirModel->index(ui->currentPath->text()));
}

void MainWindow::onFileViewItemDoubleClicked(QModelIndex index)
{
    QString path = fileModel->filePath(index);

    QFileInfo fileInfo(path);
    if (fileInfo.isDir()) {
        fileModel->setRootPath(path);
        ui->stackedWidget->listView->setRootIndex(index);
        ui->stackedWidget->treeView->setRootIndex(fileModel->index(path));

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
        ui->stackedWidget->listView->setRootIndex(fileModel->index(backPath));
        ui->stackedWidget->treeView->setRootIndex(fileModel->index(backPath));
        ui->currentPath->setText(backPath);
    }
}

void MainWindow::onForwardButton()
{
    if (!forwardPaths.isEmpty() && ui->currentPath->text() != forwardPaths.last()) {
        backPaths.append(ui->currentPath->text()); // Сохраняем текущий путь для возможности вернуться назад

        QString forwardPath = forwardPaths.takeFirst();
        fileModel->setRootPath(forwardPath);
        ui->stackedWidget->listView->setRootIndex(fileModel->index(forwardPath));
        ui->stackedWidget->treeView->setRootIndex(fileModel->index(forwardPath));
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
    ui->stackedWidget->listView->setRootIndex(fileModel->index(path));
    ui->stackedWidget->treeView->setRootIndex(fileModel->index(path));

    backPaths.append(ui->currentPath->text());
    forwardPaths.clear();

    ui->currentPath->setText(path);
}

void MainWindow::onProperties()
{
    #ifdef Q_OS_WIN

        SHELLEXECUTEINFO sei = { sizeof(sei) };
        sei.fMask = SEE_MASK_INVOKEIDLIST;
        sei.lpVerb = L"properties";
        std::wstring filePath = ui->currentPath->text().toStdWString();
        sei.lpFile = filePath.c_str();
        sei.nShow = SW_SHOW;
        sei.hwnd = nullptr;

        if (!ShellExecuteEx(&sei))
        {
            MessageBox(nullptr, L"Не удалось открыть окно свойств", L"Ошибка", MB_ICONERROR);
        }

    #elif defined(Q_OS_MAC)
        // Формируем команду AppleScript для открытия окна свойств
        QString script = QString(
                             "osascript -e 'tell application \"Finder\" to open information window of (POSIX file \"%1\" as alias)'"
                             ).arg(filePath);

        QProcess::execute(script);
    #endif
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
