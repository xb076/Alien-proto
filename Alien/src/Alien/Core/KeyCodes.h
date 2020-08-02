#pragma once

namespace Alien
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define ALIEN_KEY_SPACE           ::Alien::Key::Space
#define ALIEN_KEY_APOSTROPHE      ::Alien::Key::Apostrophe    /* ' */
#define ALIEN_KEY_COMMA           ::Alien::Key::Comma         /* , */
#define ALIEN_KEY_MINUS           ::Alien::Key::Minus         /* - */
#define ALIEN_KEY_PERIOD          ::Alien::Key::Period        /* . */
#define ALIEN_KEY_SLASH           ::Alien::Key::Slash         /* / */
#define ALIEN_KEY_0               ::Alien::Key::D0
#define ALIEN_KEY_1               ::Alien::Key::D1
#define ALIEN_KEY_2               ::Alien::Key::D2
#define ALIEN_KEY_3               ::Alien::Key::D3
#define ALIEN_KEY_4               ::Alien::Key::D4
#define ALIEN_KEY_5               ::Alien::Key::D5
#define ALIEN_KEY_6               ::Alien::Key::D6
#define ALIEN_KEY_7               ::Alien::Key::D7
#define ALIEN_KEY_8               ::Alien::Key::D8
#define ALIEN_KEY_9               ::Alien::Key::D9
#define ALIEN_KEY_SEMICOLON       ::Alien::Key::Semicolon     /* ; */
#define ALIEN_KEY_EQUAL           ::Alien::Key::Equal         /* = */
#define ALIEN_KEY_A               ::Alien::Key::A
#define ALIEN_KEY_B               ::Alien::Key::B
#define ALIEN_KEY_C               ::Alien::Key::C
#define ALIEN_KEY_D               ::Alien::Key::D
#define ALIEN_KEY_E               ::Alien::Key::E
#define ALIEN_KEY_F               ::Alien::Key::F
#define ALIEN_KEY_G               ::Alien::Key::G
#define ALIEN_KEY_H               ::Alien::Key::H
#define ALIEN_KEY_I               ::Alien::Key::I
#define ALIEN_KEY_J               ::Alien::Key::J
#define ALIEN_KEY_K               ::Alien::Key::K
#define ALIEN_KEY_L               ::Alien::Key::L
#define ALIEN_KEY_M               ::Alien::Key::M
#define ALIEN_KEY_N               ::Alien::Key::N
#define ALIEN_KEY_O               ::Alien::Key::O
#define ALIEN_KEY_P               ::Alien::Key::P
#define ALIEN_KEY_Q               ::Alien::Key::Q
#define ALIEN_KEY_R               ::Alien::Key::R
#define ALIEN_KEY_S               ::Alien::Key::S
#define ALIEN_KEY_T               ::Alien::Key::T
#define ALIEN_KEY_U               ::Alien::Key::U
#define ALIEN_KEY_V               ::Alien::Key::V
#define ALIEN_KEY_W               ::Alien::Key::W
#define ALIEN_KEY_X               ::Alien::Key::X
#define ALIEN_KEY_Y               ::Alien::Key::Y
#define ALIEN_KEY_Z               ::Alien::Key::Z
#define ALIEN_KEY_LEFT_BRACKET    ::Alien::Key::LeftBracket   /* [ */
#define ALIEN_KEY_BACKSLASH       ::Alien::Key::Backslash     /* \ */
#define ALIEN_KEY_RIGHT_BRACKET   ::Alien::Key::RightBracket  /* ] */
#define ALIEN_KEY_GRAVE_ACCENT    ::Alien::Key::GraveAccent   /* ` */
#define ALIEN_KEY_WORLD_1         ::Alien::Key::World1        /* non-US #1 */
#define ALIEN_KEY_WORLD_2         ::Alien::Key::World2        /* non-US #2 */

