#include "Alien.h"
#include "Alien/ImGui/ImGuiLayer.h"
#include <imgui/imgui.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Alien/Core/Base.h"
#include "Alien/Renderer/Renderer.h"
#include "Alien/Renderer/RendererAPI.h"
#include "Alien/Renderer/Shader.h"
#include "Alien/Renderer/Buffer.h"
#include "Alien/Renderer/VertexArray.h"
#include "Alien/Renderer/Framebuffer.h"


// ---Entry Point------------
#include "Alien/Core/EntryPoint.h"
// --------------------------



class ExampleLayer : public Alien::Layer
{
public:
	ExampleLayer() :Layer("Example") 
	{
	}

	void OnAttach() override
	{
		Alien::FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Alien::Framebuffer::Create(fbSpec);

		m_VertexArrayTriangle.reset(Alien::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		m_VertexBufferTriangle=Alien::VertexBuffer::Create(vertices, sizeof(vertices));
		//m_VertexBufferTriangle->SetData(vertices, sizeof(vertices), 7);

		Alien::BufferLayout layout = {
			{ Alien::ShaderDataType::Float3, "a_Position" },
			{ Alien::ShaderDataType::Float4, "a_Color" }
		};
		m_VertexBufferTriangle->SetLayout(layout);
		m_VertexArrayTriangle->AddVertexBuffer(m_VertexBufferTriangle);

		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBufferTriangle=Alien::IndexBuffer::Create(indices, sizeof(indices));

		m_VertexArrayTriangle->SetIndexBuffer(m_IndexBufferTriangle);

		m_VertexArraySquare.reset(Alien::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		m_VertexBufferSquare=Alien::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		m_VertexBufferSquare->SetLayout({
			{ Alien::ShaderDataType::Float3, "a_Position" }
			});
		m_VertexArraySquare->AddVertexBuffer(m_VertexBufferSquare);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		m_IndexBufferSquare=Alien::IndexBuffer::Create(squareIndices, sizeof(squareIndices));
		m_VertexArraySquare->SetIndexBuffer(m_IndexBufferSquare);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position *0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_ShaderTriangle = Alien::Shader::Create("Shader1", vertexSrc, fragmentSrc);


		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				//color = vec4(0.2, 0.3, 0.8, 1.0);
				color = vec4(u_Color, 1.0);
			}
		)";

		m_ShaderSquare = Alien::Shader::Create("Shader2", blueShaderVertexSrc, blueShaderFragmentSrc);


	}

	void OnUpdate(float deltaTime) override
	{
		m_Framebuffer->Bind();
		Alien::Renderer::SetClearColor(glm::vec4( 0.1f, 0.1f, 0.1f, 1 ));
		Alien::Renderer::Clear();

		Alien::Renderer::BeginScene();

		m_ShaderSquare->Bind();
		m_ShaderSquare->SetFloat3("u_Color", m_ColorSquare);
		Alien::Renderer::Draw(m_VertexArraySquare);

		m_ShaderTriangle->Bind();
		Alien::Renderer::Draw(m_VertexArrayTriangle);

		Alien::Renderer::EndScene();
		m_Framebuffer->Unbind();
	}

	void OnImGuiRender()
	{
		
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				/*if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 dockspace_flags ^= ImGuiDockNodeFlags_NoSplit;
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0))     dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
				ImGui::Separator();*/

				if (ImGui::MenuItem("Exit")) Alien::Application::Get().Close();
				ImGui::EndMenu();
			}


			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");
		/*auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());*/

		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_ColorSquare));
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Alien::Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = glm::vec2(viewportPanelSize.x, viewportPanelSize.y);

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();

		//ImGui::Begin("Setting");

		//auto stats = Engine::Renderer2D::GetStats();
		//ImGui::Text("Renderer2D Stats: ");
		//ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		//ImGui::Text("Quad Counts: %d", stats.QuadCount);
		//ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		//ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		//ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		//ImGui::End();

		//ImGui::Begin("Viewport");
		//ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		//LOG_APP_WARN("Viewport size: {0}, {1}", viewportPanelSize.x, viewportPanelSize.y);
		////uint32_t textureID = m_CheckerboardTexture->GetRendererID();
		////ImGui::Image((void*)textureID, ImVec2{128.f, 128.f});
		//uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		//ImGui::Image((void*)textureID, ImVec2{ 320.f, 180.f });
		//ImGui::End();


		//ImGui::End();
	}
	
	void OnEvent(Alien::Event& event) override
	{
		if (event.GetEventType() == Alien::EventType::KeyPressed)
		{
			Alien::KeyPressedEvent& e = (Alien::KeyPressedEvent&)event;
			ALIEN_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

private:
	Alien::Ref<Alien::VertexBuffer> m_VertexBufferTriangle;
	Alien::Ref<Alien::IndexBuffer> m_IndexBufferTriangle;
	Alien::Ref<Alien::VertexArray> m_VertexArrayTriangle;
	Alien::Ref<Alien::Shader> m_ShaderTriangle;

	Alien::Ref<Alien::VertexBuffer> m_VertexBufferSquare;
	Alien::Ref<Alien::IndexBuffer> m_IndexBufferSquare;
	Alien::Ref<Alien::VertexArray> m_VertexArraySquare;
	Alien::Ref<Alien::Shader> m_ShaderSquare;

	glm::vec3 m_ColorSquare = glm::vec3( .2f, .3f, .8f);

	Alien::Ref<Alien::Framebuffer> m_Framebuffer;
	bool m_ViewportFocused = false, m_ViewportHovered = false;
	glm::vec2 m_ViewportSize = glm::vec2( 0.0f, 0.0f );
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
