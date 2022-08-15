#pragma once
#include "../Templates.h"
#include <cstdarg>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define Logger Log::GetInstance()

class Log : public Singleton<Log>
{
public:
    std::shared_ptr<spdlog::logger> Instance;

    Log() {
        auto logger = spdlog::stdout_color_mt("OpenGL");

        Instance = logger;
    }

private:

};