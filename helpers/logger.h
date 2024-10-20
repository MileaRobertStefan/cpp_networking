#pragma once

#include <iostream>
#include <unistd.h>
#include "../const.h"

using namespace std;

#define _log_from_debug "[" << __FILE__ << ":" << __LINE__ << "][" << getpid() << "]\t"
#define _log_from "[" << getpid() << "]\t"

#include <ostream>
namespace Color
{
    enum Code
    {
        FG_RED = 31,
        FG_GREEN = 32,
        FG_YELLOW = 33,
        FG_BLUE = 34,
        FG_DEFAULT = 39,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_BLUE = 44,
        BG_DEFAULT = 49
    };
    class Modifier
    {
        Code code;

    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream &
        operator<<(std::ostream &os, const Modifier &mod)
        {
            return os << "\033[" << mod.code << "m";
        }
    };
};

class Logger
{
public:
    static string app_name;

    static string getName()
    {
        return "[" + app_name + "]";
    }

};

string Logger::app_name = "no-name";

Logger logger;

Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier yellow(Color::FG_YELLOW);
Color::Modifier def(Color::FG_DEFAULT);

#ifdef DEBUG
#define _log_message(x) Logger::getName() << _log_from_debug << x << std::endl
#else
#define _log_message(x) Logger::getName() << _log_from << x << std::endl
#endif

#define log(x) std::cout << _log_message(x);
#define log_error(x) std::cerr << red << _log_message(x) << def;
#define log_info(x) std::cout << blue << _log_message(x) << def;
#define log_warn(x) std::cout << yellow << _log_message(x) << def;
