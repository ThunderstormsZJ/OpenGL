#pragma once
#include <string>
#include <cstdarg>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "Templates.h"

#define Logger Log::GetInstance()

//missing string printf
//this is safe and convenient but not exactly efficient
inline std::string format(const char* fmt, ...) {
    int size = 512;
    char* buffer = 0;
    buffer = new char[size];
    va_list vl;
    va_start(vl, fmt);
    int nsize = vsnprintf(buffer, size, fmt, vl);
    if (size <= nsize) { //fail delete buffer and try again
        delete[] buffer;
        buffer = 0;
        buffer = new char[nsize + 1]; //+1 for /0
        nsize = vsnprintf(buffer, size, fmt, vl);
    }
    std::string ret(buffer);
    va_end(vl);
    delete[] buffer;
    return ret;
}

class Log: public Singleton<Log>
{
public:
    std::shared_ptr<spdlog::logger> Instance;

    Log() {
        auto logger = spdlog::stdout_color_mt("OpenGL");

        Instance = logger;
    }

private:

};
