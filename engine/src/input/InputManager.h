#ifndef KOBENGINE_INPUT_MANAGER_H
#define KOBENGINE_INPUT_MANAGER_H

// -- Standard Library --
#include <unordered_map>
#include <functional>
#include <memory>

// -- Kobengine Includes --
#include "InputStates.h"
#include "InputHandlerNull.h"

namespace kobengine
{
    //? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //? ~~    InputManager
    //? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    class InputManager
    {
    private:
        using Command = std::function<void()>;
    public:
        //--------------------------------------------------
        //    Constructor & Destructor
        //--------------------------------------------------
        explicit InputManager() = delete;
        ~InputManager() = delete;

		InputManager(const InputManager& other)					= delete;
		InputManager(InputManager&& other) noexcept				= delete;
		InputManager& operator=(const InputManager& other)		= delete;
		InputManager& operator=(InputManager&& other) noexcept	= delete;

		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
        static void ProcessInput();
		
        //--------------------------------------------------
		//    Registration
		//--------------------------------------------------
        static void SetInputHandler(std::unique_ptr<IInputHandler> handler);
        static void RegisterCommand(KeyCode key, TriggerState state, const Command& command);
        static void RegisterCommand(MouseButton button, TriggerState state, const Command& command);

        //--------------------------------------------------
		//    Accessors
		//--------------------------------------------------
        static bool IsKeyDown(KeyCode key);
        static bool IsMouseButtonDown(MouseButton button);
        static glm::vec2 GetMousePosition();
        static glm::vec2 GetMouseDelta();

    private:
        static void ProcessKeyboard();
        static void ProcessMouse();

        struct InputDetails
        {
            TriggerState state;
            Command command;
        };
        inline static std::unordered_multimap<KeyCode, InputDetails> m_KeyboardMappings;
        inline static std::unordered_multimap<MouseButton, InputDetails> m_MouseMappings;
        inline static std::unique_ptr<IInputHandler> m_pInputHandler { std::make_unique<InputHandlerNull>()};
    };
}

#endif // KOBENGINE_INPUT_MANAGER_H
