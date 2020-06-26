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
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainView
{
public:
    QAction *actionLog_out;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *rootTab;
    QVBoxLayout *verticalLayout_2;
    QFrame *line;
    QListView *listView;
    QHBoxLayout *horizontalLayout;
    QPushButton *uploadButton;
    QPushButton *downloadButton;
    QWidget *uploadQueueTab;
    QVBoxLayout *verticalLayout_3;
    QListView *uploadListView;
    QWidget *downloadQueueTab;
    QVBoxLayout *verticalLayout_4;
    QListView *downloadListView;
    QLabel *label;
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
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setTabShape(QTabWidget::Triangular);
        rootTab = new QWidget();
        rootTab->setObjectName(QString::fromUtf8("rootTab"));
        verticalLayout_2 = new QVBoxLayout(rootTab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        line = new QFrame(rootTab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        listView = new QListView(rootTab);
        listView->setObjectName(QString::fromUtf8("listView"));

        verticalLayout_2->addWidget(listView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        uploadButton = new QPushButton(rootTab);
        uploadButton->setObjectName(QString::fromUtf8("uploadButton"));
        QFont font;
        font.setFamily(QString::fromUtf8("Segoe UI Semibold"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        uploadButton->setFont(font);

        horizontalLayout->addWidget(uploadButton);

        downloadButton = new QPushButton(rootTab);
        downloadButton->setObjectName(QString::fromUtf8("downloadButton"));
        downloadButton->setFont(font);

        horizontalLayout->addWidget(downloadButton);


        verticalLayout_2->addLayout(horizontalLayout);

        tabWidget->addTab(rootTab, QString());
        uploadQueueTab = new QWidget();
        uploadQueueTab->setObjectName(QString::fromUtf8("uploadQueueTab"));
        verticalLayout_3 = new QVBoxLayout(uploadQueueTab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        uploadListView = new QListView(uploadQueueTab);
        uploadListView->setObjectName(QString::fromUtf8("uploadListView"));

        verticalLayout_3->addWidget(uploadListView);

        tabWidget->addTab(uploadQueueTab, QString());
        downloadQueueTab = new QWidget();
        downloadQueueTab->setObjectName(QString::fromUtf8("downloadQueueTab"));
        verticalLayout_4 = new QVBoxLayout(downloadQueueTab);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        downloadListView = new QListView(downloadQueueTab);
        downloadListView->setObjectName(QString::fromUtf8("downloadListView"));

        verticalLayout_4->addWidget(downloadListView);

        tabWidget->addTab(downloadQueueTab, QString());

        verticalLayout->addWidget(tabWidget);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Segoe UI"));
        font1.setPointSize(9);
        font1.setItalic(true);
        label->setFont(font1);
        label->setFrameShape(QFrame::NoFrame);
        label->setFrameShadow(QFrame::Plain);
        label->setLineWidth(0);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        MainView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainView);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menuUser = new QMenu(menubar);
        menuUser->setObjectName(QString::fromUtf8("menuUser"));
        MainView->setMenuBar(menubar);
        statusbar = new QStatusBar(MainView);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(statusbar->sizePolicy().hasHeightForWidth());
        statusbar->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setPointSize(11);
        font2.setItalic(true);
        statusbar->setFont(font2);
        MainView->setStatusBar(statusbar);

        menubar->addAction(menuUser->menuAction());
        menuUser->addAction(actionLog_out);

        retranslateUi(MainView);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainView);
    } // setupUi

    void retranslateUi(QMainWindow *MainView)
    {
        MainView->setWindowTitle(QCoreApplication::translate("MainView", "Kafka File Server", nullptr));
        actionLog_out->setText(QCoreApplication::translate("MainView", "Log-out", nullptr));
        uploadButton->setText(QCoreApplication::translate("MainView", "Upload", nullptr));
        downloadButton->setText(QCoreApplication::translate("MainView", "Download", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(rootTab), QCoreApplication::translate("MainView", "Root", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(uploadQueueTab), QCoreApplication::translate("MainView", "Upload Queue", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(downloadQueueTab), QCoreApplication::translate("MainView", "Download Queue", nullptr));
        label->setText(QCoreApplication::translate("MainView", "TextLabel", nullptr));
        menuUser->setTitle(QCoreApplication::translate("MainView", "User", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainView: public Ui_MainView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVIEW_H
