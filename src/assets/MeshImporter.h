#ifndef MESH_IMPORTER_H
#define MESH_IMPORTER_H

// -- Standard Library --
#include <string>

// -- Pompeii Includes --
#include "Handle.h"

// -- Forward Declarations --
namespace pompeii
{
	class Renderer;
}

namespace kobengine
{
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//? ~~	  Mesh Importer
	//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	class MeshImporter final
	{
	public:
		static pompeii::MeshHandle Import(pompeii::Renderer& renderer, const std::string& path);
	};
}

#endif // MESH_IMPORTER_H
