cmake_minimum_required(VERSION 3.15)

project(CommandCenter)

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

    # Make directory that 'Build' in Visual Studio would, so we can move BotConfig.txt
    # Loop over, Release, Debug, MinSizeRel, RelWithDebInfo
    list(APPEND BuildOutputList Release Debug MinSizeRel RelWithDebInfo)
    foreach(output IN LISTS BuildOutputList)
    file(MAKE_DIRECTORY	${CMAKE_SOURCE_DIR}/build/bin/${output})

    #Copy the example to build/bin/${output}
    file(COPY_FILE ${CMAKE_SOURCE_DIR}/config/BotConfig.example.txt ${CMAKE_SOURCE_DIR}/build/bin/${output}/BotConfig.txt)

    ### TODO ###
    # make symoblic link BotConfig.txt
    # permissions error, doing this in Windows.  Would need elevated permissions.
    # this would also mean we are stuck with name BotConfig.example.txt
    # confirmed works with elevated permissions.  
    # Verdict: Probably good to lose this approach. 
    #
    # mklink ${CMAKE_SOURCE_DIR}/build/bin/${output}/BotConfig.txt ${CMAKE_SOURCE_DIR}/config/BotConfig.example.txt
    endforeach()

    # Set startup project so we don't have to in IDE
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT CommandCenter)

endif ()

list(APPEND CMAKE_MODULE_PATH thirdparty/cmake)

# Dependencies
include(cpp_sc2)
include_directories(thirdparty)

add_subdirectory(src)
