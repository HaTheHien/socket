#include "ClientSocket.h"

ClientSocket::ClientSocket()
{
    int iResult;
    WSADATA wsaData;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        throw exception("WSAStartup failed: " + iResult);
    }
}

ClientSocket::~ClientSocket()
{
    if (this->buffer != nullptr)
    {
        delete this->buffer;
        this->buffer = nullptr;
    }

    if (this->ConnectSocket != INVALID_SOCKET)
    {
        shutdown(this->ConnectSocket, SD_BOTH);
        this->ConnectSocket = INVALID_SOCKET;
    }
}

void ClientSocket::ConnectToServer(string ip, string port)
{
    struct addrinfo* result = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = this->addressFamily;
    hints.ai_socktype = this->socketType;
    hints.ai_protocol = this->protocol;

    // Resolve the server address and port
    int iResult = getaddrinfo(ip.c_str(), port.c_str(), &hints, &result);
    if (iResult != 0) 
    {
        WSACleanup();
        throw exception("getaddrinfo failed");
    }

    //SOCKET ConnectSocket = INVALID_SOCKET;
    for (addrinfo* ptr = result; ptr != nullptr; ptr = ptr->ai_next)
    {
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket != INVALID_SOCKET)
        {
            iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
            if (iResult == SOCKET_ERROR) 
            {
                closesocket(ConnectSocket);
                ConnectSocket = INVALID_SOCKET;
                WSACleanup();
                throw exception("Can't connect to server");
            }
            break;
        }
    }
    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET)
    {
        WSACleanup();
        throw exception("Create socket failed: " + WSAGetLastError());
    }
}

int ClientSocket::Send(const char* data)
{
    strcpy_s(this->buffer, this->defaultBufferSize, data);
    int iResult = send(this->ConnectSocket, this->buffer, this->defaultBufferSize, 0);
    return iResult;
}

int ClientSocket::Receive()
{
    int iResult = recv(ConnectSocket, this->buffer, this->defaultBufferSize, 0);
    return iResult;
}

void ClientSocket::setBufferSize(const size_t& size)
{
    this->defaultBufferSize = size;
}

char* ClientSocket::getBuffer()
{
    return this->buffer;
}
