#include "pch.h"
#include "Application.h"

#include "imgui/imgui.h"
#include <glad/glad.h>


namespace Alien {

#define BIND_EVENT_FN_APPLICATION(fn) std::bind(&Application::##fn, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		m_Timer.reset(new Timer());
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN_APPLICATION(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		Renderer::Init();
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::RenderImGui()
	{
		m_ImGuiLayer->Begin();

		ImGui::Begin("Renderer");
		auto& caps = RendererAPI::GetCapabilities();
		ImGui::Text("Vendor: %s", caps.Vendor.c_str());
		ImGui::Text("Renderer: %s", caps.Renderer.c_str());
		ImGui::Text("Version: %s", caps.Version.c_str());

		char label[64];
		strcpy(label, "%.3fms ");
		strcat(label, "Frame Time");
		ImGui::Text(label, m_FrameTimeSec*1000);
		memset(label, 0, 64);
		strcpy(label, "%.0f ");
		strcat(label, "Frame per Second");
		ImGui::Text(label, 1/ m_FrameTimeSec);
		ImGui::End();

		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();

		m_ImGuiLayer->End();
	}

	void Application::Run()
	{
		OnInit();
		while (m_Running)
		{
			m_FrameTimeSec = m_Timer->GetMilliSeconds() / 1000;
			//PROFILE_SCOPE("Application::Run()");//, [&](auto profileResult) {m_ProfileResults.push_back(profileResult); });

			/*float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;*/

			//glClearColor(1, 0, 1, 1);
			//glClear(GL_COLOR_BUFFER_BIT);
			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(m_FrameTimeSec);

				ALIEN_RENDER_S({ self->RenderImGui(); });

				Renderer::WaitAndRender();
			}

			m_Window->OnUpdate();
		}
		OnShutdown();
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN_APPLICATION(OnWindowResize));
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN_APPLICATION(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::Close()
	{
		m_Running = false;
	}
}


