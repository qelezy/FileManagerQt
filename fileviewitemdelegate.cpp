#include "fileviewitemdelegate.h"

#ifdef Q_OS_WIN
#include <Windows.h>
#include <shellapi.h>
#elif defined(Q_OS_MAC)
#include <Cocoa/Cocoa.h>
#endif

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
            painter->setRenderHint(QPainter::Antialiasing);
            QBrush backgroundBrush = Qt::transparent;
            if (option.state & QStyle::State_Selected) {
                backgroundBrush = QColor(77, 80, 90);
            } else if (option.state & QStyle::State_MouseOver) {
                backgroundBrush = QColor(57, 60, 70);
            }
            painter->setPen(Qt::NoPen);
            painter->setBrush(backgroundBrush);
            painter->drawRoundedRect(QRect(option.rect.x() + 1, option.rect.y() + 1, option.rect.width() - 1, option.rect.height() - 1), roundingRadius, roundingRadius);
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
                QPixmap pixmap;
                #ifdef Q_OS_WIN
                SHFILEINFO shFileInfo;
                memset(&shFileInfo, 0, sizeof(SHFILEINFO));

                // Получаем иконку через SHGetFileInfo
                SHGetFileInfo(filePath.toStdWString().c_str(),
                              0,
                              &shFileInfo,
                              sizeof(SHFILEINFO),
                              SHGFI_ICON | SHGFI_LARGEICON | SHGFI_USEFILEATTRIBUTES);
                if (shFileInfo.hIcon) {
                    pixmap = QPixmap::fromImage(QImage::fromHICON(shFileInfo.hIcon));
                    DestroyIcon(shFileInfo.hIcon);
                }
                #elif defined (Q_OS_MAC)
                NSString *path = [NSString stringWithUTF8String:fileInfo.absoluteFilePath().toUtf8().constData()];
                NSString *extension = [path pathExtension];
                NSImage *iconImage = [[NSWorkspace sharedWorkspace] iconForFileType:extension];

                if (iconImage) {
                    QImage qImage(iconImage.size.width, iconImage.size.height, QImage::Format_ARGB32);
                    [iconImage lockFocus];
                    NSBitmapImageRep *bitmap = [[NSBitmapImageRep alloc] initWithFocusedViewRect:NSMakeRect(0, 0, iconImage.size.width, iconImage.size.height)];
                    [iconImage unlockFocus];
                    qImage = QImage(bitmap.bitmapData(), bitmap.pixelsWide(), bitmap.pixelsHigh(), bitmap.bytesPerRow(), QImage::Format_ARGB32);
                    delete bitmap;
                    pixmap = QPixmap::fromImage(qImage));
                }
                #endif
                QIcon icon(pixmap);
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
            painter->setRenderHint(QPainter::Antialiasing);
            QBrush backgroundBrush = Qt::transparent;
            if (option.state & QStyle::State_Selected) {
                backgroundBrush = QColor(77, 80, 90);
            } else if (option.state & QStyle::State_MouseOver) {
                backgroundBrush = QColor(57, 60, 70);
            }
            painter->setPen(Qt::NoPen);
            painter->setBrush(backgroundBrush);
            painter->drawRect(QRect(option.rect.x(), option.rect.y() + 1, option.rect.width() + 1, option.rect.height() - 2));
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
                        QPixmap pixmap;
                        #ifdef Q_OS_WIN
                        SHFILEINFO shFileInfo;
                        memset(&shFileInfo, 0, sizeof(SHFILEINFO));

                        // Получаем иконку через SHGetFileInfo
                        SHGetFileInfo(filePath.toStdWString().c_str(),
                                      0,
                                      &shFileInfo,
                                      sizeof(SHFILEINFO),
                                      SHGFI_ICON | SHGFI_LARGEICON | SHGFI_USEFILEATTRIBUTES);
                        if (shFileInfo.hIcon) {
                            pixmap = QPixmap::fromImage(QImage::fromHICON(shFileInfo.hIcon));
                            DestroyIcon(shFileInfo.hIcon);
                        }
                        #elif defined (Q_OS_MAC)
                        NSString *path = [NSString stringWithUTF8String:fileInfo.absoluteFilePath().toUtf8().constData()];
                        NSString *extension = [path pathExtension];
                        NSImage *iconImage = [[NSWorkspace sharedWorkspace] iconForFileType:extension];

                        if (iconImage) {
                            QImage qImage(iconImage.size.width, iconImage.size.height, QImage::Format_ARGB32);
                            [iconImage lockFocus];
                            NSBitmapImageRep *bitmap = [[NSBitmapImageRep alloc] initWithFocusedViewRect:NSMakeRect(0, 0, iconImage.size.width, iconImage.size.height)];
                            [iconImage unlockFocus];
                            qImage = QImage(bitmap.bitmapData(), bitmap.pixelsWide(), bitmap.pixelsHigh(), bitmap.bytesPerRow(), QImage::Format_ARGB32);
                            delete bitmap;
                            pixmap = QPixmap::fromImage(qImage));
                        }
                        #endif
                        QIcon icon(pixmap);
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

QWidget *FileViewItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    QListView *listView = qobject_cast<QListView*>(this->parent());
    QTreeView *treeView = qobject_cast<QTreeView*>(this->parent());

    QTextEdit * editor = new QTextEdit(parent);
    if (listView) {
        QTextOption textOption;
        textOption.setAlignment(Qt::AlignHCenter);
        textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

        editor->document()->setDefaultTextOption(textOption);
        editor->document()->setPageSize(QSize(elementWidth, INT_MAX));
        editor->setStyleSheet("QTextEdit { border-radius: 5px; selection-background-color: rgb(150, 60, 94); border: 1px solid white; }");

    } else if (treeView) {
        QTextOption textOption;
        textOption.setAlignment(Qt::AlignLeft);
        textOption.setWrapMode(QTextOption::NoWrap);
        editor->document()->setDefaultTextOption(textOption);
        editor->setStyleSheet("QTextEdit { border-radius: 0px; selection-background-color: rgb(150, 60, 94); border: 1px solid white; }");

    }
    editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    editor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    editor->installEventFilter(const_cast<FileViewItemDelegate*>(this));

    return editor;
}

void FileViewItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString data = index.model()->data(index).toString();

    QTextEdit * textEdit = qobject_cast<QTextEdit * >(editor);
    textEdit->setText(data);
    int dotIndex = data.lastIndexOf('.');
    if (dotIndex == -1) {
        textEdit->selectAll();
    } else {
        QTextCursor cursor = textEdit->textCursor();
        cursor.setPosition(0);
        cursor.setPosition(dotIndex, QTextCursor::KeepAnchor);
        textEdit->setTextCursor(cursor);
    }
}

void FileViewItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QTextEdit * textEdit = qobject_cast<QTextEdit * >(editor);
    model->setData(index, textEdit->toPlainText());
}

void FileViewItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    QListView *listView = qobject_cast<QListView*>(this->parent());
    QTreeView *treeView = qobject_cast<QTreeView*>(this->parent());

    QRect rect = option.rect;
    if (listView) {
        rect.setY(option.rect.y() + iconSizeIconMode - 5);
        rect.setWidth(option.rect.width() + 1);
    } else if (treeView) {
        rect.setX(option.rect.x() + iconSizeListMode);
    }

    editor->setGeometry(rect);
}

bool FileViewItemDelegate::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            emit commitData(qobject_cast<QWidget*>(obj));
            emit closeEditor(qobject_cast<QWidget*>(obj));
            return true;
        }
    }
    return QStyledItemDelegate::eventFilter(obj, event);
}
