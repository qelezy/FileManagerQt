#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QButtonGroup>
#include <QStandardPaths>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButtonMaximize();
    void onDirViewItem(QModelIndex index);
    void currentPathChanged();
    void onFileViewItemDoubleClicked(QModelIndex index);

    void onUpButton();
    void onBackButton();
    void onForwardButton();

    void onFastMenuButton();

private:
    Ui::MainWindow *ui;

    QFileSystemModel *dirModel, *fileModel;
    QString currentPath;
    QList<QString> backPaths, forwardPaths;
    QButtonGroup *buttonGroup;

    void connectButtons();
};
#endif // MAINWINDOW_H
