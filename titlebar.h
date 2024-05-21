#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QFrame>
#include <QMouseEvent>
#include <QPushButton>

class TitleBar : public QFrame
{
    Q_OBJECT
public:
    TitleBar(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
private:
    QPoint dragPosition;
    bool isDragging;
};

#endif // TITLEBAR_H
