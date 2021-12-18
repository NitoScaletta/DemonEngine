#ifndef __LOG_H__
#define __LOG_H__
#include <spdlog/spdlog.h>
#include <iostream>


class Log
{
public:
	static void init();
	static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return Log::core; }
	static std::shared_ptr<spdlog::logger>& GetClientLogger() { return Log::client; }
private:
	static std::shared_ptr<spdlog::logger> core;
	static std::shared_ptr<spdlog::logger> client;

};


#define DE_CORE_TRACE(...)		Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DE_CORE_INFO(...)		Log::GetCoreLogger()->info(__VA_ARGS__)
#define DE_CORE_WARNING(...)	Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DE_CORE_ERROR(...)		Log::GetCoreLogger()->error(__VA_ARGS__)
#define DE_CORE_CRITICAL(...)	Log::GetCoreLogger()->critical(__VA_ARGS__)


#define DE_TRACE(...)			Log::GetClientLogger()->trace(__VA_ARGS__)
#define DE_INFO(...)			Log::GetClientLogger()->info(__VA_ARGS__)
#define DE_WARNING(...)			Log::GetClientLogger()->warn(__VA_ARGS__)
#define DE_ERROR(...)			Log::GetClientLogger()->error(__VA_ARGS__)
#define DE_CRITICAL(...)		Log::GetClientLogger()->critical(__VA_ARGS__)

#endif
