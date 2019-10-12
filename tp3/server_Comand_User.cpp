#include "server_Comand_User.h"
#include "server_Directory.h"
#include "server_User.h"
#include <vector>
#include <string>
#include <iostream>

std::string Comand_User::response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) {

	user.comand_is_user();
	if (value.empty() || config.find("user")->second.compare(value) != 0) {
		user.comand_not_user();
	}
	return "331 " + config.find("passRequired")->second + "\n";
}

Comand_User::~Comand_User() {}
