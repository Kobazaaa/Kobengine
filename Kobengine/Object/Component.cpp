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

void kob::Component::OnCollisionEnter(GameObject&) { }
void kob::Component::OnCollisionExit(GameObject&) { }
void kob::Component::OnCollisionStay(GameObject&) { }


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

kob::GameObject* kob::Component::GetGameObject() const
{
	return m_pParent;
}
