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
#include <Windows.h>
#include <conio.h>
#include <algorithm>
#include <filesystem>
#include <mutex>
#include "Header.h"
#include "File_Management.h"
using namespace std;
namespace fs = std::experimental::filesystem;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "11111"

vector<thread*> a;
vector<int*> client;
vector<string*> use;
Container Mjson;
mutex blockJSON;
char buf[4096];
mutex block;
char buf2[4096];
mutex blockUpload;

string IntToString4(int kt)
{
	string t = to_string(kt);
	int n = t.size();
	for (int i = 0; i < 4 - n; i++)
	{
		t = " " + t;
	}
	return t;
}
void serverExit();
void handle_connection(int*&p);
bool DownLoad(int clientSocket,string path);
bool Upload(int clientSocket, string path);
bool DownloadJSON(int clientSocket);
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
	system("ipconfig");
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	thread EX(serverExit);
	cout << endl << "Enter button ESC in keyboard to server exit" << endl;
	// Accept a client socket
	while (true)
	{
		int check = false;
		//printf("Waiting for connection.....\n");
		ClientSocket = accept(ListenSocket,NULL,NULL);
		if (ClientSocket != SOCKET_ERROR)
		{
			int j = addClient(client, ClientSocket);
			cout << "client conect" << endl;
			for (int i = 0; i < a.size(); i++)
			{
				if (a[i] != NULL && a[i]->joinable())
				{
					check = true;
					a[i]->join();
					delete a[i];
					a[i] = new thread(handle_connection, ref(client[j]));
					break;
				}
			}
			if (check == false)
			{
				a.push_back(NULL);
				a[a.size() - 1] = new thread(handle_connection, ref(client[j]));
			}
		}
	}
}

void serverExit()
{
	while (true)
	{
		if (_kbhit()) // sever exit
		{
			char ch = _getch();
			if (ch == 27) // ESC
			{
				for (int i = 0; i < client.size(); i++)
				{
					if (client[i])
					{
						send(*client[i], ("0025" + string(ECHO) + "sever is offline!").c_str(), 26, 0);
						closesocket(*client[i]);
					}
				}
				exit(0);
			}
		}
	}
}

