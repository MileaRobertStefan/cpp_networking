#pragma once

#include "ProcessList.h"
#include "Process.h"
#include "../helpers/Libraries.h"
#include "../helpers/logger.h"

class ServerProcessor
{
    std::map<string ,Process*> commands;

public:
    int sockfd;
    
    bool process(string command);

    ServerProcessor(int _sockfd);
    ~ServerProcessor();
};

bool ServerProcessor::process(string command)
{
    auto it = commands.find(command);
    if (it == commands.end())
    {
        log_warn("Command " + command + " not found");
        return false;
    }

    std::string rez = it->second->exec(sockfd);
    log(rez);

    return true;
}

ServerProcessor::ServerProcessor(int _sockfd)
{
    sockfd = _sockfd;

    commands[HelloProcess] = new ProcessHello;
}

ServerProcessor::~ServerProcessor()
{
    for (auto &command : commands)
    {
        delete command.second;
    }

    commands.clear();
}