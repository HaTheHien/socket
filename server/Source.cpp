#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include <string>
#include <direct.h>
#include <Windows.h>
#include <conio.h>
#include <algorithm>
#include <filesystem>
#include "Header.h"
using namespace std;
namespace fs = std::experimental::filesystem;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "11111"

vector<thread*> a;
vector<int*> client;

void handle_connection(int*&p);
int addClient(vector<int*>&client,int clientSocket)
{
	for (int i = 0; i < client.size(); i++)
	{
		if (client[i] == NULL)
		{
			client[i] = new int;
			*client[i] = clientSocket;
			return i;
		}
	}
	client.push_back(NULL);
	int size = client.size() - 1;
	client[size] = new int;
	*client[size] = clientSocket;
	return size;
}
int num(char x) { return x - '0'; }
unsigned long int Value(string  s) {
	unsigned long int res = 0;
	for (int i = 0; i < s.size(); i++) res = res * 10 + num(s[i]);
	return res;
}
int __cdecl main(void)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = ::bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	
	cout << "Enter button ESC in keyboard to exit" << endl;
	// Accept a client socket
	while (true)
	{
		int check = false;
		//printf("Waiting for connection.....\n");
		ClientSocket = accept(ListenSocket,NULL,NULL);
		if (ClientSocket != SOCKET_ERROR)
		{
			int i = addClient(client, ClientSocket);
			cout << "client conect" << endl;
			for (int i = 0; i < a.size(); i++)
			{
				if (a[i] == NULL)
				{
					a[i] = new thread(handle_connection, ref(client[i]));
					break;
				}
				if (a[i] != NULL && a[i]->joinable())
				{
					a[i]->join();
					delete a[i];
					a[i] = new thread(handle_connection, ref(client[i]));
					break;
				}
			}
			if (check == false)
			{
				a.push_back(NULL);
				a[a.size() - 1] = new thread(handle_connection, ref(client[i]));
			}
		}
		if (_kbhit()) // sever exit
		{  
			char ch = _getch();
			if (ch == 27) // ESC
			{
				for (int i = 0; i < client.size(); i++)
				{
					if (client[i])
					{
						send(*client[i], (string(ECHO) + " " + "sever is offline!").c_str(), 23, 0);
						closesocket(*client[i]);
					}
				}
				closesocket(ListenSocket);
				exit(0);
			}
		}
	}
}

void handle_connection(int*&p) // lam viec sau khi ket noi
{
	/*char buf[4096];
	int byteReceive = recv(*p, buf, 4096, 0);
	string b = buf;
	cout << b << endl;
	cout << byteReceive << endl;*/
	int clientSocket = *p;
	char buf[4096];
	bool Login = false;
	string username;
	// login
	while (true)
	{
		ZeroMemory(buf, 4096);
		int byteReceive = recv(clientSocket, buf, 4096, 0);
		cout << buf << endl;
		break;
		if (byteReceive > 0)
		{
			string b = buf;
			string cat = b.substr(0, 4);
			if (cat == LOGIN)
			{
				int i = b.find(" ", 5);
				username = b.substr(5, i - 5);
				string password = b.substr(i + 1, byteReceive - i);
				ifstream fin("Login.txt");
				if (!fin.is_open())
					send(clientSocket, NOTOK, 5, 0);
				else
				{
					string a;
					while (getline(fin, a, ' '))
					{
						if (a == username)
						{
							getline(fin, a);
							if (a == password)
							{
								send(clientSocket, OK, 3, 0);
								Login = true;
								break;
							}
						}
					}
					if (Login == true)
						break;
					else
						send(clientSocket, NOTOK, 7, 0);
				}
			}
			if (cat == RES)
			{
				int i = b.find(" ", 5);
				string username = b.substr(5, i - 5);
				string password = b.substr(i + 1, byteReceive - i);
				ifstream fin("Login.txt");
				if (!fin.is_open())
				{
					ofstream fout("Login.txt");
					fout << username;
					fout << " ";
					fout << password << endl;
					fout.close();
					send(clientSocket, OK , 3, 0);
				}
				else
				{
					string a;
					while (getline(fin, a))
					{
						int i = a.find(" ");
						a = a.substr(0, i);
						if (a == username)
						{
							send(clientSocket, NOTOK, 7, 0);
							continue;
						}
					}
					Login = true;
					ofstream fout("Login.txt", ios::app);
					fout << username;
					fout << " ";
					fout << password << endl;
					fout.close();
					fin.close();
					send(clientSocket, OK, 3, 0);
					break;
				}
			}
			if (cat == EXIT)
				break;
		}
	}
	//Tao thu muc cho user
	if (Login == true)
	{
		_mkdir(username.c_str());
		for (int i = 0; i < client.size(); i++)
		{
			if (client[i])
			{
				send(*client[i], (string(ECHO) + " " + username + " login").c_str(), username.size() + 12, 0);
			}
		}
	}
	//upload download
	while (Login == true)
	{
		ZeroMemory(buf, 4096);
		int byteReceive = recv(clientSocket, buf, 4096, 0);
		if (byteReceive > 0)
		{
			string b = buf;
			string cat = b.substr(0, 4);
			if (cat == UPLOAD)
			{
				int i;
				bool flag = false;
				i = b.find(" ", 5);
				string size = b.substr(5, i - 5);
				b = b.substr(i + 1, byteReceive - i);
				string path = username + '\\' + b;

				// xu ly duplicate
				ifstream fin(path);
				if (fin.is_open())
				{
					fin.close();
					send(clientSocket, DUPLICATE, 5, 0);
					while (true)
					{
						ZeroMemory(buf, 4096);
						byteReceive = recv(clientSocket, buf, 4096, 0);
						b = buf;
						if (b == YES)
						{
							flag = true;
							break;
						}
						else if (b == NO)
						{
							send(clientSocket, ABORT, 5, 0);
							break;
						}
						else
						{
							send(clientSocket, ERR, 5, 0);
						}
					}
				}
				else
					flag = true;
				// con lai
				if (flag == true)
				{
					
					fs::space_info spaceInfo = fs::space(fs::current_path());
					if (spaceInfo.free < Value(size))
					{
						send(clientSocket, OUT_OF_SPACE, 5, 0);
						continue;
					}
					// ham trao doi du lieu
				}
			}
			if (cat == DOWNLOAD)
			{

			}
			if (cat == EXIT)
			{
				break;
			}
		}
	}
	delete p;
	p = NULL;
	for (int i = 0; i < client.size(); i++)
	{
		if (client[i])
		{
			send(*client[i], (string(ECHO) + " " + username + " logout").c_str(), username.size() + 12, 0);
		}
	}
	closesocket(clientSocket); // khi khong ket noi nua thi tat
}