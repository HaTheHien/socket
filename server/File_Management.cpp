#include "File_Management.h"

#define TEST // block this line to run .-.
#ifdef TEST
int main() {
	json j;
	j["list"] = {};
	j["list"].push_back(3);
	j["list"].push_back(0);

	cout << j.dump(4);
	json k;
	k["list"] = {};
	k["list"].push_back(0);
	k["list"].push_back(0);
	k["list"].push_back(1);
	k.merge_patch(j);
	cout << k.dump(3);
	
	return 0;
}
#endif
string _version() {

	time_t rawtime;
	struct tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	string iResult =
		to_string(timeinfo.tm_year) + "-" +
		to_string(timeinfo.tm_yday) + "-" +
		to_string(timeinfo.tm_hour) + "-" +
		to_string(timeinfo.tm_min) + "-" +
		to_string(timeinfo.tm_sec);
	return iResult;
}
Container::Container()
{
	ifstream fin(PACKG);
	if (!fin.is_open()) {
		this->Create();
		return;
	}
	fin >> file;
	fin.close();
}

void Container::Create()
{
	file["version"] = _version();
	file["documents"] = {};
	update();
}

string Container::version()
{
	if (file.contains("version"))
		return file["version"].get<string>();
	return string();
}

int BinarySearch(vector<string> arr, int n, string key) {
	int l = 0;
	int r = n - 1;
	int mid = (r - l) / 2 + l;

	while (l <= r) {
		if (key == arr[mid]) {
			return mid;
		}
		if (key < arr[mid]) {
			r = mid - 1;
			mid = (r - l) / 2 + l;
		}
		if (key > arr[mid]) {
			l = mid + 1;
			mid = (r - l) / 2 + l;
		}
	}
	return l;
}

void Container::share(vector<string> list, int mode)
{
	vector<string> _user;
	if (mode) {
		for (auto key : list) {
			if (_user.size() == 0) {
				_user.push_back(key);
			}
			else {
				int loc = BinarySearch(_user, _user.size(), key);
				if (loc > _user.size() - 1) {
					_user.push_back(key);
				}
				else {
					auto i = _user.begin();
					i += loc;
					_user.insert(i, key);
				}
			}
		}
	}
	else {

	}
}

void Container::save()
{
	ofstream fout(PACKG);
	fout <<std::setw(4) << file;
	fout.close();
}

bool Container::addDocument(string name, int size, string owner, vector<string>list)
{
	if (file["documents"].contains(name)) {
		return false;
	}
	json docInfo = {
		{"size", size},
		{"link", string(ROOT) + name},
		{"owner", owner},
		{"list", {}},
	};
	//docInfo["link"] += json(name);
	docInfo["list"] = list;
	file["documents"][name] = docInfo;
	update();
	return true;
}

bool Container::deleteDocument(string name, string username)
{
	if (file["documents"].contains(name)) {
		if (file["documents"][name]["owner"] == username) {
			return false;
		}
		string link = file["documents"][name]["link"];
		file["documents"].erase(name);
		string cmd = "rm " + link;
		system(cmd.c_str());
		update();
		return true;
	}
	return false;
}

string Container::get(string name, string username)
{
	if (file["documents"].contains(name)) {
		if (file["documents"][name]["owner"] == username) {
			return file["documents"][name]["link"].get<string>();
		}
		else if (!file["documents"][name]["list"].size()) {
			return file["documents"][name]["link"].get<string>();
		}
		else {
			for (int i = 0; i < file["documents"][name]["list"].size(); i++) {
				if (file["documents"][name]["list"][i].get<string>() == username) {
					return file["documents"][name]["link"].get<string>();
				};
			}
		}

	}
	return string();
}

uint8_t Container::size(string name)
{
	if (file["documents"].contains(name)) {
		return file["document"][name]["size"].get<uint8_t>();
	}
	return 0;
}

vector<string> Container::listDocument()
{
	vector<string> list;
	for (json::iterator it = file["documents"].begin(); it != file["documents"].end(); ++it) {
		list.push_back(it.key());
	}
	return list;
}

void Container::update()
{
	file["version"] = _version();
	save();
}