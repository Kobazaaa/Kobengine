#ifndef LAYER_STACK_H
#define LAYER_STACK_H

// -- Standard Library--
#include <memory>
#include <vector>

// -- Kobengine Includes --
#include "ILayer.h"

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  LayerStack	
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class LayerStack final
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		LayerStack() = default;
		~LayerStack();

		//--------------------------------------------------
		//    Utilities
		//--------------------------------------------------
		void PushLayer(std::unique_ptr<ILayer> layer);
		void PopLayer(ILayer* layer);

		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void UpdateAllLayers();
		void DetachAllLayers();

	private:
		std::vector<std::unique_ptr<ILayer>> m_vLayers;
	};
}

#endif // LAYER_STACK_H