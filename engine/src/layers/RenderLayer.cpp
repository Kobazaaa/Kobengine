// -- Kobengine Includes --
#include "RenderLayer.h"


//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::RenderLayer::RenderLayer()
	: m_pRenderer(std::make_shared<pompeii::Renderer>())
{
	
}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::RenderLayer::OnAttach()
{
	m_pRenderer->Initialize();
}
void kobengine::RenderLayer::OnUpdate()
{
	auto& renderedImage = m_pRenderer->Render();
	OnImageRendered.Invoke(renderedImage);
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
