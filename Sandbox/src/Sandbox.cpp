#include "Alien.h"
#include "Alien/ImGui/ImGuiLayer.h"
#include "imgui/imgui.h"

class ExampleLayer : public Alien::Layer
{
public:
	ExampleLayer() :Layer("Example") {}

	void OnUpdate() override
	{
		
	}

	void OnImGuiRender()
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}
	
	void OnEvent(Alien::Event& event) override
	{
		if (event.GetEventType() == Alien::EventType::KeyPressed)
		{
			Alien::KeyPressedEvent& e = (Alien::KeyPressedEvent&)event;
			ALIEN_TRACE("{0}", (char)e.GetKeyCode());
		}
	}


};


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

	virtual void OnInit() override
	{
		PushLayer(new ExampleLayer());
	}
};

Alien::Application* Alien::CreateApplication()
{
	//return nullptr;
	return new Sandbox();
}
