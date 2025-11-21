// -- Kobengine Includes --
#include "InputManager.h"


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::InputManager::ProcessInput()
{
	m_pInputHandler->Update();

	ProcessKeyboard();
	ProcessMouse();
}


//--------------------------------------------------
//    Registration
//--------------------------------------------------
void kobengine::InputManager::SetInputHandler(std::unique_ptr<IInputHandler> handler)
{
	m_pInputHandler = std::move(handler);
}

void kobengine::InputManager::RegisterCommand(KeyCode key, TriggerState state, const Command& command)
{
	m_KeyboardMappings.insert(std::make_pair(key, InputDetails(state, command)));
}
void kobengine::InputManager::RegisterCommand(MouseButton button, TriggerState state, const Command& command)
{
	m_MouseMappings.insert(std::make_pair(button, InputDetails(state, command)));
}


//--------------------------------------------------
//    Accessors
//--------------------------------------------------
bool kobengine::InputManager::IsKeyDown(KeyCode key)
{
	return m_pInputHandler->IsKeyDown(key);
}

bool kobengine::InputManager::IsMouseButtonDown(MouseButton button)
{
	return m_pInputHandler->IsMouseButtonDown(button);
}
glm::vec2 kobengine::InputManager::GetMousePosition()
{
	return m_pInputHandler->GetMousePosition();
}
glm::vec2 kobengine::InputManager::GetMouseDelta()
{
	return m_pInputHandler->GetMouseDelta();
}


//--------------------------------------------------
//    Helpers
//--------------------------------------------------
void kobengine::InputManager::ProcessKeyboard()
{
	for (auto& [key, details] : m_KeyboardMappings)
	{
		bool isKeyDown = m_pInputHandler->IsKeyDown(key);
		bool wasKeyDown = m_pInputHandler->WasKeyDown(key);

		if (details.state == TriggerState::Press)
			if (isKeyDown && !wasKeyDown)
				details.command();

		if (details.state == TriggerState::Release)
			if (!isKeyDown && wasKeyDown)
				details.command();

		if (details.state == TriggerState::Hold)
			if (isKeyDown)
				details.command();
	}
}
void kobengine::InputManager::ProcessMouse()
{
	for (auto& [button, details] : m_MouseMappings)
	{
		bool isButtonDown = m_pInputHandler->IsMouseButtonDown(button);
		bool wasButtonDown = m_pInputHandler->WasMouseButtonDown(button);

		if (details.state == TriggerState::Press)
			if (isButtonDown && !wasButtonDown)
				details.command();

		if (details.state == TriggerState::Release)
			if (!isButtonDown && wasButtonDown)
				details.command();

		if (details.state == TriggerState::Hold)
			if (isButtonDown)
				details.command();
	}
}
