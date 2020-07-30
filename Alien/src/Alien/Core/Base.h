#pragma once

namespace Alien {

	void InitializeCore();
	void ShutdownCore();

}

#ifdef ALIEN_DEBUG
#define ALIEN_ENABLE_ASSERTS
#endif

#ifdef ALIEN_PLATFORM_WINDOWS
	#ifdef ALIEN_BUILD_DLL
		#define Alien_API __declspec(dllexport)
	#else
		#define Alien_API __declspec(dllimport)
	#endif
#else
	#error Alien only supports Windows!
#endif

#ifdef ALIEN_ENABLE_ASSERTS
#define ALIEN_ASSERT(x, ...) { if(!(x)) { ALIEN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define ALIEN_CORE_ASSERT(x, ...) { if(!(x)) { ALIEN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define ALIEN_ASSERT(x, ...)
#define ALIEN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)


namespace Alien {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

