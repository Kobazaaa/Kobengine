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

	# input
	"${SOURCE_DIR}/input/InputManager.cpp"
	"${SOURCE_DIR}/input/InputHandlerNull.cpp"

	# layers
	"${SOURCE_DIR}/layers/LayerStack.cpp"
	"${SOURCE_DIR}/layers/RenderLayer.cpp"

	# managers
	"${SOURCE_DIR}/managers/AssetManager.cpp"

	# platform
	 # platform/GLFW
	"${SOURCE_DIR}/platform/GLFW/WindowGLFW.cpp"
	"${SOURCE_DIR}/platform/GLFW/InputHandlerGLFW.cpp"
	
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
	"${SOURCE_DIR}/events"
	"${SOURCE_DIR}/helper"
	"${SOURCE_DIR}/input"
	"${SOURCE_DIR}/layers"
	"${SOURCE_DIR}/main"
	"${SOURCE_DIR}/managers"
	"${SOURCE_DIR}/platform"
	"${SOURCE_DIR}/platform/GLFW"
	"${SOURCE_DIR}/scene"
	"${SOURCE_DIR}/scene/base"
	"${SOURCE_DIR}/scene/components"
	"${SOURCE_DIR}/scene/sceneobject"
	"${SOURCE_DIR}/systems"
)

# Max Warning Level & Warnings as Errors

#--------------------------------------------------
#    LIBRARIES
#--------------------------------------------------
include("../cmake/FetchAndIncludeLibraries.cmake")
target_link_libraries(${PROJECT_NAME} PUBLIC Pompeii)
