set(BOT_SOURCES
    BaseLocation.cpp
    BaseLocation.h
    BaseLocationManager.cpp
    BaseLocationManager.h
    BotAssert.cpp
    BotAssert.h
    BotConfig.cpp
    BotConfig.h
    BuildOrder.cpp
    BuildOrder.h
    BuildOrderQueue.cpp
    BuildOrderQueue.h
    Building.cpp
    Building.h
    BuildingData.cpp
    BuildingData.h
    BuildingManager.cpp
    BuildingManager.h
    BuildingPlacer.cpp
    BuildingPlacer.h
    CCBot.cpp
    CCBot.h
    CombatCommander.cpp
    CombatCommander.h
    Common.h
    Condition.cpp
    Condition.h
    DistanceMap.cpp
    DistanceMap.h
    GameCommander.cpp
    GameCommander.h
    JSONTools.cpp
    JSONTools.h
    MapTools.cpp
    MapTools.h
    MeleeManager.cpp
    MeleeManager.h
    MetaType.cpp
    MetaType.h
    MicroManager.cpp
    MicroManager.h
    ProductionManager.cpp
    ProductionManager.h
    RangedManager.cpp
    RangedManager.h
    ScoutManager.cpp
    ScoutManager.h
    Squad.cpp
    Squad.h
    SquadData.cpp
    SquadData.h
    SquadOrder.cpp
    SquadOrder.h
    StrategyManager.cpp
    StrategyManager.h
    TechTree.cpp
    TechTree.h
    Timer.hpp
    Unit.cpp
    Unit.h
    UnitData.cpp
    UnitData.h
    UnitInfoManager.cpp
    UnitInfoManager.h
    UnitType.cpp
    UnitType.h
    Util.cpp
    Util.h
    WorkerData.cpp
    WorkerData.h
    WorkerManager.cpp
    WorkerManager.h
    main.cpp
)

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
