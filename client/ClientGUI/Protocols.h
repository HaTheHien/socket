#pragma once
#include "ClientSocket.h"
#include <string>
#include <bitset>
#include <iostream>

using namespace std;

void loginProtocol(const string& user, const string& pass, const string& ip);

/**
 * @brief Convert int to 4-bytes 
 * @param num 
 * @return 4-bytes char*
*/
char* intToBytes(const int& num);

/**
 * @brief Convert 4-byte array to int 
 * @param bytes 
 * @return int value
*/
int bytesToInt(const char* bytes);

/**
 * @brief Be careful with offset and amount of bytes
 * @param source 
 * @param dest 
 * @param offset 
 * @param amount 
*/
void charsCopy(char* source, char* dest, const size_t& offset, const size_t& amount);

string charsCat(char* source, const size_t& offset, const size_t& amount);
