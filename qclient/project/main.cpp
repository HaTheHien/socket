#include "LoginView.h"
#include "MainView.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);

        //ASK WHERE TO SAVE
//        QString filename = "abc";
//        QFileDialog fileDialog;

//        if(filename.indexOf('.') == -1) //Not found extension
//        {
//            filename += ".txt";
//        }

//        QString savedPath = fileDialog.getSaveFileName(nullptr, "Save as", filename);

//        qDebug() << savedPath;

        LoginView loginView;
        MainView mainView;

        QObject::connect(&loginView, &LoginView::OnLoginCompleted,
                         &mainView, &MainView::setClientSocket);
        QObject::connect(&loginView, &LoginView::OnLoginViewClose,
                         &mainView, &MainView::show);
        QObject::connect(&loginView, &LoginView::OnLoginCompleted,
                         &mainView, &MainView::InitFileListFromJson);

        loginView.show();

//        //mainView.show();

//        QFileDialog fileDialog;
//        fileDialog.setFileMode(QFileDialog::FileMode::ExistingFile);
//        //Get the path
//        QString filePath = fileDialog.getOpenFileName();
//        qDebug() << "Path:" << filePath;

//        QFile file(filePath);

//        qDebug() << file.read(4096).data();

//        ifstream fin("C:\\Users\\tarza\\OneDrive\\Pictures\\Saved Pictures\\470136.jpg", ios::binary);
//        char binanyData[4088];
//        fin.read(binanyData, 4088);
//        QString s = binanyData;
//        QByteArray b = s.toUtf8();

        return a.exec();
    } catch (std::exception e) {
        QMessageBox errMess;
        errMess.setWindowIcon(QIcon(":/icons/origami.ico"));
        errMess.setWindowTitle("Info");
        errMess.setText(e.what());
        errMess.setIcon(QMessageBox::Icon::Information);
        errMess.exec();
    }


//    ClientSocket* s1 = new ClientSocket();
//    ClientSocket* s2 = s1;

//    if(s2->isValid())
//    {
//        qDebug() << "s2 is valid";
//    }
//    delete s2;
//    s2 = nullptr;

//    if(s1->isValid())
//    {
//        qDebug() << "s1 is valid";
//    }

    return 0;
}
