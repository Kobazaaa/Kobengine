#include "Component.h"


//--------------------------------------------------
//    Constructor
//--------------------------------------------------
rib::Component::Component(GameObject& parent)
	: m_pParent{ &parent }
{ }



//--------------------------------------------------
//    Loop
//--------------------------------------------------
void rib::Component::Start() {}
void rib::Component::LateUpdate() {}
void rib::Component::FixedUpdate() {}
void rib::Component::Render() const {}


//--------------------------------------------------
//    Accessors and Mutators
//--------------------------------------------------
void rib::Component::FlagForDeletion()
{
	m_DeletionFlag = true;
}
bool rib::Component::IsFlaggedForDeletion() const
{
	return m_DeletionFlag;
}

rib::GameObject* rib::Component::GetParent() const
{
	return m_pParent;
}
