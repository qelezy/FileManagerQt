/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <listview.h>
#include <resizableframe.h>
#include <titlebar.h>
#include <treeview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    ResizableFrame *window;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *titleLayout;
    QLabel *appIcon;
    TitleBar *titleBar;
    QHBoxLayout *horizontalLayout;
    QLabel *appName;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *minimizeButton;
    QPushButton *maximizeButton;
    QPushButton *closeButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *toolbarLayout;
    QPushButton *backButton;
    QPushButton *forwardButton;
    QPushButton *upButton;
    QLineEdit *currentPath;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *desktopButton;
    QPushButton *downloadsButton;
    QPushButton *documentsButton;
    QPushButton *picturesButton;
    QPushButton *musicButton;
    QPushButton *videoButton;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QSpacerItem *verticalSpacer_2;
    TreeView *treeView;
    ListView *listView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        window = new ResizableFrame(centralwidget);
        window->setObjectName("window");
        window->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	background-color: rgb(28, 31, 41);\n"
"	color: white;\n"
"	border: 1px solid rgb(47, 50, 60);\n"
"	border-radius: 10px;\n"
"}"));
        window->setFrameShape(QFrame::StyledPanel);
        window->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(window);
        verticalLayout_3->setSpacing(5);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        titleLayout = new QHBoxLayout();
        titleLayout->setSpacing(5);
        titleLayout->setObjectName("titleLayout");
        titleLayout->setContentsMargins(6, 5, 5, -1);
        appIcon = new QLabel(window);
        appIcon->setObjectName("appIcon");
        appIcon->setMinimumSize(QSize(30, 30));
        appIcon->setMaximumSize(QSize(30, 30));
        appIcon->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	border: none;\n"
"}"));
        appIcon->setPixmap(QPixmap(QString::fromUtf8(":/filemanager.ico")));
        appIcon->setScaledContents(true);

        titleLayout->addWidget(appIcon);

        titleBar = new TitleBar(window);
        titleBar->setObjectName("titleBar");
        titleBar->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	border: none;\n"
"}"));
        titleBar->setFrameShape(QFrame::StyledPanel);
        titleBar->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(titleBar);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        appName = new QLabel(titleBar);
        appName->setObjectName("appName");
        appName->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	border: none;\n"
"}"));

        horizontalLayout->addWidget(appName);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        minimizeButton = new QPushButton(titleBar);
        minimizeButton->setObjectName("minimizeButton");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(minimizeButton->sizePolicy().hasHeightForWidth());
        minimizeButton->setSizePolicy(sizePolicy);
        minimizeButton->setMinimumSize(QSize(32, 32));
        minimizeButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(28, 31, 41);\n"
"	color: white;\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:hover:!pressed {\n"
"	background-color: rgb(47, 50, 60);\n"
"}\n"
"QPushButton:pressed {\n"
"	background-color: rgb(57, 60, 70);\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/remove_icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        minimizeButton->setIcon(icon);
        minimizeButton->setIconSize(QSize(18, 18));

        horizontalLayout->addWidget(minimizeButton);

        maximizeButton = new QPushButton(titleBar);
        maximizeButton->setObjectName("maximizeButton");
        sizePolicy.setHeightForWidth(maximizeButton->sizePolicy().hasHeightForWidth());
        maximizeButton->setSizePolicy(sizePolicy);
        maximizeButton->setMinimumSize(QSize(32, 32));
        maximizeButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(28, 31, 41);\n"
"	color: white;\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:hover:!pressed {\n"
"	background-color: rgb(47, 50, 60);\n"
"}\n"
"QPushButton:pressed {\n"
"	background-color: rgb(57, 60, 70);\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/fullscreen_icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        maximizeButton->setIcon(icon1);
        maximizeButton->setIconSize(QSize(18, 18));

        horizontalLayout->addWidget(maximizeButton);

        closeButton = new QPushButton(titleBar);
        closeButton->setObjectName("closeButton");
        sizePolicy.setHeightForWidth(closeButton->sizePolicy().hasHeightForWidth());
        closeButton->setSizePolicy(sizePolicy);
        closeButton->setMinimumSize(QSize(32, 32));
        closeButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(28, 31, 41);\n"
"	color: white;\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:hover:!pressed {\n"
"	background-color: rgb(190, 26, 26);\n"
"}\n"
"QPushButton:pressed {\n"
"	background-color: rgb(205, 26, 26);\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/close_icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        closeButton->setIcon(icon2);
        closeButton->setIconSize(QSize(18, 18));

        horizontalLayout->addWidget(closeButton);


        titleLayout->addWidget(titleBar);


        verticalLayout_3->addLayout(titleLayout);

        mainLayout = new QVBoxLayout();
        mainLayout->setSpacing(10);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(6, -1, 5, 5);
        toolbarLayout = new QHBoxLayout();
        toolbarLayout->setSpacing(5);
        toolbarLayout->setObjectName("toolbarLayout");
        toolbarLayout->setContentsMargins(0, -1, 0, -1);
        backButton = new QPushButton(window);
        backButton->setObjectName("backButton");
        backButton->setMinimumSize(QSize(32, 32));
        backButton->setMaximumSize(QSize(32, 32));
        backButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(28, 31, 41);\n"
