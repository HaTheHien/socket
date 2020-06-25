#include "Protocols.h"
#include "Header.h"

void loginProtocol(const string& user, const string& pass, const string& ip)
{
	//Create socket
	ClientSocket socket;
	socket.ConnectToServer(ip);

	//<4 byte: size of package> <4byte: LOGIN> <Username> <space> <Password>
	//char* packetSize = intToBytes(4 + 4 + user.length() + 1 + pass.length());
	string packSize = to_string(4 + 4 + user.length() + 1 + pass.length());
	if (packSize.length() < 4)
	{
		for (int i = packSize.length(); i < 4; i++)
		{
			packSize = "0" + packSize;
		}
	}
	//bitset<8 * 4> packSize(4 + 4 + user.length() + 1 + pass.length());
	
	string dataToSend;	
	dataToSend +=  packSize + string(LOGIN) + user + " " + pass; //1234 is LOGIN code

	//Send login request to server
	socket.Send(dataToSend.c_str());

	//Wait for result
	int iReceived = socket.Receive();
	if (iReceived == 0)
	{
		return;
	}
	char* anwser = socket.getBuffer();

	//Resolve result
	char packetSize[4];
	charsCopy(anwser, packetSize, 0, 4);
	int iSize = bytesToInt(packetSize);

	string feedBackCode = charsCat(anwser, 4, 4);
	if (feedBackCode == OK)
	{
		string jsonVersion = charsCat(anwser, 8, 0);
		throw exception(jsonVersion.c_str());
		//Do json stuffs
	}
	else //Not OK
	{
		throw exception("Not OK!");
		return;
	}
	
}

char* intToBytes(const int& num)
{
	char ret[4];
	for (int i = 0; i < 4; i++)
	{
		ret[3 - 1] = (num >> (i * 8));
	}
	return ret;
}

int bytesToInt(const char* bytes)
{
	int ret;
	std::memcpy(&ret, bytes, 4);
	return ret;
}

void charsCopy(char* source, char* dest, const size_t& offset, const size_t& amount)
{
	for (int i = offset; i < offset + amount; i++)
	{
		dest[i] = source[i];
	}
}

/**
 * @brief Version 2 of charsCopy, return string. If leave amount as default, copy to the end
 * @param source 
 * @param offset 
 * @param amount 
 * @return 
*/
string charsCat(char* source, const size_t& offset, const size_t& amount = 0)
{
	string ret;
	if (amount == 0)
	{
		int i = offset;
		do 
		{
			ret += source[i];
			i++;
		} while (source[i] != '\0');
	}
	else
	{
		for (int i = offset; i < offset + amount; i++)
		{
			ret += source[i];
		}
	}
	return ret;
}

