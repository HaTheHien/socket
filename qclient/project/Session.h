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
#include <QFileDialog>

#define STANDARD_PACKET_SIZE 4096

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
    void Upload(ClientSocket* socket);
    void Download(ClientSocket* socket, QString filename);

    void Login_();
    void echo(QString mess);
    void echo_(QString message, int t = 2);

    ClientSocket* getPassBySocket();

signals:
    void OnServerEcho(QString message);
    void OnServerEcho__();
    void OnServerEcho_(QString message, int t = 2);
    //void OnLoginSuccess();
    void OnLoginSuccess(ClientSocket* clientSocket);
    void OnDownloadFinished();
    void OnUploadFished();
};

void Login(ClientSocket* clientSocket, QString username, QString password);

#endif // SESSIONS_H
