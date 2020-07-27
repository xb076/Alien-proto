
#include "pch.h"

#include "Core.h"

#include "Log.h"

#include <Windows.h>

#define ALIEN_BUILD_ID "v0.1a"

namespace Alien {

	void InitializeCore()
	{
		Alien::Log::Init();

		ALIEN_CORE_TRACE("Hazel Engine {}", ALIEN_BUILD_ID);
		ALIEN_CORE_TRACE("Initializing...");
	}

	void ShutdownCore()
	{
		ALIEN_CORE_TRACE("Shutting down...");
	}

}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Alien::InitializeCore();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		Alien::ShutdownCore();
		break;
	}
	return TRUE;
}
