#include <stddef.h>
#include <stdbool.h>
#include "table.h"
#include "socket.h"
#include "server.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>

#define ERROR_ -1
#define LEN_TABLE 722
#define DONT_WRITE -2
#define BYTES4 4 
#define BYTE1 1

void server_init(server_t* self, socket_t* socket) {
	self->socket = socket;
	table_t table;
	table_init(&table);
	self->table = table;
	self->get = 'G';
	self->verify = 'V';
	self->put = 'P';
	self->reset = 'R';
}

void server_destroy(server_t* self) {
	table_destroy(&self->table);
	socket_relase(self->socket);
	//free(self->socket);
	//free(self);
}

int server_receive_values(server_t* server) {
	int res;
	int row = 0;
	res = socket_receive(server->socket, &row, BYTE1);

	int col = 0;
	res = socket_receive(server->socket, &col, BYTE1);

	char value[2];
	value[1] = '\0';
	res = socket_receive(server->socket, value, BYTE1);
	int write = table_write_value(&server->table, row, col, value[0]);
	if (write == DONT_WRITE) {
		return write;
	}
	return res;
}

int server_send_table(server_t* server) {
	char* table_buffer = malloc(sizeof(char) * LEN_TABLE);
	table_buffer = table_get(&server->table, table_buffer);

	uint32_t len = LEN_TABLE;
	uint32_t new_len = htonl(len);

	int res = socket_send(server->socket, (char*)&new_len, BYTES4);
	res = socket_send(server->socket, table_buffer, len);
	free(table_buffer);
	return res;
}

int server_send_message(server_t* server, char* message) {
	uint32_t len = strlen(message);
	char* buffer = malloc(sizeof(char) * len);
	strncpy(buffer, message, len);

	uint32_t new_len = htonl(len);
	int res = socket_send(server->socket, (char*)&new_len, BYTES4);
	res = socket_send(server->socket, buffer, len);
	free(buffer);
	return res;
}

int servet_response_put(server_t* server) {
	int res = server_receive_values(server);
	if (res == DONT_WRITE) {
		char message[] = "La celda indicada no es modificable\n\0";
		return server_send_message(server, message);
	} else {
		return server_send_table(server);
	}
	return res;
}

int server_verify(server_t* server) {
	int res;
	if (table_verify(&server->table) == true) {
		char message[] = "OK\n\0";
		res = server_send_message(server, message);
	} else {
		char message[] = "ERROR\n\0";
		res = server_send_message(server, message);
	}
	return res;
}

int server_response_prosessing(server_t* server, char* buffer) {
	if (strncmp(buffer, &server->get, sizeof(char)) == 0) {
		return server_send_table(server);
	} else if (strncmp(buffer, &server->verify, sizeof(char)) == 0) {
		return server_verify(server);
	} else if (strncmp(buffer, &server->reset, sizeof(char)) == 0) {
		table_reset(&server->table);
		return server_send_table(server);
	} else if (strncmp(buffer, &server->put, sizeof(char)) == 0) {
		return servet_response_put(server);
	} else {
		return 0;
	}
	return 0;
}

int main_server(char* port) {
	socket_t socket;
	socket_init(&socket);

	int res = socket_bind_and_listen(&socket, port);
	res = socket_accept(&socket);

	server_t server;
	server_init(&server, &socket);

	char buffer[2];
	buffer[1] = '\0';
	while (res > 0) {
		res = socket_receive(&socket, buffer, sizeof(char));
		if (res == 0)
			break;
		res = server_response_prosessing(&server, buffer);
	}
	server_destroy(&server);
	return 0;
}

