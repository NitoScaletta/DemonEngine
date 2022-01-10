#include "core/Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"



std::shared_ptr<spdlog::logger> Log::client;
std::shared_ptr<spdlog::logger> Log::core;


void Log::init()
{

    spdlog::set_pattern("[%T][%n]%^[%l] %v %$");
    core = spdlog::stdout_color_mt("DemonEngine");
    core->set_level(spdlog::level::trace);
    client = spdlog::stdout_color_mt("App");
    client->set_level(spdlog::level::trace);
}

