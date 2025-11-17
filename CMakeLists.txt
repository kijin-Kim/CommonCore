cmake_minimum_required(VERSION 4.0)
project(CommonCore LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE COMMON_SOURCE_FILES src/*.cpp src/*.h)

add_library(CommonCore ${COMMON_SOURCE_FILES}
        src/Renderer/Shapes.cpp
        src/Renderer/Shapes.h
        src/Renderer/ShapeUtility.cpp
        src/Renderer/ShapeUtility.h
        src/Core/EventBus.cpp
        src/Core/EventBus.h
        src/Core/IniParser.cpp
        src/Core/IniParser.h
        src/Core/JobSystem.cpp
        src/Core/JobSystem.h
        src/Renderer/ResourceManager.cpp
        src/Renderer/ResourceManager.h
        src/Renderer/ResourceManager.cpp
        src/Renderer/ResourceManager.h
        src/Core/Delegate.cpp
        src/Core/Delegate.h
        src/Renderer/FrameBuffer.cpp
        src/Renderer/FrameBuffer.h
        src/Renderer/ImageTexture.cpp
        src/Renderer/ImageTexture.h
        src/Core/Assert.h)

include(FetchContent)

FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG c
)
FetchContent_MakeAvailable(glad)
add_library(glad_lib ${glad_SOURCE_DIR}/src/glad.c)
target_include_directories(glad_lib PUBLIC ${glad_SOURCE_DIR}/include)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.5-docking
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
        tracy
        GIT_REPOSITORY https://github.com/wolfpld/tracy.git
        GIT_TAG v0.12.2
)
FetchContent_MakeAvailable(tracy)

file(GLOB IMGUI_SRC
        ${imgui_SOURCE_DIR}/*.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
)

add_library(imgui_lib ${IMGUI_SRC})
target_include_directories(imgui_lib PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
        ${imgui_SOURCE_DIR}/misc/cpp
)
target_link_libraries(imgui_lib PUBLIC glfw glad_lib)


target_link_libraries(CommonCore
        PUBLIC
        glad_lib
        glfw
        glm
        imgui_lib
        nlohmann_json::nlohmann_json
        TracyClient
)

target_include_directories(CommonCore PUBLIC
        ${CommonCore_SOURCE_DIR}/src
        ${CommonCore_SOURCE_DIR}/external
)

set(CORE_ASSET_PATH "${CommonCore_SOURCE_DIR}/src/Renderer/Assets/")
target_compile_definitions(CommonCore PUBLIC CORE_ASSET_PATH="${CORE_ASSET_PATH}" GLFW_INCLUDE_NONE GLM_ENABLE_EXPERIMENTAL STB_IMAGE_IMPLEMENTATION)
target_compile_definitions(CommonCore PUBLIC $<$<CONFIG:Debug>:TRACY_ENABLE>)



