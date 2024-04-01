cmake_minimum_required(VERSION 3.15)

project(CommandCenter)
set(cmake_export_compile_commands = 1)

include(FetchContent)

# Specify output directories.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

# Build with c++17 support, required by sc2api.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    # Setup MSVC parallelized builds
    add_compile_options(/MP)

    # Use statically linked runtime
    set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>)
endif ()

list(APPEND CMAKE_MODULE_PATH thirdparty/cmake)

# Dependencies
include(cpp_sc2)
include_directories(thirdparty)

add_subdirectory(src)
