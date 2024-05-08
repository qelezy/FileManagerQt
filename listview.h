#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QListView>

class ListView : public QListView
{
public:
    ListView(QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // LISTVIEW_H
