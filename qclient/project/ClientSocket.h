#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
#include <QString>
#include <QtNetwork/QTcpSocket>
#include <QVector>
#include <QHash>
#include <exception>



class ClientSocket //: public QObject
{
    //Q_OBJECT
private:
    QTcpSocket* TCPSocket;
    qint16 port;
    QString hostIP;
    QByteArray buffer;

    /*
     * Go into HostLookup State.
     * If connection is established, return true
     * Ortherwise, return false
     */
    bool connectToServer();
public:
    //ClientSocket(QObject *parent);
    ClientSocket();
    ClientSocket(QString hostIP, qint16 port);
    ClientSocket(QString hostIP, QString port);
    ~ClientSocket();

//  Send data to server
//  Return number of bytes were sent
    int Send(const QString& data);
    int Send(const char* data, int size);

    /*
     * Receive message from server
     * Data is stored in Client::buffer
     */
    void Receive();

    QByteArray getBuffer();
    QTcpSocket* getSocket();

    void errorOccured(QAbstractSocket::SocketError error);

    bool isValid();

    //Setter
    void setIP(const QString& ip);
    void setPort(const qint16& port);
    void setPort(const QString& port);

signals:
    //void errorOccured(QString mess);
};

#endif // CLIENTSOCKET_H
