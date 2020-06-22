#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include "json.hpp"
#define PACKG "file.json"
using namespace nlohmann;
using namespace std;

string _version() {

	time_t rawtime;
	struct tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo ,&rawtime);
	string iResult = 
		to_string(timeinfo.tm_year) + "-" +
		to_string(timeinfo.tm_yday) + "-" + 
		to_string(timeinfo.tm_hour) + "-" +
		to_string(timeinfo.tm_min) + "-" + 
		to_string(timeinfo.tm_sec);
	return iResult;
}

class Container {
private:
	json file;
public:
	Container();
	void Create();
};