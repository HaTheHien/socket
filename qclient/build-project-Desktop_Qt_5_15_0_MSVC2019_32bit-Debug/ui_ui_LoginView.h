/********************************************************************************
** Form generated from reading UI file 'ui_LoginView.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_LOGINVIEW_H
#define UI_UI_LOGINVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginView
{
public:
    QAction *actionLog_out;
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QLineEdit *ipInput;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menuUser;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginView)
    {
        if (LoginView->objectName().isEmpty())
            LoginView->setObjectName(QString::fromUtf8("LoginView"));
        LoginView->resize(800, 600);
        actionLog_out = new QAction(LoginView);
        actionLog_out->setObjectName(QString::fromUtf8("actionLog_out"));
        centralwidget = new QWidget(LoginView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(180, 170, 371, 217));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        loginButton = new QPushButton(gridLayoutWidget);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loginButton->sizePolicy().hasHeightForWidth());
        loginButton->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu Mono"));
        font.setPointSize(14);
        loginButton->setFont(font);

        gridLayout->addWidget(loginButton, 7, 1, 1, 1, Qt::AlignRight);

        registerButton = new QPushButton(gridLayoutWidget);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));
        sizePolicy.setHeightForWidth(registerButton->sizePolicy().hasHeightForWidth());
        registerButton->setSizePolicy(sizePolicy);
        registerButton->setFont(font);

        gridLayout->addWidget(registerButton, 8, 1, 1, 1, Qt::AlignRight);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 6, 0, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 4, 0, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);

        usernameInput = new QLineEdit(gridLayoutWidget);
        usernameInput->setObjectName(QString::fromUtf8("usernameInput"));
        usernameInput->setFont(font);

        gridLayout->addWidget(usernameInput, 2, 1, 1, 1);

        passwordInput = new QLineEdit(gridLayoutWidget);
        passwordInput->setObjectName(QString::fromUtf8("passwordInput"));
        passwordInput->setFont(font);
        passwordInput->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passwordInput, 4, 1, 1, 1);

        ipInput = new QLineEdit(gridLayoutWidget);
        ipInput->setObjectName(QString::fromUtf8("ipInput"));
        ipInput->setFont(font);

        gridLayout->addWidget(ipInput, 6, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 2, 0, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);

        LoginView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginView);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menuUser = new QMenu(menubar);
        menuUser->setObjectName(QString::fromUtf8("menuUser"));
        LoginView->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginView);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        LoginView->setStatusBar(statusbar);

        menubar->addAction(menuUser->menuAction());
        menuUser->addAction(actionLog_out);

        retranslateUi(LoginView);

        QMetaObject::connectSlotsByName(LoginView);
    } // setupUi

    void retranslateUi(QMainWindow *LoginView)
    {
        LoginView->setWindowTitle(QCoreApplication::translate("LoginView", "LoginView", nullptr));
        actionLog_out->setText(QCoreApplication::translate("LoginView", "Log-out", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginView", "Login", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginView", "Register", nullptr));
        label_3->setText(QCoreApplication::translate("LoginView", "IP", nullptr));
        label_2->setText(QCoreApplication::translate("LoginView", "Password", nullptr));
        label->setText(QCoreApplication::translate("LoginView", "Username", nullptr));
        menuUser->setTitle(QCoreApplication::translate("LoginView", "User", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginView: public Ui_LoginView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_LOGINVIEW_H
