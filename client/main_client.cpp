#include "../helpers/Libraries.h"
#include "../helpers/logger.h"
#include "../communication/ServerConnect.h"

#include "./actions/Hello.h"

int main(int argc, char *argv[])
{
    // Configs
    if (argc != 3)
    {
        log_error("Usage: " << argv[0] << " <server ip>");
        return -1;
    }


    Logger::app_name = "CLIENT";

    string ip = argv[1];
    string client_name = argv[2];

    int server_sockfd = connectToServer(ip);

    // Create actions
    HelloAction hello(server_sockfd);

    // Execute actions
    while (true)
    {
         hello.exec("Hello from client " + client_name);
        sleep(5);
    }
   

    return 0;
}