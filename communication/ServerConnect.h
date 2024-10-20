#include "../helpers/Libraries.h"
#include "../helpers/logger.h"

int connectToServer(string ip)
{
    int sock = 0;
    sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        log_error("Socket creation error.");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0)
    {
        log_error("Invalid address/ Address not supported");
        return -1;
    }

    if (connect(sock, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        log_error("Connection failed.");
        return -1;
    }

    return sock;
}