#pragma once

#include "Alien/Core/Window.h"

namespace Alien {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_EventCallbackFn = callback; }

		inline unsigned int GetWidth() const override { return m_Width; }
		inline unsigned int GetHeight() const override { return m_Height; }
	protected:
		virtual void Init(const WindowProps& props) override;
		virtual void Shutdown() override;
	private:
		std::string m_Title;
		unsigned int m_Width, m_Height;

		EventCallbackFn m_EventCallbackFn;
	};

}
