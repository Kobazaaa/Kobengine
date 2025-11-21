#ifndef KOBENGINE_INTERFACE_INPUT_HANDLER_H
#define KOBENGINE_INTERFACE_INPUT_HANDLER_H

// -- Kobengine Includes --
#include "InputStates.h"
#include "glm/glm.hpp"

namespace kobengine
{
    //? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //? ~~    IInputHandler
    //? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    class IInputHandler
    {
    public:
        //--------------------------------------------------
        //    Constructor & Destructor
        //--------------------------------------------------
        virtual ~IInputHandler() = default;

		//--------------------------------------------------
		//    Functionality
		//--------------------------------------------------
        // -- General --
        virtual void Update() = 0;

        // -- Keyboard --
        virtual bool WasKeyDown(KeyCode key) const = 0;
        virtual bool IsKeyDown(KeyCode key) const = 0;

        // -- Mouse --
        virtual glm::vec2 GetMousePosition() const = 0;
        virtual glm::vec2 GetMouseDelta() const = 0;
        virtual bool IsMouseButtonDown(MouseButton button) const = 0;
        virtual bool WasMouseButtonDown(MouseButton button) const = 0;
    };
}

#endif // KOBENGINE_INTERFACE_INPUT_HANDLER_H
