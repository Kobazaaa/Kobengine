#--------------------------------------------------
#    CREATE LIBRARY
#--------------------------------------------------
# Source files
set(SOURCES
	# main
	"${SOURCE_DIR}/main/main.cpp"
	"${SOURCE_DIR}/main/Kobengine.cpp"

	# helper
	"${SOURCE_DIR}/helper/Timer.cpp"

	# managers
	"${SOURCE_DIR}/managers/AssetManager.cpp"
	
	# scene
	"${SOURCE_DIR}/scene/Scene.cpp"
	 # scene/base
	"${SOURCE_DIR}/scene/base/SceneManager.cpp"
	 # scene/components
	"${SOURCE_DIR}/scene/components/Camera.cpp"
	"${SOURCE_DIR}/scene/components/Component.cpp"
	"${SOURCE_DIR}/scene/components/LightComponent.cpp"
	"${SOURCE_DIR}/scene/components/MeshFilter.cpp"
	"${SOURCE_DIR}/scene/components/MeshRenderer.cpp"
	 # scene/sceneobject
	"${SOURCE_DIR}/scene/sceneobject/SceneObject.cpp"
	"${SOURCE_DIR}/scene/sceneobject/Transform.cpp"

	# systems
	"${SOURCE_DIR}/systems/LightingSystem.cpp"
	"${SOURCE_DIR}/systems/RenderSystem.cpp"
)

# Create the library
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Set include directories
target_include_directories(${PROJECT_NAME} PUBLIC
	"${SOURCE_DIR}"
	"${SOURCE_DIR}/helper"
	"${SOURCE_DIR}/main"
	"${SOURCE_DIR}/managers"
	"${SOURCE_DIR}/scene"
	"${SOURCE_DIR}/scene/base"
	"${SOURCE_DIR}/scene/components"
	"${SOURCE_DIR}/scene/sceneobject"
	"${SOURCE_DIR}/systems"
)

# Max Warning Level & Warnings as Errors
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

#--------------------------------------------------
#    LIBRARIES
#--------------------------------------------------
include("../cmake/FetchAndIncludeLibraries.cmake")
target_link_libraries(${PROJECT_NAME} PRIVATE Pompeii)