void handle_connection(int*&p) // lam viec sau khi ket noi
{
	int clientSocket = *p;
	bool Login = false;
	string username;
	//test
	/*block.lock();
	int byteReceive = recv(clientSocket, buf, 4096, 0);
	cout << buf << endl;
	delete p;
	p = NULL;
	block.unlock();
	return;*/
	// login
	while (true)
	{
		bool check = false;
		block.lock();
		int byteReceive = recv(clientSocket, buf, 4096, MSG_WAITALL);
		if (byteReceive == 0)
		{
			block.unlock();
			return;
		}
		if (byteReceive > 0)
		{
			string b = buf;
			string sizebuf = b.substr(0, 4);
			string cat = b.substr(4, 4);
			if (cat == LOGIN)
			{
				check = true;
				int i = b.find(" ", 8);
				username = b.substr(8, i - 8);
				string password = b.substr(i + 1, atoi(sizebuf.c_str()) - i);
				block.unlock();
				ifstream fin("Login.txt");
				if (!fin.is_open())
					send(clientSocket, ("0008" + string(NOTOK)).c_str(), 9, 0);
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
								bool flag = false;
								for (int j = 0; j < use.size(); j++)
								{
									if (a == *use[j])
									{
										flag = true;
										break;
									}
								}
								if (flag == true)
								{
									send(clientSocket, ("0029" + string(NOTOK) + "already login account").c_str(), 30, 0);
									break;
								}
								Login = true;
								int t = 8 + Mjson.version().size();
								send(clientSocket, (IntToString4(t) + string(OK) + Mjson.version()).c_str(), 9 + Mjson.version().size(), 0);
								for(int j=0;j<use.size();j++)
								{
									if (*use[j] == "")
									{
										use[j] = &username;
										break;
									}
									if (j == use.size() - 1)
										use.push_back(&username);
								}
								break;;
							}
						}
						else
							getline(fin, a);
					}
					fin.close();
					if (Login == true)
						continue;
					else
						send(clientSocket,("0018" +  string(NOTOK) + "login fail").c_str(), 19, 0);
				}
			}
			if (cat == READY)
			{
				block.unlock();
				if (!DownloadJSON(clientSocket))
				{
					Login = false;
				}
				break;
			}
			if (cat == UP_TO_DATE)
			{
				block.unlock();
				break;
			}
			if (cat == RES)
			{
				check = true;
				int i = b.find(" ", 8);
				string username = b.substr(8, i - 8);
				string password = b.substr(i + 1, byteReceive - i);
				block.unlock();
				ifstream fin("Login.txt");
				if (!fin.is_open())
				{
					ofstream fout("Login.txt");
					fout << username;
					fout << " ";
					fout << password << endl;
					fout.close();
					send(clientSocket, ("0008" + string(OK)).c_str(), 9, 0);
					fout.close();
					fin.close();
					continue;
				}
				else
				{
					string a;
					bool y = true;
					while (getline(fin, a))
					{
						int i = a.find(" ");
						a = a.substr(0, i);
						if (a == username)
						{
							send(clientSocket, ("0028" + string(NOTOK) + "username is used").c_str(), 28, 0);
							y = false;
							break;
						}
					}
					fin.close();
					if (y == false)
						continue;
					ofstream fout("Login.txt", ios::app);
					fout << username;
					fout << " ";
					fout << password << endl;
					fout.close();
					send(clientSocket,("0008" + string(OK)).c_str(), 9, 0);
					continue;
				}
			}
			if (cat == EXIT)
			{
				block.unlock();
				break;
			}
		}
		else
			block.unlock();
	}
	//Tao thu muc cho user
	int kt = 4 + 4 + username.size() + 6;
	string t = IntToString4(kt);
	if (Login == true)
	{
		for (int i = 0; i < client.size(); i++)
		{
			if (client[i])
			{
				send(*client[i], (t + string(ECHO) + username + " login").c_str(), username.size() + 15, 0);
			}
		}
		cout << username << " login" << endl;
	}
	//upload download
	while (Login == true)
	{
		bool check = false;
		block.lock();
		int byteReceive = recv(clientSocket, buf, 4096, 0);
		if (byteReceive == 0)
		{
			block.unlock();
			break;
		}
		if (byteReceive > 0)
		{
			string b = buf;
			string sizebuf = b.substr(0, 4);
			string cat = b.substr(4, 4);
			if (cat == UPLOAD)
			{
				check = true;
				int i;
				bool flag = false;
				i = b.find(" ", 8);
				string size = b.substr(8, i - 8); // kich thuoc file
				string path = b.substr(i + 1, atoi(sizebuf.c_str()) - i); // ten file
				block.unlock();
				// xu ly duplicate
				ifstream fin(path);
				if (fin.is_open()) //&& Mjson.get(path, username) != "")
				{
					fin.close();
					send(clientSocket,("0008" + string(DUPLICATE_)).c_str(), 9, 0);
					block.lock();
					while (true)
					{
						byteReceive = recv(clientSocket, buf, 4096, 0);
						if (byteReceive == 0)
						{
							block.unlock();
							break;
						}
						if (byteReceive > 0)
						{
							b = buf;
							b = b.substr(4, 4);
							if (b == YES)
							{
								flag = true;
								break;
							}
							else if (b == NO)
							{

								send(clientSocket, ("0008" + string(ABORT)).c_str(), 9, 0);
								break;
							}
							else
							{
								send(clientSocket, ("0008" + string(ERR)).c_str(), 9, 0);
								break;
							}
						}
					}
					block.unlock();
				}
				else
					flag = true;
				// con lai
				if (flag == true)
				{
					unsigned long int SIZE = Value(size);
					/*fs::space_info spaceInfo = fs::space(fs::current_path());
					if (spaceInfo.free < SIZE)
					{
						send(clientSocket,("0009" + string(OUT_OF_SPACE)).c_str(), 10, 0);
						continue;
					}*/
					if (SIZE > MAX_SIZE_FILE)
					{
						//send(clientSocket,(""))
						continue;
					}
					send(clientSocket, ("0008" + string(OK)).c_str(), 9, 0);
					// ham trao doi du lieu
					if (Upload(clientSocket, path))
					{
						vector<string> b;
						blockJSON.lock();
						Mjson.addDocument(path, SIZE, username, b);
						for (int i = 0; i < client.size(); i++)
						{
							if (client[i])
							{
								int t2 = path.size() + size.size() + username.size() + 8 + 2;
								send(*client[i], (IntToString4(t2) + string(UPDATE) +  size + " "+ username + " " + path).c_str(), t2 + 1, 0);
							}
						}
						blockJSON.unlock();
						cout << username << " upload file:" << path << endl;
					}
					else
						break;
				}
			}
			if (cat == DOWNLOAD)
			{
				check = true;
				block.unlock();
				string path = b.substr(8, atoi(sizebuf.c_str()) - 8);
				ifstream fin(path);
				if (!fin.is_open())
				{
					send(clientSocket, ("0019" + string(NOTOK) + "can't open file").c_str(), 20, 0);
					continue;
				}
				else
					send(clientSocket, ("0008" + string(OK)).c_str(), 9, 0);
				while (true)
				{
					block.lock();
					byteReceive = recv(clientSocket, buf, 4096, 0);
					if (byteReceive == 0)
					{
						cat = EXIT;
						block.unlock();
						break;
					}
					if (byteReceive > 0)
					{
						b = buf;
						string c = b.substr(4, 4);
						block.unlock();
						if (c == READY)
						{
							if (DownLoad(clientSocket, path))
								cout << username << " download file:" << path << endl;
						}
					}
					else
						block.unlock();
				}
			}
			if (cat == EXIT)
			{
				break;
			}
		}
		if (check == false)
			block.unlock();
	}
	delete p;
	p = NULL;
	if (Login == true)
	{
		for (int i = 0; i < client.size(); i++)
		{
			if (client[i])
			{
				send(*client[i], (t + string(ECHO) + username + " logout").c_str(), kt + 1, 0);
			}
		}
		cout << username << " logout" << endl;
	}
	closesocket(clientSocket); // khi khong ket noi nua thi tat
}

