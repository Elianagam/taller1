#ifndef CLIENT_THREAD_H
#define CLIENT_THREAD_H

#include "common_Socket.h"
#include "server_Comand.h"
#include "server_Thread.h"
#include "server_Directory.h"
#include "server_User.h"
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <string>
#include <utility> 
#include <map>

class Client_Thread : public Thread {
private:
	std::map<std::string,std::string> configs;
	bool is_not_dead;
	Socket socket;
	Directory &dirs;
	User user;
	
	std::string response_prossesing(const std::string& buffer);
	// a partir del string recibido busca la respuesta
	// que corresponda a lo pedido

	int send_request(const std::string& buffer);
	// envia respuesta al cliente

	int send_start();
	// envia mensaje de bienvenida

	std::string get_response();
	// Obtiene el comando enviado por el cliente
public:
	Client_Thread(std::map<std::string,std::string> configs,
		Socket socket, Directory &dirs);

	void run() override;

	void stop() override;

	bool is_dead() override;

	~Client_Thread();
};

#endif
