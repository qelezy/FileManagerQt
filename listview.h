#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QListView>
#include <QMenu>
#include <QContextMenuEvent>

class ListView : public QListView
{
    Q_OBJECT
public:
    ListView(QWidget *parent = nullptr);
    QMenu *contextMenu;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

};

#endif // LISTVIEW_H
