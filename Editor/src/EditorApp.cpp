#include "Alien.h"
#include "EditorLayer.h"



// ---Entry Point------------
#include "Alien/Core/EntryPoint.h"
// --------------------------



class EditorApp : public Alien::Application
{
public:
	EditorApp()
	{
		ALIEN_TRACE("Message Trace!");
		ALIEN_INFO("Message Info!");
		ALIEN_WARN("Message Warn!");
		ALIEN_ERROR("Message Error!");
	}

	virtual void OnInit() override
	{
		PushLayer(new Alien::EditorLayer());
	}
};

Alien::Application* Alien::CreateApplication()
{
	//return nullptr;
	return new EditorApp();
}
