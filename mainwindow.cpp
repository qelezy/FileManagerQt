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
    ui->stackedWidget->listView->setCurrentIndex(QModelIndex());

    ui->stackedWidget->treeView->setModel(fileModel);
    ui->stackedWidget->treeView->setCurrentIndex(QModelIndex());

    ui->stackedWidget->listView->setItemDelegate(new FileViewItemDelegate(ui->stackedWidget->listView));
    ui->stackedWidget->treeView->setItemDelegate(new FileViewItemDelegate(ui->stackedWidget->treeView));

    ui->stackedWidget->treeView->setEditTriggers(QAbstractItemView::EditKeyPressed);
    ui->stackedWidget->listView->setEditTriggers(QAbstractItemView::EditKeyPressed);

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

    connect(ui->stackedWidget->folderMenu->actions().last(), SIGNAL(triggered()), this, SLOT(onProperties()));
    connect(ui->stackedWidget->selectedItemMenu->actions().last(), SIGNAL(triggered()), this, SLOT(onProperties()));
    connect(ui->stackedWidget, SIGNAL(createFolderSignal()), this, SLOT(onCreateFolder()));
    connect(ui->stackedWidget, SIGNAL(createFileSignal()), this, SLOT(onCreateFile()));
    connect(ui->stackedWidget, SIGNAL(copySignal()), this, SLOT(onCopy()));
    connect(ui->stackedWidget, SIGNAL(cutSignal()), this, SLOT(onCut()));
    connect(ui->stackedWidget, SIGNAL(pasteSignal()), this, SLOT(onPaste()));
    connect(ui->stackedWidget, &StackedWidget::deleteSignal, this, [=] {
        removeFilesAndDirectoriesRecursively();
    });

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
    backPaths.append(fileModel->filePath(ui->stackedWidget->listView->rootIndex()));
    forwardPaths.clear();

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

void MainWindow::onCreateFolder()
{
    QString folderName = "", prefix = "Новая папка";
    QModelIndex newFolderIndex;
    if (ui->currentPath->text().isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Невозможно добавить папку в корневой каталог");
        return;
    }
    int i = 0;
    do {
        if (i) folderName = prefix + " " + QString::number(i);
        else folderName = prefix;
        newFolderIndex = fileModel->mkdir(fileModel->index(ui->currentPath->text()), folderName);
        i++;

    } while(!newFolderIndex.isValid());

    if (ui->stackedWidget->currentWidget() == ui->stackedWidget->listView) {
        ui->stackedWidget->listView->edit(newFolderIndex);
    } else if (ui->stackedWidget->currentWidget() == ui->stackedWidget->treeView) {
        ui->stackedWidget->treeView->edit(newFolderIndex);
    }
}

void MainWindow::onCreateFile()
{
    QString fileName = "", prefix = "Новый файл";
    QString curDir = ui->currentPath->text();
    QFile newFile;
    if (curDir.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Невозможно добавить файл в корневой каталог");
        return;
    }
    // Генерируем уникальное стандартное имя файла
    int i = 0;
    do {
        if (i)
            fileName = curDir + "/" + prefix + " " + QString::number(i);
        else
            fileName = curDir + "/" + prefix;

        newFile.setFileName(fileName);
        i++;

    } while(newFile.exists());

    if (newFile.open(QIODeviceBase::WriteOnly)) {
        newFile.close();
        if (ui->stackedWidget->currentWidget() == ui->stackedWidget->listView) {
            ui->stackedWidget->listView->edit(fileModel->index(fileName));
        } else if (ui->stackedWidget->currentWidget() == ui->stackedWidget->treeView) {
            ui->stackedWidget->treeView->edit(fileModel->index(fileName));
        }
    }
}

void MainWindow::onCopy()
{
    if (ui->stackedWidget->currentWidget() == ui->stackedWidget->listView) {
        itemsToCopy = ui->stackedWidget->listView->selectionModel()->selectedIndexes();
        itemsToMove.clear();
    } else if (ui->stackedWidget->currentWidget() == ui->stackedWidget->treeView) {
        itemsToCopy = ui->stackedWidget->treeView->selectionModel()->selectedIndexes();
        itemsToMove.clear();
    }
}

