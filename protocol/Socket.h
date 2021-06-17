#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <cstddef>

//Implementa una interfáz más simple para interactuar con los socket.
class Socket{
    private:
        int fd;
        bool is_server;

        explicit Socket(int fd);

    public:
        //Crea un socket. Si el booleano is_server esta seteado se crea un 
        //socket aceptador.
        Socket(const char *host, const char* service, bool is_server);
        
        //Constructor por movimiento
        Socket(Socket&& other); 
        
        //Acepta una conexión a un cliente, solo la pueden usar los socket 
        //aceptadores. Devuelve el socket que representa esa conexión.
        Socket accept_one();

        //Cierra la conexión en el socket.
        void close_socket();

        //Envía una tira de bytes de longitud `len`.
        void send_buffer(const char *buf, size_t len);
        //Recibe una tira de bytes de longitud `len`.
        void recv_buffer(char *buf, size_t len);

        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;

        ~Socket();
};

#endif
