#include "server_Comand_Rmd.h"
#include "server_Directory.h"
#include "server_User.h"
#include <vector>
#include <string>
#include <algorithm>

std::string Comand_Rmd::response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) {
	std::string response;
	user.comand_not_user();
	if (user.is_logged()) {
		if (dirs.delete_dir(value)) {
			response = "250 \"" + value + "\" " + config.find("rmdSuccess")->second + "\n";
		} else {
			response = "550 " + config.find("rmdFailed")->second + "\n";
		}
	} else {
		response = "530 " + config.find("clientNotLogged")->second + "\n";
	}
	return response;
}

Comand_Rmd::~Comand_Rmd() {}