void MainWindow::onCut()
{
    if (ui->stackedWidget->currentWidget() == ui->stackedWidget->listView) {
        itemsToMove = ui->stackedWidget->listView->selectionModel()->selectedIndexes();
        itemsToCopy.clear();
    } else if (ui->stackedWidget->currentWidget() == ui->stackedWidget->treeView) {
        itemsToMove = ui->stackedWidget->treeView->selectionModel()->selectedIndexes();
        itemsToCopy.clear();
    }
}

void MainWindow::onPaste()
{
    QFileInfo itemInfo;

    // Нужно определить каталог назначения (текущий или выделенный)
    QString destDir = ui->currentPath->text();

    for (QModelIndex& index : itemsToCopy) {
        QString path = fileModel->filePath(index);
        itemInfo.setFile(path);

        if (itemInfo.isFile()) {

            QFile::copy(path, destDir + "/" + itemInfo.fileName());

        } else if (itemInfo.isDir()) {
            copyOrMoveDirectorySubtree(path, destDir, false, false);
        }
    }

    for (QModelIndex& index : itemsToMove) {
        QString path = fileModel->filePath(index);
        itemInfo.setFile(path);

        if (itemInfo.isFile()) {

            QFile::copy(path, ui->currentPath->text() + "/" + itemInfo.fileName());
            QFile::remove(path);

        } else if (itemInfo.isDir()) {
            copyOrMoveDirectorySubtree(path, ui->currentPath->text(), true, true);
        }
    }
}

void MainWindow::onProperties()
{
    #ifdef Q_OS_WIN
    QModelIndex index;
    if (ui->stackedWidget->currentWidget() == ui->stackedWidget->listView) {
        if (ui->stackedWidget->listView->selectionModel()->hasSelection()) {
            index = ui->stackedWidget->listView->currentIndex();
        } else {
            index = fileModel->index(ui->currentPath->text());
        }
    } else if (ui->stackedWidget->currentWidget() == ui->stackedWidget->treeView) {
        if (ui->stackedWidget->treeView->selectionModel()->hasSelection()) {
            index = ui->stackedWidget->treeView->currentIndex();
        } else {
            index = fileModel->index(ui->currentPath->text());
        }
    }
    std::wstring filePath;
    if (index.isValid()) {
        filePath = fileModel->filePath(index).toStdWString();
    } else {
        if (ui->currentPath->text().isEmpty()) {
            if (!ShellExecute(0, 0, L"ms-settings:about", 0, 0, SW_SHOW)) {
                MessageBox(nullptr, L"Не удалось открыть окно свойств системы", L"Ошибка", MB_ICONERROR);
            }
            return;
        }
        filePath = ui->currentPath->text().toStdWString();
    }
    SHELLEXECUTEINFO sei = { sizeof(sei) };
    sei.fMask = SEE_MASK_INVOKEIDLIST;
    sei.lpVerb = L"properties";
    sei.lpFile = filePath.c_str();
    sei.nShow = SW_SHOW;
    sei.hwnd = nullptr;
    if (!ShellExecuteEx(&sei))
    {
        MessageBox(nullptr, L"Не удалось открыть окно свойств", L"Ошибка", MB_ICONERROR);
    }
    #elif defined(Q_OS_MAC)
    QModelIndex index;
    if (ui->stackedWidget->currentWidget() == ui->stackedWidget->listView) {
        index = ui->stackedWidget->listView->currentIndex();
    } else if (ui->stackedWidget->currentWidget() == ui->stackedWidget->treeView) {
        index = ui->stackedWidget->treeView->currentIndex();
    }
    QString filePath
    if (index.isValid()) {
        filePath = fileModel->filePath(index);
    } else {
        if (ui->currentPath->text().isEmpty()) {
            QProcess::startDetached("open", QStringList() << "-b" << "com.apple.systempreferences");
            return;
        }
        filePath = ui->currentPath->text();
    }
    // Формируем команду AppleScript для открытия окна свойств
    QString script = QString(
                         "osascript -e 'tell application \"Finder\" to open information window of (POSIX file \"%1\" as alias)'"
                         ).arg(filePath);

    QProcess::execute(script);
    #endif
}

