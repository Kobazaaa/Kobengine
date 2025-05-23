#include "Component.h"


//--------------------------------------------------
//    Constructor
//--------------------------------------------------
kob::Component::Component(GameObject& parent)
	: m_pParent{ &parent }
{ }



//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kob::Component::Start() {}
void kob::Component::LateUpdate() {}
void kob::Component::FixedUpdate() {}
void kob::Component::Render() const {}
void kob::Component::ImGuiRenderUpdate() {}


//--------------------------------------------------
//    Accessors and Mutators
//--------------------------------------------------
void kob::Component::FlagForDeletion()
{
	m_DeletionFlag = true;
}
bool kob::Component::IsFlaggedForDeletion() const
{
	return m_DeletionFlag;
}

kob::GameObject* kob::Component::GetParent() const
{
	return m_pParent;
}
