#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

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

private:
    Ui::MainWindow *ui;

    QFileSystemModel *dirModel, *fileModel;
    QString currentPath;

    void connectButtons();
};
#endif // MAINWINDOW_H
