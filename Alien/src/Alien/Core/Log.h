#pragma once

#include "Alien/Core/Base.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/bundled/ostream.h"

namespace Alien {

	class Alien_API Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

// Core Logging Macros
#define ALIEN_CORE_TRACE(...)	Alien::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ALIEN_CORE_INFO(...)	Alien::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ALIEN_CORE_WARN(...)	Alien::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ALIEN_CORE_ERROR(...)	Alien::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ALIEN_CORE_FATAL(...)	Alien::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Logging Macros
#define ALIEN_TRACE(...)	Alien::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ALIEN_INFO(...)		Alien::Log::GetClientLogger()->info(__VA_ARGS__)
#define ALIEN_WARN(...)		Alien::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ALIEN_ERROR(...)	Alien::Log::GetClientLogger()->error(__VA_ARGS__)
#define ALIEN_FATAL(...)	Alien::Log::GetClientLogger()->critical(__VA_ARGS__)
