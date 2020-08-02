#pragma once

namespace Alien
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,

		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2
	} Mouse;
	
	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define ALIEN_MOUSE_BUTTON_0      ::Alien::Mouse::Button0
#define ALIEN_MOUSE_BUTTON_1      ::Alien::Mouse::Button1
#define ALIEN_MOUSE_BUTTON_2      ::Alien::Mouse::Button2
#define ALIEN_MOUSE_BUTTON_3      ::Alien::Mouse::Button3
#define ALIEN_MOUSE_BUTTON_4      ::Alien::Mouse::Button4
#define ALIEN_MOUSE_BUTTON_5      ::Alien::Mouse::Button5
#define ALIEN_MOUSE_BUTTON_6      ::Alien::Mouse::Button6
#define ALIEN_MOUSE_BUTTON_7      ::Alien::Mouse::Button7
#define ALIEN_MOUSE_BUTTON_LAST   ::Alien::Mouse::ButtonLast
#define ALIEN_MOUSE_BUTTON_LEFT   ::Alien::Mouse::ButtonLeft
#define ALIEN_MOUSE_BUTTON_RIGHT  ::Alien::Mouse::ButtonRight
#define ALIEN_MOUSE_BUTTON_MIDDLE ::Alien::Mouse::ButtonMiddle
