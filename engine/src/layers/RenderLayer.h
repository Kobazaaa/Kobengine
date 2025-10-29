#ifndef RENDER_LAYER_H
#define RENDER_LAYER_H

// -- Standard Library--
#include <memory>

// -- Kobengine Includes --
#include "ILayer.h"
#include "Event.h"

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

		//--------------------------------------------------
		//    Accessors
		//--------------------------------------------------
		std::shared_ptr<pompeii::Renderer> GetRenderer();

		//--------------------------------------------------
		//    Events
		//--------------------------------------------------
		Event<const pompeii::Image&> OnImageRendered;

	private:
		std::shared_ptr<pompeii::Renderer> m_pRenderer;
	};
}

#endif // RENDER_LAYER_H