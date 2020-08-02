#include "pch.h"
#include "EditorLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Alien/Platform/OpenGL/OpenGLShader.h"
#include "Alien/Platform/OpenGL/OpenGLTexture.h"

namespace Alien {

	EditorLayer::EditorLayer()
		: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
	{
	}

	void EditorLayer::OnAttach()
	{
		Renderer2D::Init();

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);

		m_CheckerboardTexture = Texture2D::Create("assets/textures/Checkerboard.png");
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(float deltaTime)
	{

		m_CameraController.OnUpdate(deltaTime);
		Alien::Renderer2D::ResetStats();

		m_Framebuffer->Bind();

		Alien::Renderer::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1 ));
		Alien::Renderer::Clear();
		

		{
			static float rotation = 0.f;
			rotation += deltaTime * 50.f;

			
			Alien::Renderer2D::BeginScene(m_CameraController.GetCamera());
			Alien::Renderer2D::DrawRotatedQuad(glm::vec2( -1.f,-1.f ), glm::vec2(.8f,.8f ), glm::radians(rotation), glm::vec4(0.8f,0.2f,0.3f,1.0f ));
			Alien::Renderer2D::DrawQuad(glm::vec2(-1.f,0.f ), glm::vec2(.8f,.8f ), glm::vec4(0.8f,0.2f,0.3f,1.0f ));
			Alien::Renderer2D::DrawQuad(glm::vec2(-1.f,1.f ), glm::vec2(.5f,.75f ), glm::vec4(0.2f,0.3f,0.8f,1.0f ));
			Alien::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, -0.1f ), glm::vec2(1.f,1.f ), m_CheckerboardTexture, 1.f);
			Alien::Renderer2D::DrawQuad(glm::vec3(0.f, 0.f, 0.f ), glm::vec2(2.f,2.f ), m_CheckerboardTexture, 1.f);
			Alien::Renderer2D::DrawRotatedQuad(glm::vec3(0.0f, 0.0f, -0.1f ), glm::vec2(1.f,1.f), glm::radians(rotation), m_CheckerboardTexture, 2.f);
			Alien::Renderer2D::EndScene();

			/*Alien::Renderer2D::BeginScene(m_CameraController.GetCamera());
			for (float y = 1.f; y < 5.f; y += 0.5f)
			{
				for (float x = 1.f; x < 5.f; x += 0.5f)
				{
					glm::vec4 color = glm::vec4((x + 5.f) / 10.f, 0.4f, (y + 5.f) / 10.f, .5f );
					Alien::Renderer2D::DrawQuad(glm::vec2(x, y), glm::vec2(0.45f, 0.45f), color);
				}
			}

			Alien::Renderer2D::EndScene();*/
			m_Framebuffer->Unbind();
		}


	}

	void EditorLayer::OnImGuiRender()
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

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_ColorSquare));

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = glm::vec2( viewportPanelSize.x, viewportPanelSize.y );

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Alien::Event& e)
	{
		m_CameraController.OnEvent(e);
	}


}