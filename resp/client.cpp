#include <unistd.h>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include "../include/client.h"
#include "../include/resp.h"

#define BUFFER_SIZE 2048

void Client::handle_request() {
    char buffer[BUFFER_SIZE];
    std::cout << "INFO: Ready to handle client commands\n";
    
    while(true){
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes_received < 0) {
            std::cerr << "ERROR: Failed to receive data from client\n";
            break;
        }else if(bytes_received == 0){
            std::cerr << "Client disconnected\n";
            break;
        }else{
            std::cout << "Received: " << std::string_view(buffer, bytes_received) << "\n";
            buffer[bytes_received] = '\0';
            std::string resp = parse_resp(buffer);
            std::cout << "Response: " << resp << '\n';
            ssize_t bytes_sent = send(client_fd, resp.c_str(), resp.size(), 0);
            if(bytes_sent < 0){
                std::cerr << "ERROR: Failed to send data to client\n";
            }
        }
    }
    
}