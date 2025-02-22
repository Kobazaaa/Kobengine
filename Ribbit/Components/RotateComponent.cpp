#include "RotateComponent.h"
#include "GameObject.h"
#include "Timer.h"


//--------------------------------------------------
//    Constructor
//--------------------------------------------------
rib::RotateComponent::RotateComponent(GameObject& parent, float speed, float radius)
	: Component(parent)
	, m_CenterPoint	{ parent.GetLocalTransform().GetPosition() }
	, m_Speed		{ speed }
	, m_Radius		{ radius }
{}



//--------------------------------------------------
//    Loop
//--------------------------------------------------
void rib::RotateComponent::Update()
{
	float x = m_CenterPoint.x + m_Radius * cos(m_Speed * Timer::GetTotalTimeSeconds());
	float y = m_CenterPoint.y + m_Radius * sin(m_Speed * Timer::GetTotalTimeSeconds());
	GetParent()->SetLocalPosition(glm::vec3(x, y, 0));
}
