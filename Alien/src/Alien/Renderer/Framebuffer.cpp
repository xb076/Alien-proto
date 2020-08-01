#include "pch.h"
#include "Framebuffer.h"

#include "Alien/Renderer/Renderer.h"
#include "Alien/Platform/OpenGL/OpenGLFramebuffer.h"

namespace Alien {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    ALIEN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		ALIEN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}

