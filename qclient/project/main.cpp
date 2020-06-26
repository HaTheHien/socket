#include "LoginView.h"
#include "MainView.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginView loginView;
    MainView mainView;

    QObject::connect(&loginView, &LoginView::OnLoginCompleted,
                     &mainView, &MainView::setClientSocket);
    QObject::connect(&loginView, &LoginView::OnLoginViewClose,
                     &mainView, &MainView::show);
    QObject::connect(&loginView, &LoginView::OnLoginCompleted,
                     &mainView, &MainView::InitFileListFromJson);

    loginView.show();

    mainView.show();

    return a.exec();

//    QThread* t1 = QThread::create(doSomething, "12345");
//    t1->start();
//    Sleep(5*1000);
//    return 0;
}
