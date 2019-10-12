#include "server_Thread.h"
#include "server_Acceptor.h"
#include "common_Socket.h"
#include "server_Client_Thread.h"
#include "server_Directory.h"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cerrno>
#include <cstdio>

Acceptor::Acceptor(char* port, char* config_file) :
	port(port), is_not_dead(true) {
		socket._init();
		read_file(config_file);
}

void Acceptor::read_file(char* config_file) {
	std::ifstream config(config_file);
	std::string line;

	while (getline(config, line)) {
		auto delimiter = line.find("=");
		std::string comand = line.substr(0, delimiter);
		std::string message = line.substr(delimiter + 1);
		configs[comand] = message;
	}
	config.close();
}

void Acceptor::run() {
	socket._bind_and_listen(port);
	
	Directory dirs;	
	while(is_not_dead) {
		try {
			Socket new_socket = socket._accept();
			threads.push_back(new Client_Thread(configs, new_socket, dirs));
			threads.back()->start();
			for (uint32_t i = 0; i < threads.size(); i++) {
				if (threads[i]->is_dead()) {
					threads[i]->join();
					delete threads[i];
					threads.erase(threads.begin() + i);
				}
			}
		} catch (std::runtime_error e) {
			is_not_dead = false;
			break;
		}
	}
	//stop();
}

void Acceptor::stop() {
	socket._relase();
	is_not_dead = false;
	for (uint32_t i = 0; i < threads.size(); i++) {
		threads[i]->stop();
		threads[i]->join();
		delete threads[i];
	}
}

bool Acceptor::is_dead() {
	return !is_not_dead;
}
