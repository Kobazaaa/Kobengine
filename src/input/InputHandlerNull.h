#ifndef KOBENGINE_NULL_INPUT_HANDLER_H
#define KOBENGINE_NULL_INPUT_HANDLER_H

// -- Kobengine Includes --
#include "IInputHandler.h"

namespace kobengine
{
    //? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //? ~~    InputHandlerNull
    //? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    class InputHandlerNull : public IInputHandler
    {
    public:
		//--------------------------------------------------
		//    Functionality
		//--------------------------------------------------
        void Update() override;
        bool WasKeyDown(KeyCode key) const override;
        bool IsKeyDown(KeyCode key) const override;
        glm::vec2 GetMousePosition() const override;
        glm::vec2 GetMouseDelta() const override;
        bool IsMouseButtonDown(MouseButton button) const override;
        bool WasMouseButtonDown(MouseButton button) const override;
    };
}

#endif // KOBENGINE_NULL_INPUT_HANDLER_H
