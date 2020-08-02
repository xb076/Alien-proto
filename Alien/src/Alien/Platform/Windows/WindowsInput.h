#pragma once

#include "Alien/Core/Input.h"

namespace Alien {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode);

		virtual bool IsMouseButtonPressedImpl(int button);
		virtual float GetMouseXImpl();
		virtual float GetMouseYImpl();
	};

}
