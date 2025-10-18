cmake_minimum_required(VERSION 4.0)
project(PhysicsPlayground LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PhysicsPlayground
        src/Renderer/Primitives/Primitive.cpp
        src/Renderer/Primitives/Primitive.h
        src/Renderer/Primitives/RectangleMesh.cpp
        src/Renderer/Primitives/RectangleMesh.h
        src/Renderer/Renderer.cpp
        src/Renderer/Renderer.h
        src/main.cpp
        src/Renderer/Shader.cpp
        src/Renderer/Shader.h
        src/Renderer/Primitives/TriangleMesh.cpp
        src/Renderer/Primitives/TriangleMesh.h
        src/Renderer/Primitives/CircleMesh.cpp
        src/Renderer/Primitives/CircleMesh.h
        src/Core/Application.cpp
        src/Core/Application.h
        src/Core/Layers/Layer.cpp
        src/Core/Layers/Layer.h
        src/Core/Layers/MainLayer.cpp
        src/Core/Layers/MainLayer.h
        src/Core/Layers/ImGuiLayer.cpp
        src/Core/Layers/ImGuiLayer.h
        src/Renderer/Primitives/PrimitiveVertex.cpp
        src/Renderer/Primitives/PrimitiveVertex.h
)

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
        GIT_TAG v1.91.5
)
FetchContent_MakeAvailable(imgui)

file(GLOB IMGUI_SRC
        ${imgui_SOURCE_DIR}/*.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui_lib ${IMGUI_SRC})
target_include_directories(imgui_lib PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui_lib PUBLIC glfw glad_lib)


target_link_libraries(PhysicsPlayground
        PRIVATE
        glad_lib
        glfw
        glm
        imgui_lib
)

target_include_directories(PhysicsPlayground PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)


set(ASSET_DIR_PATH "${CMAKE_SOURCE_DIR}/src/Renderer/Assets/")
target_compile_definitions(PhysicsPlayground PRIVATE ASSET_DIR_PATH="${ASSET_DIR_PATH}")