
#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Alien/Platform/OpenGL/OpenGLBuffer.h"

namespace Alien {

	/*VertexBuffer* VertexBuffer::Create()
	{
		VertexBuffer* ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ALIEN_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret = new OpenGLVertexBuffer();
			break;
		default:
			ALIEN_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}

	IndexBuffer* IndexBuffer::Create()
	{
		IndexBuffer* ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ALIEN_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret = new OpenGLIndexBuffer();
			break;
		default:
			ALIEN_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}*/

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:   ALIEN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(size);
		}

		ALIEN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		Ref<VertexBuffer> ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ALIEN_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret = CreateRef<OpenGLVertexBuffer>(vertices, size);
			break;
		default:
			ALIEN_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		Ref<IndexBuffer> ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ALIEN_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret = CreateRef<OpenGLIndexBuffer>(indices, count);
			break;
		default:
			ALIEN_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}



}


