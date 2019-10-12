#include "server_Client_Thread.h"
#include "server_Thread.h"
#include "common_Socket.h"
#include "server_Comand.h"
#include "server_Directory.h"
#include "server_User.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <algorithm>
#include <string>
#include <utility> 
#include <map>
#include <exception>
#include <cmath>
#include <cerrno>
#include <cstdio>

#define EXIT_ERROR -2

Client_Thread::Client_Thread(std::map<std::string,std::string> configs, Socket socket,
	Directory &dirs) : 
	configs(configs), 
	is_not_dead(true),
	socket(socket),
	dirs(dirs) {
	}

int Client_Thread::send_request(const std::string& buffer) {
	uint32_t len = buffer.size();
	char* new_buffer = (char*)buffer.c_str();
	int res = socket._send(new_buffer, len);
	return res;
}

std::string Client_Thread::get_response() {
	std::string char_res;
	char response = '0';
	int res = 1;
	while(response != '\n' && res > 0) {
		res = socket._receive(&response, 1);
		if (response != '\n') {
			char_res.insert(char_res.end(), response);
		}
	}
	return char_res;
}

int Client_Thread::send_start() {
	std::string buffer = "220 " + configs["newClient"] + "\n";
	uint32_t len = buffer.size();
	char* new_buffer = (char*)buffer.c_str();
	int res = socket._send(new_buffer, len);
	return res;
}

std::string Client_Thread::response_prossesing(const std::string& buffer) {
	Comand* new_comand;
	std::string message;

	auto delimiter = buffer.find(" ");
	if (delimiter != std::string::npos) {
		std::string comand = buffer.substr(0, delimiter);
		std::string parameter = buffer.substr(delimiter + 1);

		new_comand = Comand::get_comand(comand);
		message = new_comand->response(configs, dirs, user, parameter);
	} else {
		new_comand = Comand::get_comand(buffer);
		message = new_comand->response(configs, dirs, user);
	}
	delete new_comand;
	return message;
}

void Client_Thread::run() {
	send_start();
	while(is_not_dead) {
		try {
			std::string buffer = get_response();
			std::string message;
			if (!buffer.empty()) {
				message = response_prossesing(buffer);
			} else {
				message = "\n";
			}
			send_request(message);
			if (buffer.compare("QUIT") == 0) break;
		} catch (std::runtime_error e) {
			is_not_dead = false;
		}
	}
	stop();
}

void Client_Thread::stop() {
	is_not_dead = false;
}

bool Client_Thread::is_dead() {
	return !is_not_dead;
}

Client_Thread::~Client_Thread() {
	socket._relase();
}
