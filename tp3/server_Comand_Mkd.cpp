#include "server_Comand_Mkd.h"
#include "server_Directory.h"
#include "server_User.h"
#include <vector>
#include <string>
#include <algorithm>

std::string Comand_Mkd::response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) {
	std::string response;
	user.comand_not_user();
	if (user.is_logged()) {
		if (!dirs.create_dir(value)) {
			response = "550 " + config.find("mkdFailed")->second + "\n";
		} else {
			response = "257 \"" + value + "\" " + config.find("mkdSuccess")->second + "\n";
		}
	} else {
		response = "530 " + config.find("clientNotLogged")->second + "\n";
	}
	return response;
}

Comand_Mkd::~Comand_Mkd() {}
