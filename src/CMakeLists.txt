# All the source files for the bot.
file(GLOB BOT_SOURCES "*.cpp" "*.h" "*.hpp")

add_executable(CommandCenter ${BOT_SOURCES})

# Show more warnings at compiletime.
if (MSVC)
    target_compile_options(CommandCenter PRIVATE /W4 /EHsc)
else ()
    target_compile_options(CommandCenter PRIVATE -Wall -Wextra)
endif ()

target_link_libraries(CommandCenter PRIVATE cpp_sc2)

if (MINGW)
    target_link_libraries(CommandCenter PRIVATE ssp)
elseif (APPLE)
    target_link_libraries(CommandCenter PRIVATE "-framework Carbon")
elseif (UNIX AND NOT APPLE) # Building on Linux
    target_link_libraries(CommandCenter PRIVATE pthread dl)
endif ()