"	color: white;\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:hover:!pressed {\n"
"	background-color: rgb(47, 50, 60);\n"
"}\n"
"QPushButton:pressed {\n"
"	background-color: rgb(57, 60, 70);\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/back_arrow.svg"), QSize(), QIcon::Normal, QIcon::Off);
        backButton->setIcon(icon3);
        backButton->setIconSize(QSize(16, 16));

        toolbarLayout->addWidget(backButton);

        forwardButton = new QPushButton(window);
        forwardButton->setObjectName("forwardButton");
        forwardButton->setMinimumSize(QSize(32, 32));
        forwardButton->setMaximumSize(QSize(32, 32));
        forwardButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(28, 31, 41);\n"
"	color: white;\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:hover:!pressed {\n"
"	background-color: rgb(47, 50, 60);\n"
"}\n"
"QPushButton:pressed {\n"
"	background-color: rgb(57, 60, 70);\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/forward_arrow.svg"), QSize(), QIcon::Normal, QIcon::Off);
        forwardButton->setIcon(icon4);
        forwardButton->setIconSize(QSize(16, 16));

        toolbarLayout->addWidget(forwardButton);

        upButton = new QPushButton(window);
        upButton->setObjectName("upButton");
        upButton->setMinimumSize(QSize(32, 32));
        upButton->setMaximumSize(QSize(32, 32));
        upButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(28, 31, 41);\n"
"	color: white;\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:hover:!pressed {\n"
"	background-color: rgb(47, 50, 60);\n"
"}\n"
"QPushButton:pressed {\n"
"	background-color: rgb(57, 60, 70);\n"
"}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/up_arrow.svg"), QSize(), QIcon::Normal, QIcon::Off);
        upButton->setIcon(icon5);
        upButton->setIconSize(QSize(16, 16));

        toolbarLayout->addWidget(upButton);

        currentPath = new QLineEdit(window);
        currentPath->setObjectName("currentPath");
        currentPath->setMinimumSize(QSize(0, 32));
        currentPath->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"	border: 1px solid rgb(47, 50, 60);\n"