bool Upload(int clientSocket, string path) 
{
	ofstream fout(path);
	blockUpload.lock();
	while (true)
	{
		int byteReceive = recv(clientSocket, buf2, 4096, 0);
		if (byteReceive == 0) // mat ket noi client
		{
			blockUpload.unlock();
			return false;
		}
		if (byteReceive > 0)
		{
			string b = buf2;
			string cat = b.substr(4, 4);
			int size = atoi(b.substr(0, 4).c_str());
			size -= 8;
			if (cat == ACK)
			{
				fout.write(buf2 + 8, size);
				send(clientSocket, ("0008" + string(ACK)).c_str(), 9, 0);
			}
			if (cat == END_OF_FILE)
			{
				fout.write(buf2 + 8, size);
				send(clientSocket, ("0008" + string(UPLOAD_DONE)).c_str(), 9, 0);
				blockUpload.unlock();
				return true;
			}
		}
	}
}

bool DownLoad(int clientSocket,string path)
{
	ifstream fin(path);
	if (!fin.is_open())
	{
		send(clientSocket, ("0019" + string(NOTOK) + "can't open file").c_str(), 20, 0);
		return false;
	}
	long int size;
	fin.seekg(0, ios::end);
	size = fin.tellg();
	fin.seekg(0, ios::beg);
	while (true)
	{
		block.lock();
		if (size > 4092)
		{
			size -= 4092;
			fin.read(buf, 4092);
			send(clientSocket, ("4096" + string(FILE_) + buf).c_str(), 4097, 0);
		}
		else
		{
			fin.read(buf, size);
			int t2 = size + 8;
			send(clientSocket, (IntToString4(t2) + string(END_OF_FILE) + buf).c_str(), size + 9, 0);
		}
		block.unlock();
		while (true)
		{
			block.lock();
			int byteReceive = recv(clientSocket, buf, 4096, 0);
			if (byteReceive == 0) // mat ket noi voi client
			{
				block.unlock();
				return false;
			}
			if (byteReceive > 0)
			{
				string b = buf;
				b = b.substr(4, 4);
				if (b == string(ACK))
				{
					block.unlock();
					break;
				}
				if (b == string(DOWNLOAD_DONE))
				{
					block.unlock();
					return true;
				}
			}
			else
				block.unlock();
		};
	}
	return false;
}

bool DownloadJSON(int clientSocket)
{
	blockJSON.lock();
	ifstream fin("file.json");
	if (!fin.is_open())
	{
		send(clientSocket, ("0008" + string(ERR)).c_str(), 9, 0);
		blockJSON.unlock();
		return false;
	}
	fin.seekg(0, ios::end);
	int size = fin.tellg();
	fin.seekg(0, ios::beg);
	while (true)
	{
		block.lock();
		if (size > 4092)
		{
			fin.read(buf, 4092);
			size -= 4092;
			send(clientSocket, ("4096" + string(FILE_) + buf).c_str(), 4097, 0);
		}
		else
		{
			int t2 = size + 8;
			fin.read(buf, size);
			send(clientSocket, (IntToString4(t2) + string(END_OF_FILE) + buf).c_str(), size + 9, 0);
		}
		block.unlock();
		while (true)
		{
			block.lock();
			int byteReceive = recv(clientSocket, buf, 4096, 0);
			if (byteReceive == 0) // mat ket noi voi client
			{
				block.unlock();
				blockJSON.unlock();
				return false;
			}
			if (byteReceive > 0)
			{
				string b = buf;
				b = b.substr(4, 4);
				if (b == string(ACK))
				{
					block.unlock();
					break;
				}
				if (b == string(DOWNLOAD_DONE))
				{
					block.unlock();
					blockJSON.unlock();
					return true;
				}
			}
			else
				block.unlock();
		};
	}
	blockJSON.unlock();
}