#include "pch.h"
#include "Renderer.h"

namespace Alien {

	struct RendererData
	{
		//Ref<RenderPass> m_ActiveRenderPass;
		Scope<RenderCommandQueue> m_CommandQueue;
		Scope<ShaderLibrary> m_ShaderLibrary;
		Scope<RendererAPI> m_RendererAPI;
		//Ref<VertexArray> m_FullscreenQuadVertexArray;
	};

	static RendererData s_Data;

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	void Renderer::Init()
	{
		//s_Instance = new Renderer();
		s_Data.m_RendererAPI.reset(RendererAPI::Create());
		s_Data.m_ShaderLibrary = CreateScope<ShaderLibrary>();
		s_Data.m_CommandQueue = CreateScope<RenderCommandQueue>();

		s_Data.m_RendererAPI->Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		s_Data.m_RendererAPI->SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::SetClearColor(const glm::vec4& color) { s_Data.m_RendererAPI->SetClearColor(color); }
	void Renderer::Clear() { s_Data.m_RendererAPI->Clear(); }

	void Renderer::Draw(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		s_Data.m_RendererAPI->DrawIndexed(vertexArray);
	}

	void* Renderer::Submit(RenderCommandFn fn, unsigned int size)
	{
		return s_Data.m_CommandQueue->Allocate(fn, size);
	}

	void Renderer::WaitAndRender()
	{
		s_Data.m_CommandQueue->Execute();
	}

}


