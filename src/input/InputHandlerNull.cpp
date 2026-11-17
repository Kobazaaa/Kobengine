// -- Kobengine Includes --
#include "InputHandlerNull.h"

//--------------------------------------------------
//    Functionality
//--------------------------------------------------
void kobengine::InputHandlerNull::Update()											{ }

bool kobengine::InputHandlerNull::WasKeyDown(KeyCode)						const	{ return false; }
bool kobengine::InputHandlerNull::IsKeyDown(KeyCode)						const	{ return false; }

glm::vec2 kobengine::InputHandlerNull::GetMousePosition()					const	{ return {}; }
glm::vec2 kobengine::InputHandlerNull::GetMouseDelta()						const	{ return {}; }
bool kobengine::InputHandlerNull::IsMouseButtonDown(MouseButton)			const	{ return false; }
bool kobengine::InputHandlerNull::WasMouseButtonDown(MouseButton)			const	{ return false; }
