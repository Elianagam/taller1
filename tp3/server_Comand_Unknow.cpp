#include "server_Comand_Unknow.h"
#include "server_Directory.h"
#include "server_User.h"
#include <vector>
#include <string>

std::string Comand_Unknow::response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) {
	user.comand_not_user();
	return "530 Unknown command.\n";
}

Comand_Unknow::~Comand_Unknow() {}
