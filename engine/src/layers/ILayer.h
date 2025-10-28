#ifndef INTERFACE_LAYER_H
#define INTERFACE_LAYER_H

// -- Standard Library --
#include <string>

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  ILayer	
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class ILayer
	{
	public:
		virtual ~ILayer() = default;

		virtual void OnAttach() {}
		virtual void OnUpdate() {}
		virtual void OnDetach() {}
	};
}

#endif // INTERFACE_LAYER_H