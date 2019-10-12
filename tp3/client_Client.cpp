#include "client_Client.h"
#include "common_Socket.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

Client::Client(char* host, char* port) : 
	host(host), port(port) {
		socket._init();
	}

int Client::send_request(std::string buffer) {
	uint32_t len = buffer.size();
	char* new_buffer = (char*)buffer.c_str();
	new_buffer[len] = '\n';
	int res = socket._send(new_buffer, len+1);
	return res;
}

int Client::get_response() {
	std::string char_res;
	char response = '0';
	int res = 1;
	while(response != '\n' && res >= 0) {
		res = socket._receive(&response, 1);
		if (response != '\n') {
			char_res.insert(char_res.end(), response);
		}
	}
	if (!char_res.empty()) {
		std::cout << char_res << "\n";
	} else {
		std::cout << char_res;
	}
	char_res.clear();
	return res;
}

int Client::get_response_list() {
	std::string char_res;
	char response = '0';
	int res = 1;
	try {
		res = socket._receive(&response, 1);
		char_res.insert(char_res.end(), response);
		if (response == '1') {
			while (char_res.find("226") == std::string::npos) {
				res = socket._receive(&response, 1);
				char_res.insert(char_res.end(), response);
			}
		}
		while(response != '\n'  && res >= 0) {
			res = socket._receive(&response, 1);
			char_res.insert(char_res.end(), response);
		}
	} catch (std::runtime_error e) {
		return -2;
	}
	std::cout << char_res;
	char_res.clear();
	return res;
}

int Client::main() {
	socket._connect(host, port);
	std::string buffer;
	int res = 1;
	res = get_response();
	while(res > 0 && !std::cin.eof()) {
		try { 
			std::getline(std::cin, buffer);
			res = send_request(buffer);
			if (buffer.compare("LIST") == 0) {
				res = get_response_list();
			} else {
				res = get_response();
			}
			if (buffer.compare("QUIT") == 0 || res <= 0 ||
				std::cin.eof()) break;
		} catch (std::runtime_error e) {
			std::cout << e.what() << std::endl;
			return 0;
		}
	}
	return 0;
}

Client::~Client() {
	socket._relase();
}
