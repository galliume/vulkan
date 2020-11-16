#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Vulk
{
	class Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
}

#define VULK_CRITICAL(...) ::Vulk::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define VULK_ERROR(...) ::Vulk::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VULK_WARN(...) ::Vulk::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VULK_INFO(...) ::Vulk::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VULK_TRACE(...) ::Vulk::Log::GetCoreLogger()->trace(__VA_ARGS__)