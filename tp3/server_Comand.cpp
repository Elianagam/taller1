#include "server_Comand.h"
#include "server_Comand_List.h"
#include "server_Comand_User.h"
#include "server_Comand_Pass.h"
#include "server_Comand_Syst.h"
#include "server_Comand_Help.h"
#include "server_Comand_Pwd.h"
#include "server_Comand_Mkd.h"
#include "server_Comand_Quit.h"
#include "server_Comand_Rmd.h"
#include "server_Comand_Unknow.h"
#include <iostream> 
#include <utility> 
#include <string>
#include <vector>
#include <bits/stdc++.h> 

Comand* Comand::get_comand(const std::string& client_request) {
	if (client_request.compare("USER") == 0) {
		return new Comand_User;
	} else if (client_request.compare("PASS") == 0) {
		return new Comand_Pass;
	} else if (client_request.compare("LIST") == 0) {
		return new Comand_List;
	} else if (client_request.compare("HELP") == 0) {
		return new Comand_Help;
	} else if (client_request.compare("SYST") == 0) {
		return new Comand_Syst;
	} else if (client_request.compare("MKD") == 0) {
		return new Comand_Mkd;
	} else if (client_request.compare("PWD") == 0) {
		return new Comand_Pwd;
	} else if (client_request.compare("RMD") == 0) {
		return new Comand_Rmd;
	} else if (client_request.compare("QUIT") == 0) {
		return new Comand_Quit;
	} else {
		return new Comand_Unknow;
	}
}

Comand::~Comand() {}
