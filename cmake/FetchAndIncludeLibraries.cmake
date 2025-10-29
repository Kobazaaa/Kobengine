include(FetchContent)

# Fetch GLFW
FetchContent_Declare(
   GLFW
   GIT_REPOSITORY https://github.com/glfw/glfw.git
   GIT_TAG 3.4
   GIT_SHALLOW TRUE
   GIT_PROGRESS TRUE
)

# Fetch GLM
FetchContent_Declare(
   GLM
   GIT_REPOSITORY https://github.com/g-truc/glm.git
   GIT_TAG 1.0.1
   GIT_SHALLOW TRUE
   GIT_PROGRESS TRUE
)

# Fetch stb
FetchContent_Declare(
   stb
   GIT_REPOSITORY https://github.com/nothings/stb.git
   GIT_TAG master
   GIT_SHALLOW TRUE
   GIT_PROGRESS TRUE
)

# Fetch assimp
FetchContent_Declare(
   assimp
   GIT_REPOSITORY https://github.com/assimp/assimp.git
   GIT_TAG v5.4.3
   GIT_SHALLOW TRUE
   GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(GLFW GLM stb assimp)

# Link libraries to the project
target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw
    glm::glm
    assimp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${stb_SOURCE_DIR}
    ${assimp_SOURCE_DIR}/include
)
