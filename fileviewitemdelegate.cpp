#include "fileviewitemdelegate.h"

FileViewItemDelegate::FileViewItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    elementWidth = 80;
    iconSizeIconMode = 64;
    iconSizeListMode = 24;
    textWidth = 72;
    fileIconOffset = 14;
    textOffsetListMode = 3;
    roundingRadius = 5;
}

void FileViewItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        QListView *listView = qobject_cast<QListView*>(parent());
        QTreeView *treeView = qobject_cast<QTreeView*>(parent());
        if (listView) {
            QString filePath = index.data(QFileSystemModel::FilePathRole).toString();
            QFileInfo fileInfo(filePath);
            QBrush backgroundBrush = Qt::transparent;
            if (option.state & QStyle::State_Selected) {
                backgroundBrush = QColor(77, 80, 90);
            } else if (option.state & QStyle::State_MouseOver) {
                backgroundBrush = QColor(57, 60, 70);
            }
            painter->setPen(Qt::NoPen);
            painter->setBrush(backgroundBrush);
            painter->drawRoundedRect(option.rect, roundingRadius, roundingRadius);
            if (fileInfo.isRoot()) {

                QIcon icon(":/icons/disk.svg");
                icon.paint(painter, QRect(option.rect.x() + (option.rect.width() - iconSizeIconMode) / 2, option.rect.y(), iconSizeIconMode, iconSizeIconMode), Qt::AlignHCenter | Qt::AlignTop);

                painter->setPen(Qt::white);
                QString text = index.data(Qt::DisplayRole).toString();

                QTextOption textOption;
                textOption.setAlignment(Qt::AlignHCenter);
                textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

                painter->drawText(QRect(option.rect.x() + (option.rect.width() - textWidth) / 2, option.rect.y() + iconSizeIconMode, textWidth, option.rect.height()), text, textOption);
            } else if (fileInfo.isDir()) {

                QIcon icon(":/icons/folder.svg");
                icon.paint(painter, QRect(option.rect.x() + (option.rect.width() - iconSizeIconMode) / 2, option.rect.y(), iconSizeIconMode, iconSizeIconMode), Qt::AlignHCenter | Qt::AlignTop);

                painter->setPen(Qt::white);
                QString text = index.data(Qt::DisplayRole).toString();

                QTextOption textOption;
                textOption.setAlignment(Qt::AlignHCenter);
                textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

                painter->drawText(QRect(option.rect.x() + (option.rect.width() - textWidth) / 2, option.rect.y() + iconSizeIconMode, textWidth, option.rect.height()), text, textOption);
            } else {

                QIcon icon = QFileIconProvider().icon(fileInfo);
                icon.paint(painter, QRect(option.rect.x() + (option.rect.width() - iconSizeIconMode) / 2, option.rect.y() + fileIconOffset, iconSizeIconMode, iconSizeIconMode), Qt::AlignHCenter | Qt::AlignTop);

                painter->setPen(Qt::white);
                QString text = index.data(Qt::DisplayRole).toString();

                QTextOption textOption;
                textOption.setAlignment(Qt::AlignHCenter);
                textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

                painter->drawText(QRect(option.rect.x() + (option.rect.width() - textWidth) / 2, option.rect.y() + iconSizeIconMode, textWidth, option.rect.height()), text, textOption);
            }
        } else if (treeView) {
            QString filePath = index.data(QFileSystemModel::FilePathRole).toString();
            QFileInfo fileInfo(filePath);
            QBrush backgroundBrush = Qt::transparent;
            if (option.state & QStyle::State_Selected) {
                backgroundBrush = QColor(77, 80, 90);
            } else if (option.state & QStyle::State_MouseOver) {
                backgroundBrush = QColor(57, 60, 70);
            }
            painter->setPen(Qt::NoPen);
            painter->setBrush(backgroundBrush);
            painter->drawRect(option.rect);
            painter->setPen(Qt::white);
            if (fileInfo.isRoot()) {
                switch (index.column()) {
                    case 0: {
                        QIcon icon(":/icons/disk.svg");
                        icon.paint(painter, QRect(option.rect.x(), option.rect.y(), iconSizeListMode, iconSizeListMode), Qt::AlignLeft | Qt::AlignVCenter);
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(option.rect.adjusted(iconSizeListMode, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
                        break;
                    }
                    case 1: {
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(option.rect.adjusted(5, 0, 0, 0), Qt::AlignRight | Qt::AlignVCenter, text);
                        break;
                    }
                    case 2: {
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(option.rect.adjusted(5, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
                        break;
                    }
                    case 3: {
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(option.rect.adjusted(5, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
                        break;
                    }
                }
            } else if (fileInfo.isDir()) {
                switch (index.column()) {
                    case 0: {
                        QIcon icon(":/icons/folder.svg");
                        icon.paint(painter, QRect(option.rect.x(), option.rect.y(), iconSizeListMode, iconSizeListMode), Qt::AlignLeft | Qt::AlignVCenter);
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(option.rect.adjusted(iconSizeListMode + textOffsetListMode, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
                        break;
                    }
                    case 1: {
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(option.rect.adjusted(5, 0, 0, 0), Qt::AlignRight | Qt::AlignVCenter, text);
                        break;
                    }
                    case 2: {
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(option.rect.adjusted(5, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
                        break;
                    }
                    case 3: {
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(option.rect.adjusted(5, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
                        break;
                    }
                }
            } else {
                switch (index.column()) {
                    case 0: {
                        QIcon icon = QFileIconProvider().icon(fileInfo);
                        icon.paint(painter, QRect(option.rect.x() + 4, option.rect.y() + 4, 16, 16), Qt::AlignLeft | Qt::AlignVCenter);
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(option.rect.adjusted(iconSizeListMode + textOffsetListMode, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
                        break;
                    }
                    case 1: {
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(option.rect.adjusted(5, 0, 0, 0), Qt::AlignRight | Qt::AlignVCenter, text);
                        break;
                    }
                    case 2: {
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(option.rect.adjusted(5, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
                        break;
                    }
                    case 3: {
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(option.rect.adjusted(5, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
                        break;
                    }
                }
            }
        }
    }
}

QSize FileViewItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QListView *listView = qobject_cast<QListView*>(parent());
    QTreeView *treeView = qobject_cast<QTreeView*>(parent());
    if (listView) {
        // Получаем данные для отображения элемента
        QString text = index.data(Qt::DisplayRole).toString();

        // Задаем параметры отображения текста
        QTextOption textOption;
        textOption.setAlignment(Qt::AlignHCenter);
        textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

        // Создаем документ с необходимыми параметрами для определения высоты текста
        QTextDocument document;
        document.setDefaultTextOption(textOption);
        document.setPageSize(QSize(elementWidth, INT_MAX));
        document.setPlainText(text);

        return QSize(elementWidth, iconSizeIconMode + document.size().height());
    } else if (treeView) {
        return QSize(option.rect.width(), 24);
    }
    return QStyledItemDelegate::sizeHint(option, index);
}