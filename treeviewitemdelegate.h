#ifndef TREEVIEWITEMDELEGATE_H
#define TREEVIEWITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QPainter>
#include <QLineEdit>

class TreeViewItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TreeViewItemDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TREEVIEWITEMDELEGATE_H
