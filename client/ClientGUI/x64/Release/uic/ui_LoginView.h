/********************************************************************************
** Form generated from reading UI file 'LoginView.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINVIEW_H
#define UI_LOGINVIEW_H

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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginViewClass
{
public:
    QAction *actionLog_out;
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *loginGridLayout;
    QLineEdit *userNameInput;
    QVBoxLayout *verticalLayout;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QLabel *usernameLabel;
    QLineEdit *passwordInput;
    QLabel *passwordLabel;
    QLabel *serverIpLable;
    QLineEdit *serverIpInput;
    QMenuBar *menuBar;
    QMenu *menuUser;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LoginViewClass)
    {
        if (LoginViewClass->objectName().isEmpty())
            LoginViewClass->setObjectName(QString::fromUtf8("LoginViewClass"));
        LoginViewClass->resize(760, 465);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginViewClass->sizePolicy().hasHeightForWidth());
        LoginViewClass->setSizePolicy(sizePolicy);
        actionLog_out = new QAction(LoginViewClass);
        actionLog_out->setObjectName(QString::fromUtf8("actionLog_out"));
        centralWidget = new QWidget(LoginViewClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(90, 170, 491, 166));
        loginGridLayout = new QGridLayout(gridLayoutWidget);
        loginGridLayout->setSpacing(6);
        loginGridLayout->setContentsMargins(11, 11, 11, 11);
        loginGridLayout->setObjectName(QString::fromUtf8("loginGridLayout"));
        loginGridLayout->setContentsMargins(0, 0, 0, 0);
        userNameInput = new QLineEdit(gridLayoutWidget);
        userNameInput->setObjectName(QString::fromUtf8("userNameInput"));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu Mono"));
        font.setPointSize(10);
        userNameInput->setFont(font);

        loginGridLayout->addWidget(userNameInput, 1, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(4, 4, 4, 4);
        loginButton = new QPushButton(gridLayoutWidget);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(30);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(loginButton->sizePolicy().hasHeightForWidth());
        loginButton->setSizePolicy(sizePolicy1);
        loginButton->setFont(font);
        loginButton->setFocusPolicy(Qt::ClickFocus);
        loginButton->setLayoutDirection(Qt::LeftToRight);
        loginButton->setAutoDefault(false);
        loginButton->setFlat(false);

        verticalLayout->addWidget(loginButton, 0, Qt::AlignRight);

        registerButton = new QPushButton(gridLayoutWidget);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));
        sizePolicy.setHeightForWidth(registerButton->sizePolicy().hasHeightForWidth());
        registerButton->setSizePolicy(sizePolicy);
        registerButton->setFont(font);
        registerButton->setFlat(false);

        verticalLayout->addWidget(registerButton, 0, Qt::AlignRight);


        loginGridLayout->addLayout(verticalLayout, 3, 2, 1, 1);

        usernameLabel = new QLabel(gridLayoutWidget);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Ubuntu Mono"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        usernameLabel->setFont(font1);

        loginGridLayout->addWidget(usernameLabel, 1, 0, 1, 1);

        passwordInput = new QLineEdit(gridLayoutWidget);
        passwordInput->setObjectName(QString::fromUtf8("passwordInput"));
        passwordInput->setFont(font);
        passwordInput->setInputMask(QString::fromUtf8(""));
        passwordInput->setEchoMode(QLineEdit::Password);

        loginGridLayout->addWidget(passwordInput, 2, 2, 1, 1);

        passwordLabel = new QLabel(gridLayoutWidget);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setFont(font1);

        loginGridLayout->addWidget(passwordLabel, 2, 0, 1, 1);

        serverIpLable = new QLabel(gridLayoutWidget);
        serverIpLable->setObjectName(QString::fromUtf8("serverIpLable"));
        serverIpLable->setFont(font1);

        loginGridLayout->addWidget(serverIpLable, 0, 0, 1, 1);

        serverIpInput = new QLineEdit(gridLayoutWidget);
        serverIpInput->setObjectName(QString::fromUtf8("serverIpInput"));
        serverIpInput->setFont(font);

        loginGridLayout->addWidget(serverIpInput, 0, 2, 1, 1);

        LoginViewClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LoginViewClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 760, 26));
        menuUser = new QMenu(menuBar);
        menuUser->setObjectName(QString::fromUtf8("menuUser"));
        LoginViewClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LoginViewClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        LoginViewClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LoginViewClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        LoginViewClass->setStatusBar(statusBar);

        menuBar->addAction(menuUser->menuAction());
        menuUser->addAction(actionLog_out);

        retranslateUi(LoginViewClass);

        QMetaObject::connectSlotsByName(LoginViewClass);
    } // setupUi

    void retranslateUi(QMainWindow *LoginViewClass)
    {
        LoginViewClass->setWindowTitle(QCoreApplication::translate("LoginViewClass", "Kafka's Files", nullptr));
        actionLog_out->setText(QCoreApplication::translate("LoginViewClass", "Log-out", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginViewClass", "Login", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginViewClass", "Register", nullptr));
        usernameLabel->setText(QCoreApplication::translate("LoginViewClass", "Username", nullptr));
        passwordLabel->setText(QCoreApplication::translate("LoginViewClass", "Password", nullptr));
        serverIpLable->setText(QCoreApplication::translate("LoginViewClass", "Server IP", nullptr));
        menuUser->setTitle(QCoreApplication::translate("LoginViewClass", "User", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginViewClass: public Ui_LoginViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINVIEW_H
