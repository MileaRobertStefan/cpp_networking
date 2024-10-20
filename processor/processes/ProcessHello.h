#pragma once

#include "../Process.h"
#include "../../helpers/logger.h"

class ProcessHello : public Process
{

public:
    ProcessHello()
    {
        name = "ProcessHello";
    };
    ~ProcessHello();
    string exec(int sockfd);
};

string ProcessHello::exec(int sockfd)
{
    log_info("Processing " + name + " started execution.");
    string message;
    readMSG(sockfd, message);
    log_info("Received message: " + message);
    message = "I'm " + name + "!";
    sendMSG(sockfd, message);
    log_info("Send message: " + message);

    log_info("Processing " + name + " finished execution.");

    return "success";
}
