#pragma once

#include "../helpers/Libraries.h"

void sendMSG(int socket_fd, const std::string& message)
{
    uint32_t message_size = htonl(message.size());  // Convert to network byte order

    // Send the size of the message
    ssize_t sent_bytes = send(socket_fd, &message_size, sizeof(uint32_t), 0);
    if (sent_bytes != sizeof(uint32_t)) {
        log_error("Failed to send message size");
        return;
    }

    // Send the message itself
    ssize_t total_sent = 0;
    ssize_t message_length = message.size();
    while (total_sent < message_length) {
        sent_bytes = send(socket_fd, message.c_str() + total_sent, message_length - total_sent, 0);
        if (sent_bytes < 0) {
            log_error("Send failed");
            return;
        }
        total_sent += sent_bytes;
    }
}

int readMSG(int socket_fd, std::string &message)
{
    message.clear();
    int message_size = 0;

    // Read the message size
    ssize_t received_bytes = read(socket_fd, &message_size, 4);

    if (received_bytes <= 0) {
        if (received_bytes == 0) {
            log_warn("Connection closed by peer");
        } else {
            log_error("Failed to read message size");
        }
        return -1;
    }

    message_size = ntohl(message_size);  // Convert from network byte order

    // Read the actual message in chunks
    uint8_t buffer[BUFFERSIZE];
    int total_received = 0;
    while (total_received < message_size) {
        ssize_t to_read = std::min(BUFFERSIZE, message_size - total_received);
        received_bytes = read(socket_fd, buffer, to_read);
        
        if (received_bytes <= 0) {
            if (received_bytes == 0) {
                log_warn("Connection closed by peer during message read");
            } else {
                log_error("Failed to read message");
            }
            return -1;
        }

        message.append((char *)buffer, received_bytes);
        total_received += received_bytes;
    }

    return message.size();
}