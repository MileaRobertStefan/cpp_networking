#pragma once

#include "../helpers/Libraries.h"
#include "../processor/ServerProcessor.h"
#include "../communication/SimpleMSG.h"

void *main_thread(void *p_new_socket);

class Listener
{
private:
    int server_fd;
    int value_read;
        int addrlen = sizeof(address);
    struct sockaddr_in address;

public:
    Listener();
    ~Listener();
    void start();
};

void Listener::start()
{
    log_info("Server started on port " << PORT);
    do
    {
        int new_socket = accept(server_fd, (sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket < 0)
        {
            log_error("Accept failed");
            exit(EXIT_FAILURE);
        }

        log_info("New connection from " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << " socket: " << new_socket);

        std::thread new_thread(main_thread, &new_socket);
        new_thread.detach();
    } while (true);
}

Listener::Listener()
{
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        log_error("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        log_error("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        log_error("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 100) < 0)
    {
        log_error("listen failed");
        exit(EXIT_FAILURE);
    }
}

Listener::~Listener()
{
}

void *main_thread(void *p_new_socket)
{
    log_info("New thread started");
    int socket_fd = *(int *)p_new_socket;
    string message;
    string error;
    ServerProcessor cpu(socket_fd);

    do
    {
        if (readMSG(socket_fd, message) < 0)
        {
            close(socket_fd);
            return nullptr;
        }

        log_info("Received message: " + message);

        cpu.process(message);

    } while (true);

    close(socket_fd);
    return nullptr;
}
