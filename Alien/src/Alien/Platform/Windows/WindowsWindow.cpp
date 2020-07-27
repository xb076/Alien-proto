
#include "pch.h"
#include "WindowsWindow.h"

namespace Alien {

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
		: Window(props)
	{

	}

	WindowsWindow::~WindowsWindow()
	{
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Title = props.Title;
		m_Width = props.Width;
		m_Height = props.Height;

		// TODO: GLFW
	}

	void WindowsWindow::Shutdown()
	{
	}
}
