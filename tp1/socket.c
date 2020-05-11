#define _POSIX_C_SOURCE 200112L

#include <stddef.h>
#include "socket.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#define ERROR_ -1
#define BACKLOG 1

#define ERROR_INIT "Error Socket Init\n"
#define ERROR_ACCEPT "Error Accept\n"

void socket_init(socket_t* self) {
	self->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (self->fd == ERROR_) { 
		printf(ERROR_INIT);
	}
}

void socket_relase(socket_t* socket){
	shutdown(socket->fd, SHUT_RDWR);
	close(socket->fd);
}

int socket_connect(socket_t* socket, const char* host, const char* server) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	struct addrinfo *results;
	struct addrinfo *ptr;

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(host, server, &hints, &results);

	bool are_we_connected = false;
	int connect_;
	for (ptr = results; ptr != NULL && are_we_connected == false; 
			ptr = ptr->ai_next) {
		connect_ = connect(socket->fd, results->ai_addr, results->ai_addrlen);
		if (connect_ == ERROR_) {
			are_we_connected = false;
		}
		are_we_connected = (connect_ != ERROR_);
	}
	freeaddrinfo(results);
	if (are_we_connected == false) {
		return ERROR_;
	}
	return connect_;
}

int socket_send(socket_t* self, void* buffer, size_t length) {
	bool socket_valid = true;
	int bytes_sent = 0;
	int send_ = 0;
	uint8_t* buf = buffer;

	while (bytes_sent < length && socket_valid) {
		send_ = send(self->fd, buf + bytes_sent, length - bytes_sent,
				 MSG_NOSIGNAL);

		if (send_ == ERROR_) {
			socket_valid = false;
		} else if (send_ == 0) {
			socket_valid = false;
		} else {
			bytes_sent += send_;
		}
	}
	if (socket_valid) return bytes_sent;

	return ERROR_;
}

int socket_receive(socket_t* self, void* buffer, size_t length) {
	bool socket_valid = true;
	int bytes_recv = 0;
	int recv_ = 0;
	uint8_t* buf = buffer;

	while (bytes_recv < length && socket_valid == true) {
		recv_ = recv(self->fd, buf + bytes_recv, length - bytes_recv, 0); //-1

		if (recv_ == ERROR_) {
			socket_valid = false;
		} else if (recv_ == 0) {
			socket_valid = false;
		} else {
			bytes_recv += recv_; 
		}
	}
	if (socket_valid) return recv_;

	return ERROR_;
}

int socket_accept(socket_t* self) {
	int new_fd = accept(self->fd, NULL, NULL);
	if (new_fd < 0) {
		printf(ERROR_ACCEPT);
		return ERROR_;
	}
	return new_fd;
}

int socket_bind_and_listen(socket_t* socket, const char* service) {
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
		s = bind(socket->fd, results->ai_addr, results->ai_addrlen);
		if (s < 0) {
			are_we_connected = false;
		}
		are_we_connected = (s != ERROR_);
	}
	if (are_we_connected == false) {
		return ERROR_;
	}
	// Tiene que saber el numero de conneciones que puede aceptar
	s = listen(socket->fd, BACKLOG); 
	if (s < 0) {
		freeaddrinfo(results);
		return ERROR_;
	}

	freeaddrinfo(results);
	return s;
}
