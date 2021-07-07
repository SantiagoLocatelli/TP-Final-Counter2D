#include "Socket.h"
#include "GeneralException.h"
#include "SocketClosedException.h"

#include <string>
#include <cstring>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define FAILURE -1
#define SUCCESS 0
#define NO_SOCKET -1

Socket::Socket(const char *host, const char* service, bool is_server)
: is_server(is_server){
    struct addrinfo hints;
    struct addrinfo* result;

    std::memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    if (is_server){
        hints.ai_flags = AI_PASSIVE;
    }
    int err = getaddrinfo(host, service, &hints, &result);
    if (err != SUCCESS){
        throw GeneralException("Fallo en `getaddrinfo`: " 
        + std::string(gai_strerror(err)) + ".\n");
    }

    int skt;
    bool created = false;
    for (struct addrinfo* ptr = result; 
         ptr != NULL && !created; ptr = ptr->ai_next){
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (skt != FAILURE) {
            if (is_server){
                int option = 1;
                err = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
                if (err == FAILURE){
                    break;
                }
                err = bind(skt, ptr->ai_addr, ptr->ai_addrlen);
            } else {
                err = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
            }

            if (err == FAILURE){
                close(skt);
            } else {
                created = true;
            }
        }
    }

    freeaddrinfo(result);

    if (!created){
        throw GeneralException("Imposible crear socket.\n");
    }

    if (is_server){
        if (listen(skt, 10) == FAILURE){
            close(skt);
            throw GeneralException("Fallo en `listen`: " 
            + std::string(strerror(errno)) + ".\n");
        }
    }

    fd = skt;
}

Socket::Socket(int fd):fd(fd), is_server(false){}

Socket::Socket(Socket&& other){
    this->fd = other.fd;
    this->is_server = other.is_server;

    other.fd = NO_SOCKET;
}

Socket Socket::accept_one(){
    if (fd == NO_SOCKET){
        throw GeneralException("El socket no está conectado.\n");
    }

    if (!is_server){
        throw GeneralException("Un cliente no puede aceptar.\n");
    }

    int peerskt = accept(fd, NULL, NULL);
    if (peerskt == FAILURE){
        throw SocketClosedException();
    }

    Socket peer(peerskt);

    return peer;
}

void Socket::close_socket(){
    if (fd != NO_SOCKET){
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
    fd = NO_SOCKET;
}

void Socket::send_buffer(const char *buf, size_t len){
    if (fd == NO_SOCKET){
        throw GeneralException("El socket no está conectado.\n");
    }

    size_t bytes_sent = 0;
    int r = 0;

    while (bytes_sent < len && r != FAILURE){
        r = send(fd, &(buf[bytes_sent]), len-bytes_sent, MSG_NOSIGNAL);
        if (r == FAILURE) 
            throw GeneralException("Fallo en `send`: " 
            + std::string(strerror(errno)) + ".\n");
        else 
            bytes_sent += r;
    }
}

void Socket::recv_buffer(char *buf, size_t len){
    if (fd == NO_SOCKET){
        throw GeneralException("El socket no está conectado.\n");
    }
    size_t bytes_recieved = 0;

    while (bytes_recieved < len){
        int r = recv(fd, &(buf[bytes_recieved]), len - bytes_recieved, 0);
        if (r == FAILURE) 
            throw GeneralException("Fallo en `recieve`: " 
            + std::string(strerror(errno)) + ".\n");
        else if (r == 0)
            throw SocketClosedException();
        else
            bytes_recieved += r;
    }
}

Socket::~Socket(){
    if (fd != NO_SOCKET){
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
}
