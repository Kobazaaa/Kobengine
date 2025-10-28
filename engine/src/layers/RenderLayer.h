#ifndef RENDER_LAYER_H
#define RENDER_LAYER_H

// -- Standard Library--
#include <memory>

// -- Kobengine Includes --
#include "ILayer.h"

// -- Pompeii Includes --
#include "Renderer.h"

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  RenderLayer	
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class RenderLayer final : public ILayer
	{
	public:
		//--------------------------------------------------
		//    Constructor & Destructor
		//--------------------------------------------------
		explicit RenderLayer();

		//--------------------------------------------------
		//    Loop
		//--------------------------------------------------
		void OnAttach() override;
		void OnUpdate() override;
		void OnDetach() override;

		std::shared_ptr<pompeii::Renderer> GetRenderer() { return m_pRenderer; }

	private:
		std::shared_ptr<pompeii::Renderer> m_pRenderer;
	};
}

#endif // RENDER_LAYER_H