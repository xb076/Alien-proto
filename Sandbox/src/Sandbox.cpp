#include "Alien.h"
#include "Alien/ImGui/ImGuiLayer.h"
#include "imgui/imgui.h"
#include "glad/glad.h"

#include "Alien/Core/Base.h"
#include "Alien/Renderer/Renderer.h"
#include "Alien/Renderer/Shader.h"
#include "Alien/Renderer/Buffer.h"
#include "Alien/Renderer/VertexArray.h"

class ExampleLayer : public Alien::Layer
{
public:
	ExampleLayer() :Layer("Example") 
	{
		m_VertexArray.reset(Alien::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		Alien::Ref<Alien::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Alien::VertexBuffer::Create(vertices, sizeof(vertices)));

		Alien::BufferLayout layout = {
			{ Alien::ShaderDataType::Float3, "a_Position" },
			{ Alien::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Alien::Ref<Alien::IndexBuffer> indexBuffer;
		indexBuffer.reset(Alien::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Alien::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		Alien::Ref<Alien::VertexBuffer> squareVB;
		squareVB.reset(Alien::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Alien::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Alien::Ref<Alien::IndexBuffer> squareIB;
		squareIB.reset(Alien::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

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

		m_Shader.reset(new Alien::Shader(vertexSrc, fragmentSrc));


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

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Alien::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override
	{
		Alien::RenderCommand::SetClearColor(glm::vec4( 0.1f, 0.1f, 0.1f, 1 ));
		Alien::RenderCommand::Clear();

		Alien::Renderer::BeginScene();

		m_BlueShader->Bind();
		Alien::Renderer::Submit(m_SquareVA);

		m_Shader->Bind();
		Alien::Renderer::Submit(m_VertexArray);

		Alien::Renderer::EndScene();
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

private:
	Alien::Ref<Alien::Shader> m_Shader;
	Alien::Ref<Alien::VertexArray> m_VertexArray;

	Alien::Ref<Alien::Shader> m_BlueShader;
	Alien::Ref<Alien::VertexArray> m_SquareVA;
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
