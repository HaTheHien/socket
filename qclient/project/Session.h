#ifndef SESSIONS_H
#define SESSIONS_H
#include "ClientSocket.h"
#include "Header.h"
#include "File_Management.h"
#include <fstream>
#include <QThread>
#include <QMessageBox>
#include <QIcon>
#include <QAbstractButton>
#include <QTimer>

class Session: public QObject
{
    Q_OBJECT
private:
    QThread* worker;
    ClientSocket* passBySocket;
    QString username;
    QString password;
public:
    //explicit Session(QObject *parent=nullptr);
    Session();
    //~Session();
    void StartToLogin(ClientSocket* clientSocket, QString username, QString password);
    void Login(ClientSocket* clientSocket, QString username, QString password);
    void Register(ClientSocket* socket, QString username, QString password);
    void Upload(ClientSocket* socket, QString filename);
    void Download(ClientSocket* socket, QString filename);

    void Login_();

    ClientSocket* getPassBySocket();

signals:
    void OnServerEcho(QString& message);
    //void OnLoginSuccess();
    void OnLoginSuccess(ClientSocket* clientSocket);
};

void Login(ClientSocket* clientSocket, QString username, QString password);

#endif // SESSIONS_H
