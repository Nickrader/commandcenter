cmake_minimum_required(VERSION 3.15)

project(CommandCenter)

include(FetchContent)

# Specify output directories.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

# Build with c++14 support, required by sc2api.
set(CMAKE_CXX_STANDARD 14)

if (MSVC)
    # Setup MSVC parallelized builds
    add_compile_options(/MP)

    # Use statically linked runtime
    set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>)
endif ()

list(APPEND CMAKE_MODULE_PATH thirdparty/cmake)

# cpp-sc2 dependency
include(cpp_sc2)

add_subdirectory(src)
