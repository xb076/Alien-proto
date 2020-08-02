#pragma once

#include "Alien.h"

namespace Alien {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(float deltaTime) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		Ref<Texture2D> m_CheckerboardTexture, m_LogoTexture;
		glm::vec3 m_ColorSquare = glm::vec3(.2f, .3f, .8f);
		OrthographicCameraController m_CameraController;

		Alien::Ref<Alien::Framebuffer> m_Framebuffer;
		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = glm::vec2(0.0f, 0.0f);

	};

}