/* Function keys */
#define ALIEN_KEY_ESCAPE          ::Alien::Key::Escape
#define ALIEN_KEY_ENTER           ::Alien::Key::Enter
#define ALIEN_KEY_TAB             ::Alien::Key::Tab
#define ALIEN_KEY_BACKSPACE       ::Alien::Key::Backspace
#define ALIEN_KEY_INSERT          ::Alien::Key::Insert
#define ALIEN_KEY_DELETE          ::Alien::Key::Delete
#define ALIEN_KEY_RIGHT           ::Alien::Key::Right
#define ALIEN_KEY_LEFT            ::Alien::Key::Left
#define ALIEN_KEY_DOWN            ::Alien::Key::Down
#define ALIEN_KEY_UP              ::Alien::Key::Up
#define ALIEN_KEY_PAGE_UP         ::Alien::Key::PageUp
#define ALIEN_KEY_PAGE_DOWN       ::Alien::Key::PageDown
#define ALIEN_KEY_HOME            ::Alien::Key::Home
#define ALIEN_KEY_END             ::Alien::Key::End
#define ALIEN_KEY_CAPS_LOCK       ::Alien::Key::CapsLock
#define ALIEN_KEY_SCROLL_LOCK     ::Alien::Key::ScrollLock
#define ALIEN_KEY_NUM_LOCK        ::Alien::Key::NumLock
#define ALIEN_KEY_PRINT_SCREEN    ::Alien::Key::PrintScreen
#define ALIEN_KEY_PAUSE           ::Alien::Key::Pause
#define ALIEN_KEY_F1              ::Alien::Key::F1
#define ALIEN_KEY_F2              ::Alien::Key::F2
#define ALIEN_KEY_F3              ::Alien::Key::F3
#define ALIEN_KEY_F4              ::Alien::Key::F4
#define ALIEN_KEY_F5              ::Alien::Key::F5
#define ALIEN_KEY_F6              ::Alien::Key::F6
#define ALIEN_KEY_F7              ::Alien::Key::F7
#define ALIEN_KEY_F8              ::Alien::Key::F8
#define ALIEN_KEY_F9              ::Alien::Key::F9
#define ALIEN_KEY_F10             ::Alien::Key::F10
#define ALIEN_KEY_F11             ::Alien::Key::F11
#define ALIEN_KEY_F12             ::Alien::Key::F12
#define ALIEN_KEY_F13             ::Alien::Key::F13
#define ALIEN_KEY_F14             ::Alien::Key::F14
#define ALIEN_KEY_F15             ::Alien::Key::F15
#define ALIEN_KEY_F16             ::Alien::Key::F16
#define ALIEN_KEY_F17             ::Alien::Key::F17
#define ALIEN_KEY_F18             ::Alien::Key::F18
#define ALIEN_KEY_F19             ::Alien::Key::F19
#define ALIEN_KEY_F20             ::Alien::Key::F20
#define ALIEN_KEY_F21             ::Alien::Key::F21
#define ALIEN_KEY_F22             ::Alien::Key::F22
#define ALIEN_KEY_F23             ::Alien::Key::F23
#define ALIEN_KEY_F24             ::Alien::Key::F24
#define ALIEN_KEY_F25             ::Alien::Key::F25

/* Keypad */
#define ALIEN_KEY_KP_0            ::Alien::Key::KP0
#define ALIEN_KEY_KP_1            ::Alien::Key::KP1
#define ALIEN_KEY_KP_2            ::Alien::Key::KP2
#define ALIEN_KEY_KP_3            ::Alien::Key::KP3
#define ALIEN_KEY_KP_4            ::Alien::Key::KP4
#define ALIEN_KEY_KP_5            ::Alien::Key::KP5
#define ALIEN_KEY_KP_6            ::Alien::Key::KP6
#define ALIEN_KEY_KP_7            ::Alien::Key::KP7
#define ALIEN_KEY_KP_8            ::Alien::Key::KP8
#define ALIEN_KEY_KP_9            ::Alien::Key::KP9
#define ALIEN_KEY_KP_DECIMAL      ::Alien::Key::KPDecimal
#define ALIEN_KEY_KP_DIVIDE       ::Alien::Key::KPDivide
#define ALIEN_KEY_KP_MULTIPLY     ::Alien::Key::KPMultiply
#define ALIEN_KEY_KP_SUBTRACT     ::Alien::Key::KPSubtract
#define ALIEN_KEY_KP_ADD          ::Alien::Key::KPAdd
#define ALIEN_KEY_KP_ENTER        ::Alien::Key::KPEnter
#define ALIEN_KEY_KP_EQUAL        ::Alien::Key::KPEqual

#define ALIEN_KEY_LEFT_SHIFT      ::Alien::Key::LeftShift
#define ALIEN_KEY_LEFT_CONTROL    ::Alien::Key::LeftControl
#define ALIEN_KEY_LEFT_ALT        ::Alien::Key::LeftAlt
#define ALIEN_KEY_LEFT_SUPER      ::Alien::Key::LeftSuper
#define ALIEN_KEY_RIGHT_SHIFT     ::Alien::Key::RightShift
#define ALIEN_KEY_RIGHT_CONTROL   ::Alien::Key::RightControl
#define ALIEN_KEY_RIGHT_ALT       ::Alien::Key::RightAlt
#define ALIEN_KEY_RIGHT_SUPER     ::Alien::Key::RightSuper
#define ALIEN_KEY_MENU            ::Alien::Key::Menu



