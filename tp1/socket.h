#ifndef _SOCKET_H_
#define _SOCKET_H_

typedef struct {
    int fd;
} socket_t;

void socket_init(socket_t* socket);

void socket_relase(socket_t* socket);

int socket_accept(socket_t* self);

int socket_send(socket_t* self, void* buffer, size_t length);

int socket_receive(socket_t* self, void* buffer, size_t length);

int socket_connect(socket_t* socket, const char* host, const char* server);

int socket_bind_and_listen(socket_t* socket, const char* service);

#endif
