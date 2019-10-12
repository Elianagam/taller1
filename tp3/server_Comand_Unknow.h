#ifndef COMAND_UNKNOW_H
#define COMAND_UNKNOW_H

#include "server_Comand.h"
#include "server_Directory.h"
#include "server_User.h"
#include <string>
#include <vector>

class Comand_Unknow : public Comand {
public:
	std::string response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) override;

	~Comand_Unknow();
};

#endif