"	border-radius: 5px;\n"
"	background-color: rgb(38, 41, 51);\n"
"	color: white;\n"
"	padding-left: 5px;\n"
"}"));

        toolbarLayout->addWidget(currentPath);


        mainLayout->addLayout(toolbarLayout);

        splitter = new QSplitter(window);
        splitter->setObjectName("splitter");
        splitter->setStyleSheet(QString::fromUtf8("QSplitter {\n"
"	border: none;\n"
"}"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(0);
        splitter->setChildrenCollapsible(true);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        desktopButton = new QPushButton(verticalLayoutWidget);
        desktopButton->setObjectName("desktopButton");
        desktopButton->setMinimumSize(QSize(0, 28));
        desktopButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	padding-left: 22px;\n"
"	text-align: left;\n"
"	background-color: rgb(28, 31, 41);\n"
"	color: white;\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(57, 60, 70);\n"
"}\n"
"QPushButton:checked {\n"
"	background-color: rgb(77, 80, 90);\n"
"}"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/desktop_icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        desktopButton->setIcon(icon6);
        desktopButton->setIconSize(QSize(25, 25));
        desktopButton->setCheckable(true);

        verticalLayout->addWidget(desktopButton);

        downloadsButton = new QPushButton(verticalLayoutWidget);
        downloadsButton->setObjectName("downloadsButton");
        downloadsButton->setMinimumSize(QSize(0, 28));
        downloadsButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	padding-left: 22px;\n"
"	text-align: left;\n"
"	background-color: rgb(28, 31, 41);\n"
"	color: white;\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(57, 60, 70);\n"
"}\n"
"QPushButton:checked {\n"
"	background-color: rgb(77, 80, 90);\n"
"}"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/downloads_icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        downloadsButton->setIcon(icon7);
        downloadsButton->setIconSize(QSize(25, 25));
        downloadsButton->setCheckable(true);

        verticalLayout->addWidget(downloadsButton);

        documentsButton = new QPushButton(verticalLayoutWidget);
        documentsButton->setObjectName("documentsButton");
        documentsButton->setMinimumSize(QSize(0, 28));
        documentsButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	padding-left: 22px;\n"
"	text-align: left;\n"
"	background-color: rgb(28, 31, 41);\n"
"	color: white;\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(57, 60, 70);\n"
"}\n"
"QPushButton:checked {\n"
"	background-color: rgb(77, 80, 90);\n"
"}"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/documents_icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        documentsButton->setIcon(icon8);
        documentsButton->setIconSize(QSize(25, 25));
        documentsButton->setCheckable(true);

        verticalLayout->addWidget(documentsButton);

        picturesButton = new QPushButton(verticalLayoutWidget);
        picturesButton->setObjectName("picturesButton");
        picturesButton->setMinimumSize(QSize(0, 28));
        picturesButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	padding-left: 22px;\n"
"	text-align: left;\n"
"	background-color: rgb(28, 31, 41);\n"
"	color: white;\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(57, 60, 70);\n"
"}\n"
"QPushButton:checked {\n"
"	background-color: rgb(77, 80, 90);\n"
"}"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/pictures_icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        picturesButton->setIcon(icon9);
        picturesButton->setIconSize(QSize(25, 25));
        picturesButton->setCheckable(true);

        verticalLayout->addWidget(picturesButton);

        musicButton = new QPushButton(verticalLayoutWidget);
        musicButton->setObjectName("musicButton");
        musicButton->setMinimumSize(QSize(0, 28));
        musicButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	padding-left: 22px;\n"
"	text-align: left;\n"
"	background-color: rgb(28, 31, 41);\n"
"	color: white;\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(57, 60, 70);\n"
"}\n"
"QPushButton:checked {\n"
"	background-color: rgb(77, 80, 90);\n"
"}"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/music_icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        musicButton->setIcon(icon10);
        musicButton->setIconSize(QSize(25, 25));
        musicButton->setCheckable(true);

        verticalLayout->addWidget(musicButton);

        videoButton = new QPushButton(verticalLayoutWidget);
        videoButton->setObjectName("videoButton");
        videoButton->setMinimumSize(QSize(0, 28));
        videoButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	padding-left: 22px;\n"
"	text-align: left;\n"
"	background-color: rgb(28, 31, 41);\n"
"	color: white;\n"
"	border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(57, 60, 70);\n"
"}\n"
"QPushButton:checked {\n"
"	background-color: rgb(77, 80, 90);\n"
"}"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icons/video_icon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        videoButton->setIcon(icon11);
        videoButton->setIconSize(QSize(25, 25));
        videoButton->setCheckable(true);

        verticalLayout->addWidget(videoButton);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName("line");
        line->setMinimumSize(QSize(0, 1));
        line->setStyleSheet(QString::fromUtf8("background-color: rgb(67, 70, 80);\n"
"border-radius: 1px;\n"
"padding-right: 5px;"));
        line->setFrameShadow(QFrame::Sunken);
        line->setLineWidth(0);
        line->setMidLineWidth(1);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        verticalSpacer_2 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        treeView = new TreeView(verticalLayoutWidget);
        treeView->setObjectName("treeView");
        treeView->setMinimumSize(QSize(0, 0));
        treeView->setStyleSheet(QString::fromUtf8("QTreeView {\n"
"	border: none;\n"
"	border-top-left-radius: 0;\n"
"	border-top-right-radius: 0;\n"
"	border-bottom-left-radius: 10px;\n"
"	border-bottom-right-radius: 0;\n"
"}\n"
"QTreeView::item {\n"
"	border-radius: 5px;\n"
"}\n"
"QTreeView::item:hover {\n"
"	background-color: rgb(57, 60, 70);\n"
"}\n"
"QTreeView::item:selected {\n"
"	background-color: rgb(77, 80, 90);\n"
"}"));
        treeView->header()->setVisible(false);

        verticalLayout->addWidget(treeView);

        splitter->addWidget(verticalLayoutWidget);
        listView = new ListView(splitter);
        listView->setObjectName("listView");
        listView->setMinimumSize(QSize(0, 0));
        listView->setMouseTracking(true);
        listView->setStyleSheet(QString::fromUtf8("QListView {\n"
"	border: 1px solid rgb(47, 50, 60);\n"
"	border-radius: 5px;\n"
"	background-color: rgb(38, 41, 51);\n"
"	padding: 10px;\n"
"}"));
        listView->setIconSize(QSize(0, 0));
        listView->setFlow(QListView::LeftToRight);
        listView->setSpacing(5);
        listView->setWordWrap(true);
        splitter->addWidget(listView);

        mainLayout->addWidget(splitter);

        mainLayout->setStretch(1, 1);

        verticalLayout_3->addLayout(mainLayout);

        verticalLayout_3->setStretch(1, 1);

        gridLayout->addWidget(window, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273\320\276\320\262\321\213\320\271 \320\274\320\265\320\275\320\265\320\264\320\266\320\265\321\200", nullptr));
        appName->setText(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273\320\276\320\262\321\213\320\271 \320\274\320\265\320\275\320\265\320\264\320\266\320\265\321\200", nullptr));
        minimizeButton->setText(QString());
        maximizeButton->setText(QString());
        closeButton->setText(QString());
        backButton->setText(QString());
        forwardButton->setText(QString());
        upButton->setText(QString());
        desktopButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\261\320\276\321\207\320\270\320\271 \321\201\321\202\320\276\320\273", nullptr));
        downloadsButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\270", nullptr));
        documentsButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\272\321\203\320\274\320\265\320\275\321\202\321\213", nullptr));
        picturesButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217", nullptr));
        musicButton->setText(QCoreApplication::translate("MainWindow", "\320\234\321\203\320\267\321\213\320\272\320\260", nullptr));
        videoButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\264\320\265\320\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
