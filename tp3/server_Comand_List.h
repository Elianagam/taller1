#ifndef COMAND_LIST_H
#define COMAND_LIST_H

#include "server_Comand.h"
#include "server_Directory.h"
#include "server_User.h"
#include <string>
#include <vector>

class Comand_List : public Comand {
public:
	//Comand_List(bool* logged, bool* comand_user);

	std::string response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) override;

	~Comand_List();
};

#endif
