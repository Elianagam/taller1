#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>

class Socket {
private:
	int fd;

	Socket(int new_fd);
public:
	Socket();

	void _init();

	void _relase();

	Socket _accept();

	int _send(void* buffer, size_t length);

	int _receive(char* buffer, size_t length);

	int _connect(char* host, char* port);

	int _bind_and_listen(char* service);

	~Socket();
};

#endif
