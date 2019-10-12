#include "server_Comand_Help.h"
#include "server_User.h"
#include "server_Directory.h"
#include <vector>
#include <string>

std::string Comand_Help::response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) {
	std::string response;
	user.comand_not_user();
	if (user.is_logged()) {
		response = "214 HELP LIST MKD PASS PWD QUIT RMD SYST USER\n";
	} else {
		response = "530 " + config.find("clientNotLogged")->second + "\n";
	}
	return response;
}

Comand_Help::~Comand_Help() {}
