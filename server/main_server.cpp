#include "../helpers/Libraries.h"
#include "../helpers/logger.h"
#include "../communication/Listener.h"

int main()
{
    // Configs
    Logger::app_name = "SERVER";

    //Start the listener
    Listener listener;
    listener.start();
    return 0;
}