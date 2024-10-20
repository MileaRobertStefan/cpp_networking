#include "../..//helpers/logger.h"




int main()
{
    Logger::app_name = "logger_test";
    
    log("Hello World");

    log_error("This is a logic error");

    log_info("This is an info message");

    log_warn("This is a warning message");

    log("This is a normal message");
}