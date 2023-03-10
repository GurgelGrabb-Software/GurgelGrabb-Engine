#pragma once

#include "GG/Rendering/GLInclude.h"

#include <string>

namespace gg
{
	enum EInputCode : int
	{
		KEY_A = GLFW_KEY_A,
		KEY_B = GLFW_KEY_B,
		KEY_C = GLFW_KEY_C,
		KEY_D = GLFW_KEY_D,
		KEY_E = GLFW_KEY_E,
		KEY_F = GLFW_KEY_F,
		KEY_G = GLFW_KEY_G,
		KEY_H = GLFW_KEY_H,
		KEY_I = GLFW_KEY_I,
		KEY_J = GLFW_KEY_J,
		KEY_K = GLFW_KEY_K,
		KEY_L = GLFW_KEY_L,
		KEY_M = GLFW_KEY_M,
		KEY_N = GLFW_KEY_N,
		KEY_O = GLFW_KEY_O,
		KEY_P = GLFW_KEY_P,
		KEY_Q = GLFW_KEY_Q,
		KEY_R = GLFW_KEY_R,
		KEY_S = GLFW_KEY_S,
		KEY_T = GLFW_KEY_T,
		KEY_U = GLFW_KEY_U,
		KEY_V = GLFW_KEY_V,
		KEY_W = GLFW_KEY_W,
		KEY_X = GLFW_KEY_X,
		KEY_Y = GLFW_KEY_Y,
		KEY_Z = GLFW_KEY_Z,

		NUM_0 = GLFW_KEY_0,
		NUM_1 = GLFW_KEY_1,
		NUM_2 = GLFW_KEY_2,
		NUM_3 = GLFW_KEY_3,
		NUM_4 = GLFW_KEY_4,
		NUM_5 = GLFW_KEY_5,
		NUM_6 = GLFW_KEY_6,
		NUM_7 = GLFW_KEY_7,
		NUM_8 = GLFW_KEY_8,
		NUM_9 = GLFW_KEY_9,

		F1 = GLFW_KEY_F1,
		F2 = GLFW_KEY_F2,
		F3 = GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12,

		LEFT = GLFW_KEY_LEFT,
		RIGHT = GLFW_KEY_RIGHT,
		UP = GLFW_KEY_UP,
		DOWN = GLFW_KEY_DOWN,

		LALT = GLFW_KEY_LEFT_ALT,
		RALT = GLFW_KEY_RIGHT_ALT,
		LCTRL = GLFW_KEY_LEFT_CONTROL,
		RCTRL = GLFW_KEY_RIGHT_CONTROL,
		LSHIFT = GLFW_KEY_LEFT_SHIFT,
		RSHIFT = GLFW_KEY_RIGHT_SHIFT,
		CAPS = GLFW_KEY_CAPS_LOCK,
		TAB = GLFW_KEY_TAB,
		BACKSPACE = GLFW_KEY_BACKSPACE,
		ENTER = GLFW_KEY_ENTER,

		INSERT = GLFW_KEY_INSERT,
		DELETE = GLFW_KEY_DELETE,
		HOME = GLFW_KEY_HOME,
		END = GLFW_KEY_END,
		PGUP = GLFW_KEY_PAGE_UP,
		PGDOWN = GLFW_KEY_PAGE_DOWN,

		PLUS = GLFW_KEY_KP_ADD,
		MINUS = GLFW_KEY_KP_SUBTRACT,
	};

	const std::string& ToString( EInputCode inputCode );
} // namespace gg