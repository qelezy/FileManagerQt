#include "listviewitemdelegate.h"

ListViewItemDelegate::ListViewItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    elementWidth = 80;
    iconSize = 64;
    textWidth = 72;
    fileIconOffset = 14;
    roundingRadius = 10;
}

void ListViewItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        QString filePath = index.data(QFileSystemModel::FilePathRole).toString();
        QFileInfo fileInfo(filePath);
        if (fileInfo.isDir()) {
            QBrush backgroundBrush = Qt::transparent;
            if (option.state & QStyle::State_Selected) {
                backgroundBrush = QColor(77, 80, 90);
            } else if (option.state & QStyle::State_MouseOver) {
                backgroundBrush = QColor(57, 60, 70);
            }
            painter->setPen(Qt::NoPen);
            painter->setBrush(backgroundBrush);
            painter->drawRoundedRect(option.rect, roundingRadius, roundingRadius);

            QIcon icon(":/icons/folder.svg");
            icon.paint(painter, QRect(option.rect.x() + (option.rect.width() - iconSize) / 2, option.rect.y(), iconSize, iconSize), Qt::AlignHCenter | Qt::AlignTop);

            // Отображение текста элемента под иконкой
            painter->setPen(Qt::white);
            QString text = index.data(Qt::DisplayRole).toString();

            QTextOption textOption;
            textOption.setAlignment(Qt::AlignHCenter);
            textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

            painter->drawText(QRect(option.rect.x() + (option.rect.width() - textWidth) / 2, option.rect.y() + iconSize, textWidth, option.rect.height()), text, textOption);
        } else {
            QBrush backgroundBrush = Qt::transparent;
            if (option.state & QStyle::State_Selected) {
                backgroundBrush = QColor(77, 80, 90);
            } else if (option.state & QStyle::State_MouseOver) {
                backgroundBrush = QColor(57, 60, 70);
            }
            painter->setPen(Qt::NoPen);
            painter->setBrush(backgroundBrush);
            painter->drawRoundedRect(option.rect, roundingRadius, roundingRadius);

            QIcon icon = QFileIconProvider().icon(fileInfo);
            icon.paint(painter, QRect(option.rect.x() + (option.rect.width() - iconSize) / 2, option.rect.y() + fileIconOffset, iconSize, iconSize), Qt::AlignHCenter | Qt::AlignTop);

            painter->setPen(Qt::white);
            QString text = index.data(Qt::DisplayRole).toString();

            QTextOption textOption;
            textOption.setAlignment(Qt::AlignHCenter);
            textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

            painter->drawText(QRect(option.rect.x() + (option.rect.width() - textWidth) / 2, option.rect.y() + iconSize, textWidth, option.rect.height()), text, textOption);
        }
    }
}

QSize ListViewItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);

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

    return QSize(elementWidth, iconSize + document.size().height());
}
