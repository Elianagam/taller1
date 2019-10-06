#ifndef _CLIENT_H_
#define _CLIENT_H_

typedef struct {
	socket_t* socket;
	char* get;
	char* verify;
	char* reset;
	char* exit;
} client_t;

void client_init(client_t* self, socket_t* socket);

void client_destroy(client_t* self);

int client_request_prosessing(client_t* client, char* buffer);

int check_put_response(char* buffer);

int client_send_put(client_t* client, char* buffer);

int client_verify(client_t* client);

int client_reset(client_t* client);

int client_get(client_t* client);

int main_client(char* host, char* port);

#endif

