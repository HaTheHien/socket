#include "File_Management.h"

#define TEST // block this line to run .-.
#ifdef TEST
int main() {
	json j;
	j["list"] = {};
	vector<string> v;
	v.push_back("a");
	j["list"] = v;
	for (int i = 0; i < j["list"].size(); i++) {
		cout << j["list"][i].get<string>();
	}
	return 0;
}
#endif // TEST

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

void Container::share(vector<string> list, int mode)
{
}

void Container::save()
{
	ofstream fout(PACKG);
	fout << file;
	fout.close();
}

bool Container::addDocument(string name, int size, string owner, vector<string>list)
{
	if (file["documents"].contains(name)) {
		return false;
	}
	json docInfo = {
		{"size", size},
		{"link", ROOT},
		{"owner", owner},
		{"list", {}},
	};
	docInfo["link"] += name;
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

int Container::size(string name)
{
	if (file["documents"].contains(name)) {
		return file["document"][name]["size"].get<int>();
	}
	return 0;
}

void Container::update()
{
	file["version"] = _version();
	save();
}