void MainWindow::copyOrMoveDirectorySubtree(const QString & from, const QString & to, bool isOverwrite, bool isMove)
{
    QDir fromDir(from);
    QDir toDir(to);

    const auto sourcePathLength = fromDir.absolutePath().length();

    toDir.mkdir(fromDir.dirName());
    toDir.cd(fromDir.dirName());

    QDirIterator it(from, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        const QFileInfo fileInfo = it.nextFileInfo();


        if (fileInfo.fileName() == "." || fileInfo.fileName() == "..") {
            continue;
        }
        // canonicalPath -> возвращает путь без символьных ссылок.
        // Мы копируем файл на который ссылается символическая ссылка, а не ссылку и соответственно с другой стороны тоже надо вставить файл в каталог, на который ссылается ссылка, т.е. разрешить ссылку.
        QString subPath = fileInfo.absoluteFilePath().mid(sourcePathLength);
        const QString curDirName = toDir.dirName();
        // Решаем проблему рекурсивного копирования в случае когда from == to. Проблема: в toDir создается каталог с тем же именем что и в sourcePath и обновленное содержимое from (в котором создан каталог toDir) копируется в каталог toDir и в результате получаем в каталоге toDir каталог toDir ))
        if (curDirName == subPath.mid(1)) {
            subPath = subPath.mid(curDirName.length() + 1);
        }

        const QString newPath = toDir.canonicalPath() + subPath;

        if (fileInfo.isFile()) {

            // Статический метод copy по умолчанию не перезаписывает существующий файл, он просто вернет false.
            if (isOverwrite) {
                QFile::remove(newPath);
            }

            QFile::copy(fileInfo.absoluteFilePath(), newPath);

        } else if (fileInfo.isDir()) {

            toDir.mkpath(newPath);

        }

    }
    // Если мы перемещаем каталог, то мы должны удалить исходный каталог.
    if (isMove) {
        fromDir.removeRecursively();
    }
}

void MainWindow::moveDirectoryContentsToTrashRecursively(const QString &dirPath)
{
    QDir dir(dirPath);
    if (!dir.exists()) return;

    QList<QString> files = dir.entryList(QDir::Files), dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    QFile tmpFile;
    for (const auto& fileName : files) {
        tmpFile.setFileName(dir.absoluteFilePath(fileName));
        tmpFile.moveToTrash();
    }

    for (const auto& dirName : dirs) {
        moveDirectoryContentsToTrashRecursively(dir.absolutePath() + "/" + dirName);
    }

    dir.rmdir(dir.absolutePath());
}

void MainWindow::removeFilesAndDirectoriesRecursively()
{
    QFileInfo info; QFile curFile;
    QModelIndexList indexList;
    if (ui->stackedWidget->currentWidget() == ui->stackedWidget->listView) {
        indexList = ui->stackedWidget->listView->selectionModel()->selectedIndexes();
    } else if (ui->stackedWidget->currentWidget() == ui->stackedWidget->treeView) {
        indexList = ui->stackedWidget->treeView->selectionModel()->selectedIndexes();
    }
    ui->stackedWidget->treeView->selectionModel()->selectedIndexes();
    for (QModelIndex& index : indexList) {
        QString path = fileModel->filePath(index);
        info.setFile(path);

        if (info.isFile()) {
            curFile.setFileName(info.absoluteFilePath());
            curFile.moveToTrash();

        } else if (info.isDir()) {
            moveDirectoryContentsToTrashRecursively(info.absoluteFilePath());
        }
    }
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
