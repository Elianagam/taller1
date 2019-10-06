#include <stddef.h>
#include "socket.h"
#include "client.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>

#define EXIT_ -2
#define ERROR_ -1
#define VALUE_POS 4
#define ROW_POS 9
#define COL_POS 11
#define LEN_TABLE 722
#define MAX_INPUT_SIZE 15
#define BYTES4 4
#define BYTE1 1

// FUNCIONES AUXILIARES ------------------------
int get_value(char* buffer) {
	char pos = buffer[VALUE_POS];
	if (atoi(&pos) > 0) {
		return pos;
	}
	return 'E';
}

int get_row(char* buffer) {
	int pos = atoi(&buffer[ROW_POS]);
	if (pos > 0) {
		return pos;
	}
	return ERROR_;
}

int get_col(char* buffer) {
	int pos = atoi(&buffer[COL_POS]);
	if (pos > 0) {
		return pos;
	}
	return ERROR_;
}

int check_put_response(char* buffer) {
	int value = 0;
	int row = 0;
	int col = 0;
	int reg = sscanf(buffer, "put %d in %d,%d", &value, &row, &col);

	if (reg == 3) {
		if (col <= 0 || col > 9 || row <= 0 || row > 9) {
			fprintf(stderr,"Error en los índices. Rango soportado: [1,9]\n");
			return ERROR_;
		}
		if (value <= 0 || value > 9) {
			fprintf(stderr, "Error en el valor ingresado. Rango soportado: [1,9]\n");
			return ERROR_;
		}
	}
	return 0;
}

// ----------------------------------------------
void client_init(client_t* self, socket_t* socket) {
	self->socket = socket;
	self->get = "get\0";
	self->reset = "reset\0";
	self->verify = "verify\0";
	self->exit = "exit\0";
	}

void client_destroy(client_t* self) {
	socket_relase(self->socket);
	//free(self->socket);
	//free(self);
}

int client_send_put(client_t* client, char* buffer) {
	int res;
	res = socket_send(client->socket, "P", BYTE1);
	uint8_t row = get_row(buffer);
	res = socket_send(client->socket, &row, BYTE1);
	
	uint8_t col = get_col(buffer);	
	res = socket_send(client->socket, &col, BYTE1);

	char value[2];
	value[0] = get_value(buffer);
	value[1] = '\0';
	res = socket_send(client->socket, value, BYTE1);
	
	return res;
}

int client_get(client_t* client) {
	uint32_t len;
	int res = socket_receive(client->socket, &len, BYTES4);
	len = ntohl(len);
	
	char to_print[LEN_TABLE];
	to_print[len] = '\0';
	
	res = socket_receive(client->socket, to_print, len);
	printf("%s", to_print);
	return res;
}

int client_request_prosessing(client_t* client, char* buffer) {
	int res = EXIT_;
	if (strncmp(buffer, client->get, 3) == 0) {
		res = socket_send(client->socket, "G", BYTE1);
		res = client_get(client);
	} else if (strncmp(buffer, client->verify, 6) == 0) {
		res = socket_send(client->socket, "V", BYTE1);
		res = client_get(client);
	} else if (strncmp(buffer, client->reset, 5) == 0) {
		res = socket_send(client->socket, "R", BYTE1);
		res = client_get(client);
		
	} else if (strncmp(buffer, client->exit, 4) == 0) {
		return EXIT_;
	} else if (check_put_response(buffer) == 0) {
		res = client_send_put(client, buffer);
		res = client_get(client);
	} else {
		res = ERROR_;
	}
	return res;
}

int main_client(char* host, char* port) {
	socket_t socket;
	socket_init(&socket);
	int res = socket_connect(&socket, host, port);

	client_t client;
	client_init(&client, &socket);

	char buffer[MAX_INPUT_SIZE];
	char* c;
	while (res != EXIT_) {
		c = fgets(buffer, MAX_INPUT_SIZE, stdin);
		if (c == NULL) break;
		res = client_request_prosessing(&client, buffer);
	}
	client_destroy(&client);
	return 0;
}

