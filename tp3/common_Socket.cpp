#define _POSIX_C_SOURCE 200112L

#include "common_Socket.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <cmath>
#include <cerrno>
#include <cstdio>

#define BACKLOG 20
#define EXIT_ERROR -2

Socket::Socket() {}

void Socket::_init() {
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1) {
		throw std::runtime_error("Error Socket Init");
	}
}

Socket::Socket(int new_fd) {
	fd = new_fd;
}

int Socket::_connect(char* host, char* port) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
  	struct addrinfo *results;
	struct addrinfo *ptr;

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(host, port, &hints, &results);

	bool are_we_connected = false;
	int connect_ = 0;
	for (ptr = results; ptr != NULL && are_we_connected == false; 
			ptr = ptr->ai_next) {
			connect_ = connect(fd, results->ai_addr, results->ai_addrlen);
		if (connect_ == -1) {
			are_we_connected = false;
		}
		are_we_connected = (connect_ != -1);
	}
	freeaddrinfo(results);
	if (are_we_connected == false) {
		if (fd == -1) {
			throw std::runtime_error("Error Socket Connect");
		}
	}
	return connect_;
}

int Socket::_send(void* buffer, size_t length) {
	bool socket_valid = true;
	uint32_t bytes_sent = 0;
	int send_ = 0;
	uint8_t* buf = (uint8_t*)buffer;

	while (bytes_sent < length && socket_valid) {
		send_ = send(fd, buf + bytes_sent, length - bytes_sent,
				 MSG_NOSIGNAL);
		if (send_ == -1) {
			socket_valid = false;
		} else if (send_ == 0) {
			socket_valid = false;
		} else {
			bytes_sent += send_;
		}
	}
	if (socket_valid) 
		return bytes_sent;

	throw std::runtime_error("Error Socket Send");
}

int Socket::_receive(char* buffer, size_t length) {
	bool socket_valid = true;
	uint32_t bytes_recv = 0;
	int recv_ = 0;
	uint8_t* buf = (uint8_t*)buffer;

	while (bytes_recv < length && socket_valid) {
		recv_ = recv(fd, buf + bytes_recv, length - bytes_recv, 0); //-1

		if (recv_ == -1) {
			socket_valid = false;
		} else if (recv_ == 0) {
			socket_valid = false;
		} else {
			bytes_recv += recv_; 
		}
	}
	if (socket_valid) return recv_;
	
	throw std::runtime_error("Error Socket Receive");
}

Socket Socket::_accept() {
	int new_fd = accept(fd, NULL, NULL);
	if (new_fd < 0) {
		throw std::runtime_error("Error Socket Accept");
	}
	return Socket(new_fd);
}

int Socket::_bind_and_listen(char* service) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
  	struct addrinfo *results;
	struct addrinfo *ptr;

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, service, &hints, &results);
	
	bool are_we_connected = false;
	int s;
	for (ptr = results; ptr != NULL && are_we_connected == false; 
			ptr = ptr->ai_next) {
		s = bind(fd, results->ai_addr, results->ai_addrlen);
		if (s < 0) {
			are_we_connected = false;
		}
		are_we_connected = (s != -1);
	}
	if (are_we_connected == false) {
		freeaddrinfo(results);
		throw std::runtime_error("Error Socket Bind");
	}
	// Tiene que saber el numero de conneciones que puede aceptar
	s = listen(fd, BACKLOG); 
	if (s < 0) {
		freeaddrinfo(results);
		throw std::runtime_error("Error Socket Bind");
	}

	freeaddrinfo(results);
	return s;
}

void Socket::_relase() {
	shutdown(fd, SHUT_RDWR);
	close(fd);
}

Socket::~Socket() {}
