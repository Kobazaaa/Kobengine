// -- Kobengine Includes --
#include "InputHandlerGLFW.h"
#include "WindowGLFW.h"


//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::InputHandlerGLFW::InputHandlerGLFW(WindowGLFW* pWindow)
	: m_pWindow(pWindow)
	, m_pNativeWindow(static_cast<GLFWwindow*>(pWindow->GetNativeHandle()))
{ }


//--------------------------------------------------
//    Functionality
//--------------------------------------------------
// -- General --
void kobengine::InputHandlerGLFW::Update()
{
    // -- Keyboard --
    m_PreviousKeyStates = m_CurrentKeyStates;
    for (int i = 0; i < KOBENGINE_KEYCODE_COUNT; ++i)
    {
        KeyCode key = static_cast<KeyCode>(i);
        int native = ConvertToNativeKeyCode(key);

        if (native == GLFW_KEY_UNKNOWN)
        {
            m_CurrentKeyStates[i] = false;
            continue;
        }

        int state = glfwGetKey(m_pNativeWindow, native);
        m_CurrentKeyStates[i] = state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    // -- Mouse --
    m_PreviousMouseStates = m_CurrentMouseStates;
    for (int i = 0; i < KOBENGINE_MOUSEBUTTON_COUNT; ++i)
    {
        MouseButton key = static_cast<MouseButton>(i);
        int native = ConvertToNativeMouseButton(key);

        if (native == GLFW_KEY_UNKNOWN)
        {
            m_CurrentMouseStates[i] = false;
            continue;
        }

        int state = glfwGetMouseButton(m_pNativeWindow, native);
        m_CurrentMouseStates[i] = state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    m_PreviousMousePos = m_CurrentMousePos;
    double x;
    double y;
    glfwGetCursorPos(m_pNativeWindow, &x, &y);
	m_CurrentMousePos = glm::vec2(x, y);
}

// -- Keyboard --
bool kobengine::InputHandlerGLFW::WasKeyDown(KeyCode key) const
{
    int index = static_cast<int>(key);
    return m_PreviousKeyStates[index];
}
bool kobengine::InputHandlerGLFW::IsKeyDown(KeyCode key) const
{
    int index = static_cast<int>(key);
    return m_CurrentKeyStates[index];
}

// -- Mouse --
glm::vec2 kobengine::InputHandlerGLFW::GetMousePosition() const
{
    return m_CurrentMousePos;
}
glm::vec2 kobengine::InputHandlerGLFW::GetMouseDelta() const
{
    return m_CurrentMousePos - m_PreviousMousePos;
}
bool kobengine::InputHandlerGLFW::IsMouseButtonDown(MouseButton button) const
{
    int index = static_cast<int>(button);
    return m_CurrentMouseStates[index];
}
bool kobengine::InputHandlerGLFW::WasMouseButtonDown(MouseButton button) const
{
    int index = static_cast<int>(button);
    return m_PreviousMouseStates[index];
}

//--------------------------------------------------
//    Helper
//--------------------------------------------------
int kobengine::InputHandlerGLFW::ConvertToNativeKeyCode(KeyCode key)
{
    switch (key)
    {
		// Letters
        case KeyCode::A: return GLFW_KEY_A;
        case KeyCode::B: return GLFW_KEY_B;
        case KeyCode::C: return GLFW_KEY_C;
        case KeyCode::D: return GLFW_KEY_D;
        case KeyCode::E: return GLFW_KEY_E;
        case KeyCode::F: return GLFW_KEY_F;
        case KeyCode::G: return GLFW_KEY_G;
        case KeyCode::H: return GLFW_KEY_H;
        case KeyCode::I: return GLFW_KEY_I;
        case KeyCode::J: return GLFW_KEY_J;
        case KeyCode::K: return GLFW_KEY_K;
        case KeyCode::L: return GLFW_KEY_L;
        case KeyCode::M: return GLFW_KEY_M;
        case KeyCode::N: return GLFW_KEY_N;
        case KeyCode::O: return GLFW_KEY_O;
        case KeyCode::P: return GLFW_KEY_P;
        case KeyCode::Q: return GLFW_KEY_Q;
        case KeyCode::R: return GLFW_KEY_R;
        case KeyCode::S: return GLFW_KEY_S;
        case KeyCode::T: return GLFW_KEY_T;
        case KeyCode::U: return GLFW_KEY_U;
        case KeyCode::V: return GLFW_KEY_V;
        case KeyCode::W: return GLFW_KEY_W;
        case KeyCode::X: return GLFW_KEY_X;
        case KeyCode::Y: return GLFW_KEY_Y;
        case KeyCode::Z: return GLFW_KEY_Z;

		// Special Keys
        case KeyCode::LSHIFT: return GLFW_KEY_LEFT_SHIFT;

		// Function keys
        case KeyCode::F1:  return GLFW_KEY_F1;
        case KeyCode::F2:  return GLFW_KEY_F2;
        case KeyCode::F3:  return GLFW_KEY_F3;
        case KeyCode::F4:  return GLFW_KEY_F4;
        case KeyCode::F5:  return GLFW_KEY_F5;
        case KeyCode::F6:  return GLFW_KEY_F6;
        case KeyCode::F7:  return GLFW_KEY_F7;
        case KeyCode::F8:  return GLFW_KEY_F8;
        case KeyCode::F9:  return GLFW_KEY_F9;
        case KeyCode::F10: return GLFW_KEY_F10;
        case KeyCode::F11: return GLFW_KEY_F11;
        case KeyCode::F12: return GLFW_KEY_F12;

		// Numbers
        case KeyCode::Num0: return GLFW_KEY_0;
        case KeyCode::Num1: return GLFW_KEY_1;
        case KeyCode::Num2: return GLFW_KEY_2;
        case KeyCode::Num3: return GLFW_KEY_3;
        case KeyCode::Num4: return GLFW_KEY_4;
        case KeyCode::Num5: return GLFW_KEY_5;
        case KeyCode::Num6: return GLFW_KEY_6;
        case KeyCode::Num7: return GLFW_KEY_7;
        case KeyCode::Num8: return GLFW_KEY_8;
        case KeyCode::Num9: return GLFW_KEY_9;

		// Numpad
        case KeyCode::Numpad0: return GLFW_KEY_KP_0;
        case KeyCode::Numpad1: return GLFW_KEY_KP_1;
        case KeyCode::Numpad2: return GLFW_KEY_KP_2;
        case KeyCode::Numpad3: return GLFW_KEY_KP_3;
        case KeyCode::Numpad4: return GLFW_KEY_KP_4;
        case KeyCode::Numpad5: return GLFW_KEY_KP_5;
        case KeyCode::Numpad6: return GLFW_KEY_KP_6;
        case KeyCode::Numpad7: return GLFW_KEY_KP_7;
        case KeyCode::Numpad8: return GLFW_KEY_KP_8;
        case KeyCode::Numpad9: return GLFW_KEY_KP_9;

		// Arrow keys
        case KeyCode::ARROW_LEFT:  return GLFW_KEY_LEFT;
        case KeyCode::ARROW_RIGHT: return GLFW_KEY_RIGHT;
        case KeyCode::ARROW_UP:    return GLFW_KEY_UP;
        case KeyCode::ARROW_DOWN:  return GLFW_KEY_DOWN;

        default: return GLFW_KEY_UNKNOWN;
    }
}
int kobengine::InputHandlerGLFW::ConvertToNativeMouseButton(MouseButton key)
{
    switch (key)
    {
    case MouseButton::Left:     return GLFW_MOUSE_BUTTON_1;
    case MouseButton::Right:    return GLFW_MOUSE_BUTTON_2;
    case MouseButton::Middle:   return GLFW_MOUSE_BUTTON_3;
    case MouseButton::Button4:  return GLFW_MOUSE_BUTTON_4;
    case MouseButton::Button5:  return GLFW_MOUSE_BUTTON_5;

    default: return GLFW_KEY_UNKNOWN;
    }
}
