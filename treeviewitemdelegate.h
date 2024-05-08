#ifndef TREEVIEWITEMDELEGATE_H
#define TREEVIEWITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QPainter>

class TreeViewItemDelegate : public QStyledItemDelegate
{
public:
    TreeViewItemDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TREEVIEWITEMDELEGATE_H
