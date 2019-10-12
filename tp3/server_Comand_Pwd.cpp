#include "server_Comand_Pwd.h"
#include "server_Directory.h"
#include "server_User.h"
#include <vector>
#include <string>

std::string Comand_Pwd::response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) {
	std::string response;
	user.comand_not_user();
	if (user.is_logged()) {
		response = "257 " + config.find("currentDirectoryMsg")->second + "\n";
	} else {
		response = "530 " + config.find("clientNotLogged")->second + "\n";
	}
	return response;
}

Comand_Pwd::~Comand_Pwd() {}
