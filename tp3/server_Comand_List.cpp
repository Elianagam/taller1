#include "server_Comand_List.h"
#include "server_Directory.h"
#include "server_User.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string Comand_List::response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) {
	std::string response;
	user.comand_not_user();
	if (user.is_logged()) {
		response = "150 " + config.find("listBegin")->second + "\n";
		response += dirs.get_dirs();
		response += "226 " + config.find("listEnd")->second + "\n";
	} else {
		response = "530 " + config.find("clientNotLogged")->second + "\n";
	}
	return response;
}

Comand_List::~Comand_List() {}
