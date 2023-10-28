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

    # Make directory that 'Build' in Visual Studio would, so we can move BotConfig.txt
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin/Debug)
    file(COPY_FILE ${CMAKE_SOURCE_DIR}/bin/BotConfig.txt ${CMAKE_SOURCE_DIR}/build/bin/Debug/BotConfig.txt)

    # Set startup project so we don't have to in IDE
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT CommandCenter)

endif ()

list(APPEND CMAKE_MODULE_PATH thirdparty/cmake)

# Dependencies
include(cpp_sc2)
include_directories(thirdparty)

add_subdirectory(src)
