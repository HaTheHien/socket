//#undef UNICODE
//
//#define WIN32_LEAN_AND_MEAN
//
//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <iostream>
//#include <vector>
//#include <thread>
//#include <fstream>
//#include <string>
//#include "Header.h"
//using namespace std;
//
//// Need to link with Ws2_32.lib
//#pragma comment (lib, "Ws2_32.lib")
//// #pragma comment (lib, "Mswsock.lib")
//
//#define DEFAULT_BUFLEN 512
//#define DEFAULT_PORT "11111"
//void handle_connection(int*p);
//int __cdecl main(void)
//{
//	WSADATA wsaData;
//	int iResult;
//
//	SOCKET ListenSocket = INVALID_SOCKET;
//	SOCKET ClientSocket = INVALID_SOCKET;
//
//	struct addrinfo *result = NULL;
//	struct addrinfo hints;
//
//	int iSendResult;
//	char recvbuf[DEFAULT_BUFLEN];
//	int recvbuflen = DEFAULT_BUFLEN;
//
//	// Initialize Winsock
//	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (iResult != 0) {
//		printf("WSAStartup failed with error: %d\n", iResult);
//		return 1;
//	}
//
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_INET;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_protocol = IPPROTO_TCP;
//	hints.ai_flags = AI_PASSIVE;
//
//	// Resolve the server address and port
//	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
//	if (iResult != 0) {
//		printf("getaddrinfo failed with error: %d\n", iResult);
//		WSACleanup();
//		return 1;
//	}
//
//	// Create a SOCKET for connecting to server
//	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
//	if (ListenSocket == INVALID_SOCKET) {
//		printf("socket failed with error: %ld\n", WSAGetLastError());
//		freeaddrinfo(result);
//		WSACleanup();
//		return 1;
//	}
//
//	// Setup the TCP listening socket
//	
//	iResult = ::bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
//
//	if (iResult == SOCKET_ERROR) {
//		printf("bind failed with error: %d\n", WSAGetLastError());
//		freeaddrinfo(result);
//		closesocket(ListenSocket);
//		WSACleanup();
//		return 1;
//	}
//
//	freeaddrinfo(result);
//
//	iResult = listen(ListenSocket, SOMAXCONN);
//	if (iResult == SOCKET_ERROR) {
//		printf("listen failed with error: %d\n", WSAGetLastError());
//		closesocket(ListenSocket);
//		WSACleanup();
//		return 1;
//	}
//	
//	// Accept a client socket
//	vector<thread*> a;
//	while (true)
//	{
//		//printf("Waiting for connection.....\n");
//		ClientSocket = accept(ListenSocket,NULL,NULL);
//		if (ClientSocket != SOCKET_ERROR)
//		{
//			send(ClientSocket, "Hello client", 13, 0);
//			for (int i = 0; i < a.size(); i++)
//			{
//				if (a[i] == NULL)
//				{
//					int *p = new int;
//					*p = ClientSocket;
//					a[i] = new thread(handle_connection, ref(p));
//				}
//				if (a[i] != NULL && a[i]->joinable())
//				{
//					delete a[i];
//					int *p = new int;
//					*p = ClientSocket;
//					a[i] = new thread(handle_connection, ref(p));
//				}
//			}
//			a.push_back(NULL);
//			int *p = new int;
//			*p = ClientSocket;
//			a[a.size() - 1] = new thread(handle_connection, ref(p)); 
//		}
//		
//	}
//
//	// No longer need server socket
//	//closesocket(ListenSocket);
//
//	// Receive until the peer shuts down the connection
//	closesocket(ListenSocket);
//}
//
//void handle_connection(int*p) // lam viec sau khi ket noi
//{
//	int clientSocket = *p;
//	delete p;
//	char buf[4096];
//	bool Login = false;
//	string username;
//	// login
//	while (true)
//	{
//		ZeroMemory(buf, 4096);
//		int byteReceive = recv(clientSocket, buf, 4096, 0);
//		if (byteReceive > 0)
//		{
//			string b = buf;
//			string cat = b.substr(0, 4);
//			if (cat == LOGIN)
//			{
//				int i = b.find(" ", 5);
//				username = b.substr(5, i - 5);
//				string password = b.substr(i + 1, byteReceive - i);
//				ifstream fin("Login.txt");
//				if (!fin.is_open())
//					send(clientSocket, NOTOK, 5, 0);
//				else
//				{
//					string a;
//					while (getline(fin, a, ' '))
//					{
//						if (a == username)
//						{
//							getline(fin, a);
//							if (a == password)
//							{
//								send(clientSocket, OK, 3, 0);
//								Login = true;
//								break;
//							}
//						}
//					}
//					if (Login == true)
//						break;
//					else
//						send(clientSocket, NOTOK, 7, 0);
//				}
//			}
//			if (cat == RES)
//			{
//				int i = b.find(" ", 5);
//				string username = b.substr(5, i - 5);
//				string password = b.substr(i + 1, byteReceive - i);
//				ifstream fin("Login.txt");
//				if (!fin.is_open())
//				{
//					ofstream fout("Login.txt");
//					fout << username;
//					fout << " ";
//					fout << password << endl;
//					fout.close();
//					send(clientSocket, OK , 3, 0);
//				}
//				else
//				{
//					string a;
//					while (getline(fin, a))
//					{
//						int i = a.find(" ");
//						a = a.substr(0, i);
//						if (a == username)
//						{
//							send(clientSocket, NOTOK, 7, 0);
//							continue;
//						}
//					}
//					Login = true;
//					ofstream fout("Login.txt", ios::app);
//					fout << username;
//					fout << " ";
//					fout << password << endl;
//					fout.close();
//					fin.close();
//					send(clientSocket, OK, 3, 0);
//					break;
//				}
//			}
//			if (cat == EXIT)
//				break;
//		}
//	}
//	//upload download
//	ZeroMemory(buf, 4096);
//	if (Login == true)
//	{
//
//	}
//	closesocket(clientSocket); // khi khong ket noi nua thi tat
//}