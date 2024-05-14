#include "listviewitemdelegate.h"

ListViewItemDelegate::ListViewItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    elementWidth = 80;
    iconSizeIconMode = 64;
    iconSizeListMode = 24;
    textWidth = 72;
    fileIconOffset = 14;
    textOffsetListMode = 3;
    roundingRadius = 5;
}

void ListViewItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        QListView *listView = qobject_cast<QListView*>(parent());
        if (listView) {
            QString filePath = index.data(QFileSystemModel::FilePathRole).toString();
            QFileInfo fileInfo(filePath);
            switch (listView->viewMode()) {
                case QListView::ListMode: {
                    QBrush backgroundBrush = Qt::transparent;
                    if (option.state & QStyle::State_Selected) {
                        backgroundBrush = QColor(77, 80, 90);
                    } else if (option.state & QStyle::State_MouseOver) {
                        backgroundBrush = QColor(57, 60, 70);
                    }
                    painter->setPen(Qt::NoPen);
                    painter->setBrush(backgroundBrush);
                    painter->drawRoundedRect(QRect(option.rect.x(), option.rect.y(), option.rect.width(), iconSizeListMode), roundingRadius, roundingRadius);
                    if (fileInfo.isRoot()) {
                        QIcon icon(":/icons/disk.svg");
                        icon.paint(painter, option.rect, Qt::AlignLeft | Qt::AlignVCenter);

                        painter->setPen(Qt::white);
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(QRect(option.rect.x() + iconSizeListMode + textOffsetListMode, option.rect.y(), option.rect.width(), iconSizeListMode), Qt::AlignLeft | Qt::AlignVCenter, text);
                    } else if (fileInfo.isDir()) {
                        QIcon icon(":/icons/folder.svg");
                        icon.paint(painter, QRect(option.rect.x(), option.rect.y(), option.rect.width(), iconSizeListMode), Qt::AlignLeft | Qt::AlignVCenter);

                        painter->setPen(Qt::white);
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(QRect(option.rect.x() + iconSizeListMode + textOffsetListMode, option.rect.y(), option.rect.width(), iconSizeListMode), Qt::AlignLeft | Qt::AlignVCenter, text);
                    } else {
                        QIcon icon = QFileIconProvider().icon(fileInfo);
                        icon.paint(painter, QRect(option.rect.x() + 4, option.rect.y() + 4, 16, 16), Qt::AlignLeft | Qt::AlignVCenter);

                        painter->setPen(Qt::white);
                        QString text = index.data(Qt::DisplayRole).toString();
                        painter->drawText(QRect(option.rect.x() + iconSizeListMode + textOffsetListMode - 1, option.rect.y(), option.rect.width(), iconSizeListMode), Qt::AlignLeft | Qt::AlignVCenter, text);
                    }
                    break;
                }
                case QListView::IconMode: {
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
                    break;
                }
            }
        }
    }
}

QSize ListViewItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QListView *listView = qobject_cast<QListView*>(parent());
    if (listView) {
        switch(listView->viewMode()) {
            case QListView::ListMode:
                return QSize(option.rect.width(), iconSizeListMode);
            case QListView::IconMode: {
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
            }
        }
    }
    return QSize();
}
