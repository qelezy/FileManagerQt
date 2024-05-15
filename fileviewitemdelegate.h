#ifndef FILEVIEWITEMDELEGATE_H
#define FILEVIEWITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QPainter>
#include <QFileIconProvider>
#include <QTextDocument>
#include <QListView>
#include <QTreeView>

class FileViewItemDelegate : public QStyledItemDelegate
{
public:
    FileViewItemDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    int elementWidth, iconSizeIconMode, iconSizeListMode, textWidth, fileIconOffset, textOffsetListMode, roundingRadius;
};

#endif // FILEVIEWITEMDELEGATE_H
