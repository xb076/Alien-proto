#include "pch.h"
#include "OpenGLRendererAPI.h"
#include "Alien/Renderer/Renderer.h"
#include <glad/glad.h>

namespace Alien {


	void OpenGLRendererAPI::Init()
	{
		ALIEN_RENDER({
		//glDebugMessageCallback(OpenGLLogMessage, nullptr);
		//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		//glEnable(GL_DEPTH_TEST);
		////glEnable(GL_CULL_FACE);
		//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		//glFrontFace(GL_CCW);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		auto& caps = RendererAPI::GetCapabilities();

		caps.Vendor = (const char*)glGetString(GL_VENDOR);
		caps.Renderer = (const char*)glGetString(GL_RENDERER);
		caps.Version = (const char*)glGetString(GL_VERSION);

		//glGetIntegerv(GL_MAX_SAMPLES, &caps.MaxSamples);
		//glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &caps.MaxAnisotropy);
		});
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		ALIEN_RENDER_1(color, {
			glClearColor(color.r, color.g, color.b, color.a);
		});
	}

	void OpenGLRendererAPI::Clear()
	{
		ALIEN_RENDER({
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		});
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		ALIEN_RENDER_4(x, y, width, height, {
			glViewport(x, y, width, height);
		});
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		ALIEN_RENDER_1(vertexArray, {
			glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);
		});
	}


}


