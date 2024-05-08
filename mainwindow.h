#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QDesktopServices>

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
    void onTreeViewItem(QModelIndex index);
    void currentPathChanged();
    void onListViewItemDoubleClicked(QModelIndex index);
    void onUpButton();
    void onBackButton();
    void onForwardButton();

private:
    Ui::MainWindow *ui;

    QFileSystemModel *dirModel, *fileModel;
    QString currentPath;
    QList<QString> backPaths, forwardPaths;

    void connectButtons();
};
#endif // MAINWINDOW_H
