#include "File_Management.h"
int main() {
	cout << _version();
	return 0;
}

Container::Container()
{
	ifstream fin(PACKG);
	if (!fin.is_open()) {
		this->Create();
	}

	fin >> file;
}

string Container::version()
{
	if (file.contains("version"))
		return file["version"];
	return string();
}
