#pragma once

#include "Alien/Core/Core.h"
#include "Alien/Core/Window.h"

#include "Alien/Events/ApplicationEvent.h"

namespace Alien {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate() {}

		virtual void OnEvent(Event& event);
	private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		Scope<Window> m_Window;
		bool m_Running = true;
	};

	// Implemented by CLIENT
	Application* CreateApplication();
}
