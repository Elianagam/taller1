#ifndef COMAND_USER_H
#define COMAND_USER_H

#include <vector>
#include <string>
#include "server_Comand.h"
#include "server_Directory.h"
#include "server_User.h"

class Comand_User : public Comand {
public:
	std::string response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) override;
	// devuelve el mensaje de ingrese password.
	// si no es correcto, comand_user sera falso
	
	~Comand_User();
};

#endif
