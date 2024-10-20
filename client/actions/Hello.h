#include "../../helpers/Libraries.h"
#include "../../helpers/logger.h"
#include "../../communication/SimpleMSG.h"

class HelloAction
{
    string name = "Hello";
    int sockfd;

public:

    HelloAction(int sockfd)
    {
        this->sockfd = sockfd;
    }

    void exec(string message)
    {
        log_info("Processing "+ name +" action!.");
        sendMSG(sockfd, HelloProcess);

        sendMSG(sockfd, message);
        log_info("Send message: " + message);

        readMSG(sockfd, message);
        log_info("Received message: " + message);;

        log_info("Processing Hello action finished.");
    }
};