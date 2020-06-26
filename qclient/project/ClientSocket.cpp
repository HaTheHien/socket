#include "ClientSocket.h"


//ClientSocket::ClientSocket(QObject *parent) : QObject(parent)
//{
//    //this->socket = new QTcpSocket();
//}

//ClientSocket::ClientSocket()
//{

//}

QVector<QString> SockError
{
    "ConnectionRefusedError",           //0
    "RemoteHostClosedError",
    "HostNotFoundError",
    "SocketAccessError",
    "SocketResourceError",
    "SocketTimeoutError",               //5
    "DatagramTooLargeError",
    "NetworkError",
    "AddressInUseError",
    "SocketAddressNotAvailableError",
    "UnsupportedSocketOperationError",  //10
    "UnfinishedSocketOperationError",
    "ProxyAuthenticationRequiredError",
    "SslHandshakeFailedError",
    "ProxyConnectionRefusedError",
    "ProxyConnectionClosedError",       //15
    "ProxyConnectionTimeoutError",
    "ProxyNotFoundError",
    "ProxyProtocolError",
    "OperationError",
    "SslInternalError",                 //20
    "SslInvalidUserDataError",
    "TemporaryError"
};

ClientSocket::ClientSocket(QString hostIP, qint16 port)
{
    this->hostIP = hostIP;
    this->port = port;
    this->TCPSocket = new QTcpSocket();

    if(this->connectToServer() == false)
    {
        throw std::exception("Can't connect to server!");
    }
}

ClientSocket::ClientSocket(QString hostIP, QString port)
{
    this->hostIP = hostIP;
    this->port = port.toUShort();
    this->TCPSocket = new QTcpSocket();

//    QObject::connect(this->TCPSocket, &QTcpSocket::errorOccurred,
//                     this, &ClientSocket::errorOccured);

    if(this->connectToServer() == false)
    {
        throw std::exception("Can't connect to server!");
    }
}

ClientSocket::~ClientSocket()
{
    if(this->TCPSocket->isValid())
    {
        this->TCPSocket->disconnectFromHost();
    }
    this->TCPSocket->waitForDisconnected();

//    QObject::disconnect(this->TCPSocket, &QTcpSocket::errorOccurred,
//                        this, &ClientSocket::errorOccured);

    delete this->TCPSocket;
    this->TCPSocket = nullptr;
}

bool ClientSocket::connectToServer()
{
    //this->TCPSocket = new QTcpSocket();
    this->TCPSocket->connectToHost(this->hostIP, this->port);
    return this->TCPSocket->waitForConnected();
}

ClientSocket::ClientSocket()
{
//    QObject::connect(this->TCPSocket, &QTcpSocket::errorOccurred,
//                     this, &ClientSocket::errorOccured);
}

int ClientSocket::Send(const QString &data)
{
    QByteArray tmp = data.toLocal8Bit();
    return this->TCPSocket->write(tmp.data());
}

void ClientSocket::Receive()
{
    if(this->TCPSocket->waitForReadyRead()) //Wait 30s
    {
        this->buffer = this->TCPSocket->readAll();
    }
//    else
//    {
//        throw std::exception("Server time out!");
//    }

//    while(!this->TCPSocket->waitForReadyRead())
//    {
//        //wait forever
//    }
//    this->buffer = this->TCPSocket->readAll();
}

QByteArray ClientSocket::getBuffer()
{
    return this->buffer;
}

QTcpSocket *ClientSocket::getSocket()
{
    return this->TCPSocket;
}

void ClientSocket::errorOccured(QAbstractSocket::SocketError error)
{
    qint32 errCode = error;

    throw std::exception(SockError[errCode].toStdString().c_str());
}

bool ClientSocket::isValid()
{
    if(this->TCPSocket == nullptr)
        return false;

    return this->TCPSocket->isValid();
}

void ClientSocket::setIP(const QString &ip)
{
    this->hostIP = ip;
}

void ClientSocket::setPort(const qint16 &port)
{
    this->port = port;
}

void ClientSocket::setPort(const QString &port)
{
    this->port = port.toUShort();
}
