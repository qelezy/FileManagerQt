#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QStackedWidget>
#include <QMenu>
#include <QListView>
#include <QTreeView>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QHeaderView>

class StackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    StackedWidget(QWidget *parent = nullptr);
    QListView *listView;
    QTreeView *treeView;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    QMenu *contextMenu;
};

#endif // STACKEDWIDGET_H
