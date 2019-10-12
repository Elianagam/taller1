#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "server_Thread.h"
#include "common_Socket.h"
#include <map>
#include <string>
#include <vector>

class Acceptor : public Thread {
private:
	Socket socket;
	char* port;
	bool is_not_dead;
	std::vector<Thread*> threads;

	void read_file(char* config_file);
	// carga el archivo de configuracion a un map
public:
	std::map<std::string,std::string> configs;
	
	Acceptor(char* port, char* config_file);

	void run() override;

	void stop() override;

	bool is_dead() override;
};

#endif
