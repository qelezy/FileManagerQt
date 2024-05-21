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
#include <QTextEdit>
#include <QKeyEvent>
#include <QApplication>

class FileViewItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    FileViewItemDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    int elementWidth, iconSizeIconMode, iconSizeListMode, textWidth, fileIconOffset, textOffsetListMode, roundingRadius;
};

#endif // FILEVIEWITEMDELEGATE_H
