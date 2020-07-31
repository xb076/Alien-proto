#include "pch.h"
#include "RendererAPI.h"
#include "Alien/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Alien {

	//RendererAPI::API RendererAPI::s_RendererAPI = RendererAPI::API::OpenGL;

	RendererAPI* RendererAPI::Create()
	{
		RendererAPI* ret = nullptr;
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			ALIEN_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret=new OpenGLRendererAPI();
			break;
		default:
			ALIEN_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}

}