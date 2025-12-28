cmake_policy(SET CMP0135 NEW)
cmake_minimum_required(VERSION 3.21)
project(cpp_renderer VERSION 0.1 LANGUAGES CXX)

# Comment this to make it run fast!
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_TESTS "Build unit tests" ON)

include(GNUInstallDirs)
enable_testing()

# App target
add_executable(cpp_renderer src/main.cpp)
target_compile_options(cpp_renderer PRIVATE -g -O0)
target_compile_features(cpp_renderer PRIVATE cxx_std_17)

# Find SDL2 from the specified version
set(SDL2_VERSION "2.28.0")
set(SDL2_DIR "https://github.com/libsdl-org/SDL/releases/download/release-${SDL2_VERSION}/SDL2-${SDL2_VERSION}.tar.gz")

# Download and extract SDL2
include(FetchContent)
FetchContent_Declare(
    sdl2
    URL ${SDL2_DIR}
)
# Disable PipeWire audio backend to avoid incompatibility with newer PipeWire versions
set(SDL_PIPEWIRE OFF CACHE BOOL "Disable PipeWire audio backend" FORCE)
FetchContent_MakeAvailable(sdl2)

# Download and setup ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.90
)
FetchContent_MakeAvailable(imgui)

# Create ImGui library
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

# Find OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(imgui PUBLIC OpenGL::GL)

# Link SDL2 to ImGui
if(TARGET SDL2::SDL2)
    target_link_libraries(imgui PRIVATE SDL2::SDL2)
endif()

# Link SDL2 and ImGui
if(TARGET SDL2::SDL2)
    message(STATUS "Found SDL2 via config: using SDL2::SDL2 target")
    target_link_libraries(cpp_renderer PRIVATE SDL2::SDL2)
else()
    # If SDL2 wasn't found, fetch and build it as a subproject (fallback)
    include(FetchContent)
    FetchContent_Declare(
        SDL2repo
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.26.7
    )
    FetchContent_MakeAvailable(SDL2repo)
    # SDL adds SDL2::SDL2 target when built from source
    target_link_libraries(cpp_renderer PRIVATE SDL2::SDL2)
endif()

target_link_libraries(cpp_renderer PRIVATE imgui OpenGL::GL)
target_include_directories(cpp_renderer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Tests using Catch2
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)

    # Collect all test source files
    file(GLOB_RECURSE TEST_SOURCES "tests/**/*.cpp" "tests/*.cpp")
    
    add_executable(tests ${TEST_SOURCES})
    target_compile_options(tests PRIVATE -g -O0)
    target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
    target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
    add_test(NAME unit_tests COMMAND tests)
endif()

# Installation (optional)
install(TARGETS cpp_renderer
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
