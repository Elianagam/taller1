#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <vector>
#include <mutex>

class Directory {
private:
	std::vector<std::string> dirs;
	std::mutex mutex;
public:
	Directory();
	
	bool delete_dir(std::string dir_name);
	//elimina el directorio si existiera, si no existe retorna falses

	bool create_dir(std::string dir_name);
	// si no existe el directorio lo crea, si existe retorna false

	std::string get_dirs();
	// el string contiene una lista ordenada de directorios

	Directory(const Directory&) = delete;

	Directory& operator=(const Directory&) = delete;

	Directory(Directory&& other);

	Directory& operator=(Directory&& other);

};

#endif
