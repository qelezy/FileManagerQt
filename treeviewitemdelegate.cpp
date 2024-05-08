#include "treeviewitemdelegate.h"

TreeViewItemDelegate::TreeViewItemDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void TreeViewItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        QString filePath = index.data(QFileSystemModel::FilePathRole).toString();
        QFileInfo fileInfo(filePath);
        if (fileInfo.isRoot()) {
            QIcon icon(":/icons/disk.svg");
            QRect iconRect = option.rect;
            QSize iconSize = icon.actualSize(iconRect.size());
            icon.paint(painter, iconRect, Qt::AlignLeft);

            // Отображение текста элемента после иконки
            QString text = index.data(Qt::DisplayRole).toString();
            QRect textRect = option.rect.adjusted(iconSize.width() + 3, 0, 0, 0);
            painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
        } else if (fileInfo.isDir()) {
            QIcon icon(":/icons/folder.svg");
            QRect iconRect = option.rect;
            QSize iconSize = icon.actualSize(iconRect.size());
            icon.paint(painter, iconRect, Qt::AlignLeft);

            // Отображение текста элемента после иконки
            QString text = index.data(Qt::DisplayRole).toString();
            QRect textRect = option.rect.adjusted(iconSize.width() + 3, 0, 0, 0);
            painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
        } else {
            QStyledItemDelegate::paint(painter, option, index);
        }
    }
}

QSize TreeViewItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(28);
    return size;
}
