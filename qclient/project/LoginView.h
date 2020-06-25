#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QMainWindow>
#include <exception>
#include <QErrorMessage>
#include "Session.h"
#include <QThread>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginView; }
QT_END_NAMESPACE

class LoginView : public QMainWindow
{
    Q_OBJECT

public:
    LoginView(QWidget *parent = nullptr);
    ~LoginView();
    ClientSocket* clientSocket = nullptr;
private:
    Ui::LoginView *ui;

private slots:
    void OnLoginButtonClick();
    void OnRegisterButtonClick();

signals:
    void OnLoginCompleted(ClientSocket* clientSocket);
    void OnLoginViewClose();
};
#endif // LOGINVIEW_H
