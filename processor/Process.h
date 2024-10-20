#pragma once

#include "../helpers/Libraries.h"
#include "../communication/SimpleMSG.h"

class Process
{
public:
    std::string name;
    virtual std::string exec(int sockfd) = 0;
    Process();
    ~Process();
};

Process::Process()
{
}

Process::~Process()
{
}