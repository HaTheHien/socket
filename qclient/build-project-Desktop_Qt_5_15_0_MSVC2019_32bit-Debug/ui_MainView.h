/********************************************************************************
** Form generated from reading UI file 'MainView.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINVIEW_H
#define UI_MAINVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainView
{
public:
    QAction *actionLog_out;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QListView *listView;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QPushButton *uploadButton;
    QPushButton *downloadButton;
    QMenuBar *menubar;
    QMenu *menuUser;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainView)
    {
        if (MainView->objectName().isEmpty())
            MainView->setObjectName(QString::fromUtf8("MainView"));
        MainView->setWindowModality(Qt::NonModal);
        MainView->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/origami.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainView->setWindowIcon(icon);
        MainView->setIconSize(QSize(45, 45));
        MainView->setTabShape(QTabWidget::Triangular);
        actionLog_out = new QAction(MainView);
        actionLog_out->setObjectName(QString::fromUtf8("actionLog_out"));
        centralwidget = new QWidget(MainView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));

        verticalLayout->addWidget(listView);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        uploadButton = new QPushButton(centralwidget);
        uploadButton->setObjectName(QString::fromUtf8("uploadButton"));

        horizontalLayout->addWidget(uploadButton);

        downloadButton = new QPushButton(centralwidget);
        downloadButton->setObjectName(QString::fromUtf8("downloadButton"));

        horizontalLayout->addWidget(downloadButton);


        verticalLayout->addLayout(horizontalLayout);

        MainView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainView);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menuUser = new QMenu(menubar);
        menuUser->setObjectName(QString::fromUtf8("menuUser"));
        MainView->setMenuBar(menubar);
        statusbar = new QStatusBar(MainView);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainView->setStatusBar(statusbar);

        menubar->addAction(menuUser->menuAction());
        menuUser->addAction(actionLog_out);

        retranslateUi(MainView);

        QMetaObject::connectSlotsByName(MainView);
    } // setupUi

    void retranslateUi(QMainWindow *MainView)
    {
        MainView->setWindowTitle(QCoreApplication::translate("MainView", "Kafka File Server", nullptr));
        actionLog_out->setText(QCoreApplication::translate("MainView", "Log-out", nullptr));
        uploadButton->setText(QCoreApplication::translate("MainView", "Upload", nullptr));
        downloadButton->setText(QCoreApplication::translate("MainView", "Download", nullptr));
        menuUser->setTitle(QCoreApplication::translate("MainView", "User", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainView: public Ui_MainView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVIEW_H
