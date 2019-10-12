#ifndef COMAND_PASS_H
#define COMAND_PASS_H

#include "server_Comand.h"
#include "server_Directory.h"
#include "server_User.h"
#include <string>
#include <vector>

class Comand_Pass : public Comand {
public:

	std::string response(const std::map<std::string,std::string>& config,
		Directory &dirs, User &user, std::string value) override;
	// Si el anterior comando fue usuario (y fue correcto)
	// y la contraseña es correcta se iniciara sesion
	~Comand_Pass();
};

#endif
