#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include "windows.h"
#define PACKG	"file.json"
#define ROOT	"root/"
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
protected:
	void share(vector<string> list, int mode);
	void save();
	void update();
public:
	Container();
	void Create();
	string version();
	bool addDocument(string name, int size, string owner, vector<string>list);
	bool deleteDocument(string name, string username);
	string get(string name, string username);
	uint8_t size(string name);
	vector<string> listDocument();
};