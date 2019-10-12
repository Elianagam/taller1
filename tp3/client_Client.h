#ifndef CLIENT_H
#define CLIENT_H

#include "common_Socket.h"
#include <string>

class Client {
private:
	Socket socket;
	char* host;
	char* port;
public:
	Client(char* host, char* port);

	int send_request(std::string buffer);

	int get_response();
	// recibe de 1 bit a la vez hasta que encuentra el \n

	int get_response_list();
	// Si se envia un comando list espera que llegue un 226 
	// y despues busca el \n

	int main();

	~Client();
};

#endif
