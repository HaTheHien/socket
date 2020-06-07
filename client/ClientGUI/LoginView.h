#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LoginView.h"
#include "ClientSocket.h"
#include <iostream>
#include <qerrormessage.h>

using namespace std;

class LoginView : public QMainWindow
{
    Q_OBJECT

private:
    
public:
    LoginView(QWidget *parent = Q_NULLPTR);
    Ui::LoginViewClass ui;

private slots:
    void OnLoginButtonClick();
    void OnRegisterButtonClick();
};
