#ifndef _SERVER_H_
#define _SERVER_H_

typedef struct {
	socket_t* socket;
	table_t table;
	char get;
	char verify;
	char reset;
	char put;
} server_t;

void server_init(server_t* self, socket_t* socket);

void server_destroy(server_t* self);

int server_response_prosessing(server_t* server, char* buffer);

int server_send_message(server_t* server, char* buffer);

int server_send_table(server_t* server);

int server_receive_values(server_t* server);

int server_verify(server_t* server);

int servet_response_put(server_t* server);

int main_server(char* port);

#endif

