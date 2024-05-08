#include "titlebar.h"
#include "mainwindow.h"

TitleBar::TitleBar(QWidget *parent) : QFrame(parent)
{
    isDragging = false;
    setMouseTracking(true);
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (qobject_cast<QPushButton*>(childAt(event->pos())) == nullptr)
        {
            dragPosition = event->globalPosition().toPoint() - window()->pos();
            isDragging = true;
        }
    }
    QFrame::mousePressEvent(event);
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging) {
        if (window()->isMaximized()) {
            //MainWindow *mainWindow = qobject_cast<MainWindow*>(window());
            QIcon icon;
            icon.addFile(":/icons/fullscreen_icon.svg", QSize(18, 18));
            //ui->maximizeButton->setIcon(icon);
            findChild<QPushButton*>("maximizeButton")->setIcon(icon);
            //ui->window
            window()->findChild<QFrame*>("window")->setStyleSheet("QFrame {background-color: rgb(28, 31, 41); color: white; border: 1px solid rgb(47, 50, 60); border-radius: 10px;}");
            double windowWidth = window()->width();
            window()->showNormal();
            double offset = dragPosition.x() / windowWidth * window()->width();
            if (offset > window()->width() - 109) { // 109 - Ширина правой части заголовка (кнопки закрыть, свернуть, развернуть на весь экран)
                offset = window()->width() - 109;
            }
            window()->move(event->globalPosition().toPoint().x() - offset, event->globalPosition().toPoint().y() - dragPosition.y());
            dragPosition = event->globalPosition().toPoint() - window()->pos();
        }
        window()->move(event->globalPosition().toPoint() - dragPosition);
    }
    QFrame::mouseMoveEvent(event);
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (isDragging) {
        isDragging = false;
    }
    QFrame::mouseReleaseEvent(event);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        MainWindow *mainWindow = qobject_cast<MainWindow*>(window());
        QIcon icon;
        if (mainWindow->isMaximized()) {
            mainWindow->showNormal();
            icon.addFile(":/icons/fullscreen_icon.svg", QSize(18, 18));
            findChild<QPushButton*>("maximizeButton")->setIcon(icon);
            parentWidget()->setStyleSheet("QFrame {background-color: rgb(28, 31, 41); color: white; border: 1px solid rgb(47, 50, 60); border-radius: 10px;}");
        } else {
            mainWindow->showMaximized();
            icon.addFile(":/icons/fullscreen_exit_icon.svg", QSize(18, 18));
            findChild<QPushButton*>("maximizeButton")->setIcon(icon);
            parentWidget()->setStyleSheet("QFrame {background-color: rgb(28, 31, 41); color: white;}");
        }
    }
    QFrame::mouseDoubleClickEvent(event);
}

