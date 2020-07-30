
#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Alien/Platform/OpenGL/OpenGLBuffer.h"

namespace Alien {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		VertexBuffer* ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ALIEN_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret = new OpenGLVertexBuffer(vertices, size);
			break;
		default:
			ALIEN_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		IndexBuffer* ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ALIEN_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret = new OpenGLIndexBuffer(indices, size);
			break;
		default:
			ALIEN_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}




}


