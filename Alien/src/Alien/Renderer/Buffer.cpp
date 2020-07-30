
#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Alien/Platform/OpenGL/OpenGLBuffer.h"

namespace Alien {

	VertexBuffer* VertexBuffer::Create()
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
	}




}


