#include <stddef.h>
#include <stdbool.h>
#include "table.h"
#include "socket.h"
#include "client.h"
#include "server.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EXIT_ -2
#define ERROR_ -1

#define SERVER "server"
#define SERVER_LEN 6
#define CLIENT "client"
#define CLIENT_LEN 6

int main(int argc, char* argv[]) {
	int response = 0;
	if (argc < 2) {
		return ERROR_;
	} else if (strncmp(argv[1], SERVER, SERVER_LEN) == 0) {
		response = main_server(argv[2]);
	} else if (strncmp(argv[1], CLIENT, CLIENT_LEN) == 0) {
		response = main_client(argv[2], argv[3]);
	} else {
		return ERROR_;
	}
	return response;
}

