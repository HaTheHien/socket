#include "LoginView.h"
#include "ui_ui_LoginView.h"


LoginView::LoginView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginView)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icons/origami.ico"));

    connect(ui->loginButton, &QPushButton::clicked,
            this, &LoginView::OnLoginButtonClick);
    connect(ui->registerButton, &QPushButton::clicked,
            this, &LoginView::OnRegisterButtonClick);

    this->clientSocket = nullptr;


}

LoginView::~LoginView()
{
    delete ui;
//    if(clientSocket->isValid())
//        delete clientSocket;
}

void LoginView::OnLoginButtonClick()
{
    qDebug("Login clicked!");
    try
    {
        //Inform user that we are logining in
//        QMessageBox loginDialog;
//        loginDialog.setWindowIcon(QIcon(":/icons/origami.ico"));
//        loginDialog.setText("Logining in...\nPlease wait");
//        loginDialog.setStandardButtons(QMessageBox::StandardButton::Cancel);
//        QAbstractButton* cancelButton = loginDialog.button(QMessageBox::StandardButton::Cancel);

        if(clientSocket == nullptr)
        {
            clientSocket = new ClientSocket(ui->ipInput->text(), QString("11111"));
        }

//        auto f = [&](){
//            Session s;
//            s.StartToLogin(clientSocket, ui->usernameInput->text(), ui->passwordInput->text());
//        };

//        QThread* loginThread = QThread::create(f);

//        //Open dialog when start
//        QObject::connect(loginThread, &QThread::started,
//                         &loginDialog, &QMessageBox::exec);
//        //Turn off message box when job is done
//        QObject::connect(loginThread, &QThread::finished,
//                         &loginDialog, &QMessageBox::deleteLater);
//        //Stop login when user want to
//        QObject::connect(cancelButton, &QAbstractButton::clicked,
//                         loginThread, &QThread::quit);

//        loginThread->start();

        Session loginSess;
        //loginSess.StartToLogin(clientSocket, ui->usernameInput->text(), ui->passwordInput->text());

        loginSess.Login(clientSocket, ui->usernameInput->text(), ui->passwordInput->text());


        qDebug() <<"Login Success!";
        this->hide();

        emit OnLoginViewClose();
        emit OnLoginCompleted(clientSocket);

        return;

    } catch (std::exception& e) {
        QMessageBox errMess;
        errMess.setWindowIcon(QIcon(":/icons/origami.ico"));
        errMess.setWindowTitle("Error");
        errMess.setText(e.what());
        errMess.setIcon(QMessageBox::Icon::Critical);
        errMess.exec();
    }
}

void LoginView::OnRegisterButtonClick()
{
    qDebug("Register clicked!");
    try
    {
        //Inform user that we are logining in
//        QMessageBox loginDialog;
//        loginDialog.setWindowIcon(QIcon(":/icons/origami.ico"));
//        loginDialog.setText("Logining in...\nPlease wait");
//        loginDialog.setStandardButtons(QMessageBox::StandardButton::Cancel);
//        QAbstractButton* cancelButton = loginDialog.button(QMessageBox::StandardButton::Cancel);

        if(clientSocket == nullptr)
        {
            clientSocket = new ClientSocket(ui->ipInput->text(), QString("11111"));
        }

//        auto f = [&](){
//            Session s;
//            s.StartToLogin(clientSocket, ui->usernameInput->text(), ui->passwordInput->text());
//        };

//        QThread* loginThread = QThread::create(f);

//        //Open dialog when start
//        QObject::connect(loginThread, &QThread::started,
//                         &loginDialog, &QMessageBox::exec);
//        //Turn off message box when job is done
//        QObject::connect(loginThread, &QThread::finished,
//                         &loginDialog, &QMessageBox::deleteLater);
//        //Stop login when user want to
//        QObject::connect(cancelButton, &QAbstractButton::clicked,
//                         loginThread, &QThread::quit);

//        loginThread->start();

        Session registerSess;
        //loginSess.StartToLogin(clientSocket, ui->usernameInput->text(), ui->passwordInput->text());

        registerSess.Register(clientSocket, ui->usernameInput->text(), ui->passwordInput->text());

        //emit OnLoginCompleted(clientSocket);

        return;

    } catch (std::exception& e) {
        QMessageBox errMess;
        errMess.setWindowIcon(QIcon(":/icons/origami.ico"));
        errMess.setWindowTitle("Info");
        errMess.setText(e.what());
        errMess.setIcon(QMessageBox::Icon::Information);
        errMess.exec();
    }
}

