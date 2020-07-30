#include "pch.h"
#include "RenderCommand.h"

#include "Alien/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Alien {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();




}