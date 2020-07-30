#pragma once

#include "Alien/Core/Window.h"
#include "Alien/Core/LayerStack.h"
#include "Alien/Core/TimeStep.h"
#include "Alien/Events/ApplicationEvent.h"

#include "Alien/ImGui/ImGuiLayer.h"

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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		static inline Application& Get() { return *s_Instance; }
	private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
		Timestep m_Timestep;
		float m_LastFrameTime = 0.0f;

		struct ProfileResult
		{
			const char* Name;
			float Time;
		};

		std::vector<ProfileResult> m_ProfileResults;

	};

	// Implemented by CLIENT
	Application* CreateApplication();
}
