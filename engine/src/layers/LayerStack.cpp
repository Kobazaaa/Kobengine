// -- Kobengine Includes --
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
kobengine::ILayer* kobengine::LayerStack::PushLayer(std::unique_ptr<ILayer> layer)
{
	m_vLayers.push_back(std::move(layer));
	auto ptr = m_vLayers.back().get();
	ptr->OnAttach();
	return ptr;
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
	m_vLayers.clear();
}
