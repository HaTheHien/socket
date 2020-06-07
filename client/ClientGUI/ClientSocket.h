#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string>
#include <exception>

using namespace std;
#pragma comment(lib, "Ws2_32.lib")

class ClientSocket
{
private:
	int addressFamily = AF_UNSPEC; //Internet address family is unspecified so that either an IPv6 or IPv4
	int socketType = SOCK_STREAM;
	int protocol = IPPROTO_TCP;
	SOCKET ConnectSocket = INVALID_SOCKET;
	size_t defaultBufferSize = 512;
	char* buffer = new char[defaultBufferSize];
public:
	/**
	 * @brief Init object as well as Winsock. Have exception.
	*/
	ClientSocket();
	
	~ClientSocket();

	/**
	 * @brief Create connection to a specific server. Have exception.
	 * @param ip: IP address or host name
	 * @param port: Default is 11111
	*/
	void ConnectToServer(string ip, string port = "11111");

	/**
	 * @brief Send data to server. 
	 * @param data: Maxium size should be 512 byte. If data size is too big, split it out and send multiple times.
	 * @return Number of bytes were sent successfully. If error, return -1.
	*/
	int Send(char* data);

	/**
	 * @brief Receive data from server.
	 * @return Number of received bytes. Data are stored in buffer, call getBuffer to take them.
	 * If connection closed, return 0. If error, return negative interger.
	*/
	int Receive();

	void setBufferSize(const size_t& size);

	char* getBuffer();
};

