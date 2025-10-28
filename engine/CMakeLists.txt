#--------------------------------------------------
#    CREATE LIBRARY
#--------------------------------------------------
# Source files
set(SOURCES
	# main
	"${SOURCE_DIR}/main/main.cpp"
	"${SOURCE_DIR}/main/Application.cpp"

	# helper
	"${SOURCE_DIR}/helper/Timer.cpp"

	# layers
	"${SOURCE_DIR}/layers/LayerStack.cpp"

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

	# window
	"${SOURCE_DIR}/window/WindowGLFW.cpp"
)

# Create the library
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Set include directories
target_include_directories(${PROJECT_NAME} PUBLIC
	"${SOURCE_DIR}"
	"${SOURCE_DIR}/helper"
	"${SOURCE_DIR}/layers"
	"${SOURCE_DIR}/main"
	"${SOURCE_DIR}/managers"
	"${SOURCE_DIR}/scene"
	"${SOURCE_DIR}/scene/base"
	"${SOURCE_DIR}/scene/components"
	"${SOURCE_DIR}/scene/sceneobject"
	"${SOURCE_DIR}/systems"
	"${SOURCE_DIR}/window"
)

# Max Warning Level & Warnings as Errors

#--------------------------------------------------
#    LIBRARIES
#--------------------------------------------------
include("../cmake/FetchAndIncludeLibraries.cmake")
target_link_libraries(${PROJECT_NAME} PUBLIC Pompeii)
