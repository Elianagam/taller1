#include "server_Comand_Quit.h"
#include "server_Directory.h"
#include "server_User.h"
#include <vector>
#include <string>

std::string Comand_Quit::response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) {
	user.comand_not_user();
	return "221 " + config.find("quitSuccess")->second + "\n";
}

Comand_Quit::~Comand_Quit() {}
