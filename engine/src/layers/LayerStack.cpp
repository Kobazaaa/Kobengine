#include "LayerStack.h"


//--------------------------------------------------
//    Constructor & Destructor
//--------------------------------------------------
kobengine::LayerStack::~LayerStack()
{
	DetachAllLayers();
}


//--------------------------------------------------
//    Utilities
//--------------------------------------------------
void kobengine::LayerStack::PushLayer(std::unique_ptr<ILayer> layer)
{
	m_vLayers.push_back(std::move(layer));
	m_vLayers.back()->OnAttach();
}
void kobengine::LayerStack::PopLayer(ILayer* layer)
{
	layer->OnDetach();
	std::erase_if(m_vLayers, [layer](const std::unique_ptr<ILayer>& iLayer) { return layer == iLayer.get(); });
}


//--------------------------------------------------
//    Loop
//--------------------------------------------------
void kobengine::LayerStack::UpdateAllLayers()
{
	for (const auto& layer : m_vLayers)
		layer->OnUpdate();
}
void kobengine::LayerStack::DetachAllLayers()
{
	for (const auto& layer : m_vLayers)
		layer->OnDetach();
}
