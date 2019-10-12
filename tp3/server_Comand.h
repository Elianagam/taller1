#ifndef COMAND_H
#define COMAND_H

#include <map>
#include <vector>
#include <string>
#include "server_Directory.h"
#include "server_User.h"

class Comand {
public:
	virtual std::string response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value="") = 0;

	static Comand* get_comand(const std::string& client_request);

	virtual ~Comand();
};

#endif
