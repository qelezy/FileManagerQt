#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    TreeView(QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // TREEVIEW_H
