#pragma once

#ifdef ALIEN_PLATFORM_WINDOWS

extern Alien::Application* Alien::CreateApplication();

int main(int argc, char* argv[])
{
	//Engine::Log::Init();
	//LOG_CORE_WARN("Initialized Log!");
	//int a = 5;
	//LOG_APP_INFO("Hello! Var={0}", a);


	//auto app = Engine::CreateApplication();
	//app->Run();
	//delete app;

	Alien::Log::Init();

	auto app = Alien::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif
