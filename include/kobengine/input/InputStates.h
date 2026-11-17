#ifndef KOBENGINE_INPUT_STATES_H
#define KOBENGINE_INPUT_STATES_H

namespace kobengine
{
	enum class TriggerState
	{
		Press,
		Hold,
		Release
	};

	enum class KeyCode
	{
		// -- Letters --
		A, 
		B, 
		C, 
		D, 
		E, 
		F, 
		G, 
		H, 
		I, 
		J, 
		K, 
		L, 
		M, 
		N, 
		O, 
		P, 
		Q, 
		R, 
		S, 
		T, 
		U, 
		V, 
		W,
		X, 
		Y,
		Z,

		// -- Special Keys --
		LSHIFT,

		// -- Function Keys --
		F1, 
		F2, 
		F3, 
		F4,
		F5, 
		F6,
		F7,
		F8, 
		F9,
		F10,
		F11,
		F12,

		// -- Numbers --
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,

		// -- Numpad Numbers --
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,

		// -- Arrow Keys --
		ARROW_LEFT, 
		ARROW_RIGHT,
		ARROW_UP, 
		ARROW_DOWN,
	};
	#define KOBENGINE_KEYCODE_COUNT 63

	enum class MouseButton
	{
		Left,
		Right,
		Middle,
		Button4,
		Button5
	};
	#define KOBENGINE_MOUSEBUTTON_COUNT 5
}

#endif // KOBENGINE_INPUT_STATES_H
