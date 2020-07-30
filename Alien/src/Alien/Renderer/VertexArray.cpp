#include "pch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Alien/Platform/OpenGL/OpenGLVertexArray.h"

namespace Alien {

	VertexArray* VertexArray::Create()
	{
		VertexArray* ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ALIEN_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret = new OpenGLVertexArray();
			break;
		default:
			ALIEN_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}



}