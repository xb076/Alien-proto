#include "pch.h"
#include "OpenGLRendererAPI.h"
#include "Alien/Renderer/Renderer.h"
#include <glad/glad.h>

namespace Alien {

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		ALIEN_RENDER_1(color, {
			ALIEN_CORE_INFO("OpenGLRendererAPI::SetClearColor()");
			glClearColor(color.r, color.g, color.b, color.a);
		});
	}

	void OpenGLRendererAPI::Clear()
	{
		ALIEN_RENDER({
			ALIEN_CORE_INFO("OpenGLRendererAPI::Clear()");
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		});
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		ALIEN_RENDER_1(vertexArray, {
			ALIEN_CORE_INFO("OpenGLRendererAPI::DrawIndexed(), count<{0}>", vertexArray->GetIndexBuffers()->GetCount());
			glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);
		});
	}


}


