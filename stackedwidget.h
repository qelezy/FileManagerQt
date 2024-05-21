#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QStackedWidget>
#include <QMenu>
#include <QListView>
#include <QTreeView>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QHeaderView>
#include <QShortcut>

class StackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    StackedWidget(QWidget *parent = nullptr);
    QListView *listView;
    QTreeView *treeView;
    QMenu *folderMenu, *selectedItemMenu;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

signals:
    void createFolderSignal();
    void createFileSignal();
    void pasteSignal();
    void propertiesSignal();
    void copySignal();
    void cutSignal();
    void deleteSignal();

private:
    void createMenus();

};

#endif // STACKEDWIDGET_H
