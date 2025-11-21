#ifndef KOBENGINE_GLFW_INPUT_HANDLER_H
#define KOBENGINE_GLFW_INPUT_HANDLER_H

// -- Standard Library --
#include <array>

// -- Kobengine Includes --
#include "IInputHandler.h"
#include "WindowGLFW.h"

namespace kobengine
{
    //? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //? ~~    InputHandlerGLFW
    //? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    class InputHandlerGLFW : public IInputHandler
    {
    public:
        //--------------------------------------------------
        //    Constructor & Destructor
        //--------------------------------------------------
        explicit InputHandlerGLFW(WindowGLFW* pWindow);
        ~InputHandlerGLFW() override = default;

        InputHandlerGLFW(const InputHandlerGLFW& other) = default;
        InputHandlerGLFW(InputHandlerGLFW&& other) noexcept = default;
        InputHandlerGLFW& operator=(const InputHandlerGLFW& other) = default;
        InputHandlerGLFW& operator=(InputHandlerGLFW&& other) noexcept = default;

        //--------------------------------------------------
        //    Functionality
        //--------------------------------------------------
        // -- General --
        void Update() override;

        // -- Keyboard --
        bool WasKeyDown(KeyCode key) const override;
        bool IsKeyDown(KeyCode key) const override;

        // -- Mouse --
        glm::vec2 GetMousePosition() const override;
        glm::vec2 GetMouseDelta() const override;
        bool IsMouseButtonDown(MouseButton button) const override;
        bool WasMouseButtonDown(MouseButton button) const override;

    private:
        static int ConvertToNativeKeyCode(KeyCode key);
        static int ConvertToNativeMouseButton(MouseButton key);

        WindowGLFW* m_pWindow;
        GLFWwindow* m_pNativeWindow;

        // -- Keyboard --
        std::array<bool, KOBENGINE_KEYCODE_COUNT> m_CurrentKeyStates{};
        std::array<bool, KOBENGINE_KEYCODE_COUNT> m_PreviousKeyStates{};

        // -- Mouse --
        glm::vec2 m_CurrentMousePos;
        glm::vec2 m_PreviousMousePos;
        std::array<bool, KOBENGINE_MOUSEBUTTON_COUNT> m_CurrentMouseStates{};
        std::array<bool, KOBENGINE_MOUSEBUTTON_COUNT> m_PreviousMouseStates{};
    };
}

#endif // KOBENGINE_NULL_INPUT_HANDLER_H
