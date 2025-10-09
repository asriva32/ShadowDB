#ifndef CLIENT_H
#define CLIENT_H

#include <unistd.h>
#include "DB/KVStore.h"

class Client{

public:
    Client() = default;
    Client(int fd) : client_fd(fd) {}
    ~Client() { if (client_fd != -1) close(client_fd); }

    int get_fd() const { return client_fd; }
    
    void handle_request(KVStore &kv);

private:
    int client_fd;
};



#endif // CLIENT_H