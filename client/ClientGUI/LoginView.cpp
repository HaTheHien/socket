#include "LoginView.h"
#include <qdesktopwidget.h>
#include <qdialog.h>
#include <qmessagebox.h>

LoginView::LoginView(QWidget *parent)
    : QMainWindow(parent)
{
    QDesktopWidget dw;
    int x = dw.width()*0.7;
    int y = dw.height()*0.7;
    this->resize(x, y);
    
    this->setWindowIcon(QIcon("Origami"));

    ui.setupUi(this);
    

    QObject::connect(ui.loginButton, &QPushButton::clicked,
                        this, &LoginView::OnLoginButtonClick);

}

void LoginView::OnLoginButtonClick()
{
    try
    {
        ClientSocket sock;
        sock.ConnectToServer(ui.serverIpInput->text().toStdString());
    }
    catch (const std::exception& e)
    {
        QErrorMessage errorMess;
        errorMess.showMessage(e.what());
        errorMess.exec();
        //cout << e.what();
    }
}

void LoginView::OnRegisterButtonClick()
{

}
