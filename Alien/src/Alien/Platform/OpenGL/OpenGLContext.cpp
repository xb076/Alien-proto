
#include "pch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Alien {

	OpenGLContext::OpenGLContext(GLFWwindow * windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ALIEN_CORE_ASSERT(windowHandle, "Window Handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ALIEN_CORE_ASSERT(status, "Failed to initialize Glad!");

		ALIEN_CORE_INFO("OpenGL Info: ");
		ALIEN_CORE_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
		ALIEN_CORE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
		ALIEN_CORE_INFO(" Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}

