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


class ExampleLayer : public Alien::Layer
{
public:
	ExampleLayer() :Layer("Example") 
	{
	}

	void OnAttach() override
	{
		m_VertexArrayTriangle.reset(Alien::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		m_VertexBufferTriangle.reset(Alien::VertexBuffer::Create());
		m_VertexBufferTriangle->SetData(vertices, sizeof(vertices), 7);

		Alien::BufferLayout layout = {
			{ Alien::ShaderDataType::Float3, "a_Position" },
			{ Alien::ShaderDataType::Float4, "a_Color" }
		};
		m_VertexBufferTriangle->SetLayout(layout);
		m_VertexArrayTriangle->AddVertexBuffer(m_VertexBufferTriangle);

		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBufferTriangle.reset(Alien::IndexBuffer::Create());
		m_IndexBufferTriangle->SetData(indices, sizeof(indices));

		m_VertexArrayTriangle->SetIndexBuffer(m_IndexBufferTriangle);

		m_VertexArraySquare.reset(Alien::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		m_VertexBufferSquare.reset(Alien::VertexBuffer::Create());
		m_VertexBufferSquare->SetData(squareVertices, sizeof(squareVertices));

		m_VertexBufferSquare->SetLayout({
			{ Alien::ShaderDataType::Float3, "a_Position" }
			});
		m_VertexArraySquare->AddVertexBuffer(m_VertexBufferSquare);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		m_IndexBufferSquare.reset(Alien::IndexBuffer::Create());
		m_IndexBufferSquare->SetData(squareIndices, sizeof(squareIndices));
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

	void OnUpdate() override
	{
		Alien::Renderer::SetClearColor(glm::vec4( 0.1f, 0.1f, 0.1f, 1 ));
		Alien::Renderer::Clear();

		Alien::Renderer::BeginScene();

		m_ShaderSquare->Bind();
		m_ShaderSquare->SetFloat3("u_Color", m_ColorSquare);
		Alien::Renderer::Draw(m_VertexArraySquare);

		m_ShaderTriangle->Bind();
		Alien::Renderer::Draw(m_VertexArrayTriangle);

		Alien::Renderer::EndScene();
	}

	void OnImGuiRender()
	{
		ImGui::Begin("ColorPicker");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_ColorSquare));

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
