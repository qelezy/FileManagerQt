#ifndef LISTVIEWITEMDELEGATE_H
#define LISTVIEWITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QPainter>
#include <QFileIconProvider>
#include <QTextDocument>
#include <QListView>

class ListViewItemDelegate : public QStyledItemDelegate
{
public:
    ListViewItemDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    int elementWidth, iconSizeIconMode, iconSizeListMode, textWidth, fileIconOffset, textOffsetListMode, roundingRadius;
};

#endif // LISTVIEWITEMDELEGATE_H
