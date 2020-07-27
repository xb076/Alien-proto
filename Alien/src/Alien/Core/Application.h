#pragma once

#include "Alien/Core/Core.h"
#include "Alien/Core/Window.h"

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
	private:
		bool m_Running = true;
	};

	// Implemented by CLIENT
	Application* CreateApplication();
}
