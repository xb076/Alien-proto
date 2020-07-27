#pragma once

#ifdef ALIEN_PLATFORM_WINDOWS

extern Alien::Application* Alien::CreateApplication();

int main(int argc, char** argv)
{
	Alien::Log::Init();
	Alien::Application* app = Alien::CreateApplication();
	ALIEN_CORE_ASSERT(app, "Client Application is null!");
	app->Run();
	delete app;
}

#endif
