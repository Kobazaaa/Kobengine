#pragma once
#include <memory>
#include <unordered_map>

#include "Command.h"
#include "Gamepad.h"
#include "Singleton.h"

namespace kob
{
	enum class TriggerState
	{
		Pressed,
		Down,
		Released
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		void RegisterGamepadButton(WORD button, std::unique_ptr<Command> cmd, TriggerState state);
		void RegisterKeyboardKey(SDL_KeyCode key, std::unique_ptr<Command> cmd, TriggerState state);
	private:
		void ProcessKeyboard();
		void ProcessGamepad();

		struct Input
		{
			TriggerState state;
			std::unique_ptr<Command> command;
		};

		Gamepad m_Gamepad{0};
		std::unordered_map<WORD, Input> m_GamepadMappings;
		std::unordered_map<SDL_KeyCode, Input> m_KeyboardMappings;

		Uint8 m_PreviousKeyboardStates[SDL_NUM_SCANCODES] = {0};
	};

}
