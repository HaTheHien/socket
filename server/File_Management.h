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

class Container {
private:
	json file;
protected:
	void share(vector<string> list, int mode, string name);
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
	void createCache(vector<string>share_username);
	vector<string> unpackg();
};