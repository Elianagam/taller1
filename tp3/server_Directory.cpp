#include "server_Directory.h"
#include <mutex>
#include <string>
#include <vector>
#include <algorithm>

Directory::Directory() {}

bool sort_dirs(std::string dir1, std::string dir2) {
	return dir1 < dir2;
}

bool Directory::delete_dir(std::string dir_name) {
	std::unique_lock<std::mutex> lock(mutex);
	std::vector<std::string>::iterator position = std::find(dirs.begin(), dirs.end(), dir_name);
	if (position != dirs.end()) {
    	dirs.erase(position);
    	return true;
    }
    return false;
}

bool Directory::create_dir(std::string dir_name) {
	std::unique_lock<std::mutex> lock(mutex);
	if (std::find(dirs.begin(), dirs.end(), dir_name) == dirs.end()) {
		dirs.push_back(dir_name);
		return true;
	} 
	return false;
}

std::string Directory::get_dirs() {
	std::unique_lock<std::mutex> lock(mutex);
	std::string lines = "";
	// en orden alfabetico
	std::sort(dirs.begin(), dirs.end(), sort_dirs);
	for (uint32_t i = 0; i < dirs.size(); i++) {
		lines += "drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34 " + dirs.at(i) + "\n";
	}
	return lines;
}

Directory::Directory(Directory&& other) {
	this->dirs = std::move(other.dirs);
}

Directory& Directory::operator=(Directory&& other) {
	this->dirs = std::move(other.dirs);
	return *this;
}
