// -- Kobengine Includes --
#include "RenderLayer.h"


//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::RenderLayer::RenderLayer(pompeii::IWindow* pWindow)
	: m_pRenderer(std::make_shared<pompeii::Renderer>())
	, m_pWindow(pWindow)
{ }


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::RenderLayer::OnAttach()
{
	m_pRenderer->Initialize(m_pWindow);
}
void kobengine::RenderLayer::OnUpdate()
{
	m_pRenderer->Render();
}
void kobengine::RenderLayer::OnDetach()
{
	m_pRenderer->Deinitialize();
}

//--------------------------------------------------
//    Accessors
//--------------------------------------------------
std::shared_ptr<pompeii::Renderer> kobengine::RenderLayer::GetRenderer()
{
	return m_pRenderer;
}
