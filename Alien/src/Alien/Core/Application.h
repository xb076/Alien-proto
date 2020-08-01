#pragma once

#include "Alien/Core/Window.h"
#include "Alien/Core/LayerStack.h"
#include "Alien/Core/TimeStep.h"
#include "Alien/Events/ApplicationEvent.h"
#include "Alien/Renderer/Renderer.h"

#include "Alien/ImGui/ImGuiLayer.h"

namespace Alien {
	
	class Timer
	{
	public:
		Timer() { m_StartTimepoint = std::chrono::high_resolution_clock::now(); }
		~Timer() {}
		float GetMilliSeconds()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			m_StartTimepoint = endTimepoint;

			return (end - start) * 0.001f;
		}

	private:
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	};

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		virtual void OnInit() { }
		virtual void OnShutdown() {}
		virtual void OnUpdate() {}

		virtual void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void RenderImGui();

		inline Window& GetWindow() { return *m_Window; }

		static inline Application& Get() { return *s_Instance; }
	private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		Scope<Timer> m_Timer;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;

	};

	// Implemented by CLIENT
	Application* CreateApplication();
}
