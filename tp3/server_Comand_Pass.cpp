#include "server_Comand_Pass.h"
#include "server_Directory.h"
#include "server_User.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility> 
#include <bits/stdc++.h> 

std::string Comand_Pass::response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) {
	std::string response;
	if (config.find("password")->second.compare(value) == 0 && user.last_comand_was_user()) {
		user.comand_not_user();
		user.loggin();
		response = "230 " + config.find("loginSuccess")->second + "\n";
	} else {
		user.comand_not_user();
		response = "530 " + config.find("loginFailed")->second + "\n";
	}
	return response;
}

Comand_Pass::~Comand_Pass() {}
