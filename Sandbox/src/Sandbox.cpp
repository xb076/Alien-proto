#include "Alien.h"

class Sandbox : public Alien::Application
{
public:
	Sandbox()
	{
		ALIEN_TRACE("Message Trace!");
		ALIEN_INFO("Message Info!");
		ALIEN_WARN("Message Warn!");
		ALIEN_ERROR("Message Error!");
	}
};

Alien::Application* Alien::CreateApplication()
{
	//return nullptr;
	return new Sandbox();
}
