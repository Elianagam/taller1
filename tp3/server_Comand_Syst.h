#ifndef COMAND_SYST_H
#define COMAND_SYST_H

#include "server_Comand.h"
#include "server_Directory.h"
#include "server_User.h"
#include <string>
#include <vector>

class Comand_Syst : public Comand {
public:
	std::string response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) override;

	~Comand_Syst();
};

#endif
