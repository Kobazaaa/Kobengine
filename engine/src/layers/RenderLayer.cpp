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
	renderedImage;
}

void kobengine::RenderLayer::OnDetach()
{
	m_pRenderer->Deinitialize();
}
