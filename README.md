# CommandCenter: AI Bot for Broodwar and Starcraft II

CommandCenter is a StarCraft AI bot that can play both StarCraft: Broodwar and StarCraft 2. This fork is focused on the StarCraft 2 part of the bot.

![CommandCenter Screenshot](https://i.imgur.com/SbTymsO.jpg)

CommandCenter is written in C++ using [BWAPI](https://github.com/bwapi/bwapi) and Blizzard's [StarCraft II AI API](https://github.com/Blizzard/s2client-api). It provides many wrapper functions around both APIs that allow it to perform the same functionality in both games via the same source code. It is written by [David Churchill](http://www.cs.mun.ca/~dchurchill/), Assistant Professor of [Computer Science](https://www.cs.mun.ca/) at Memorial University, and organizer of the [AIIDE StarCraft AI Competition](http://www.cs.mun.ca/~dchurchill/starcraftaicomp/).

CommandCenter is based on the architecture of [UAlbertaBot](https://github.com/davechurchill/ualbertabot/wiki), and is intended to be an easy to use architecture for you to quickly modify, play with, and build your own bot. The bot itself does not contain much in the way of hard-coded strategy or tactics, however it provides a good starting point for you to implement your own strategies for any race. 

CommandCenter currently provides the following features:
* Plays both Starcraft games with the same source code
* Plays all 3 races with generalized micro controllers for combat units
* Performs online map analysis, extracting information such as base locations and expansions
* Keeps track of all previously seen enemy units and their last known locations on the map
* Has a WorkerManager which manages resource gathering and worker allocation / buiding
* Is able to carry out predefined build-orders written in a configuration file
* Allows you to easily create your own build-orders and modify them on the fly in-game
* Contains a building placement algorithm, finding the closest buildable location to a given position for a given building 
* Scouts the map with a worker unit, discovering where the enemy base is located
* Once a specific condition has been reached (having 12 combat units, by default), it will commence an attack, sending waves of units at the enemy base
* Squads can be formed, consisting of multiple units following a specific order such as attack or defend a given location

CommandCenter should eventually have all of the functionality of UAlbertaBot, however much of its features are not currently completed. Here is an up-to-date list of features currently missing from CommandCenter that will be implemented soon:
* Only units and basic buildings can be constructed via the ProductionManager. No add-ons, research, or upgrades yet.
* There is no automatic build-order planning system
* There is no combat simulation package for predicting combat battle victory
* The bot only plays 1v1, and will have undefined behavior / crash if played against multiple enemies or on teams

# Download and Run CommandCenter

StarCraft 2: You must have an up-to-date retail version of StarCraft II installed to run the bot. You must also download and install some maps to use with the bot, which you can find here: https://github.com/Blizzard/s2client-proto#downloads. Please note that there is a password provided on that page to extract the maps from the zip files.

The bot comes with a configuration file named [BotConfig.txt](https://github.com/davechurchill/commandcenter/blob/master/bin/BotConfig.txt) in which you can modify build orders, print various debug information to the screen, and set some bot parameters. You can define multiple builds orders in the 'Strategies' section of the file, and choose which named strategy to implement when the bot plays a specific race. Unit names in the build-order are case sensitive, and must be exactly how they appear in-game with no spaces. Some of the options in the configuration file are currently not implemented, such as the KiteWithRangedUnits option.

Please note that this config file is in JSON format, and the bot will not run unless it is well-formatted JSON. The configuration file must be in the same directory as CommandCenter.exe in order for the bot to run correctly. If you have made an error in the JSON syntax and can't find it on your own, you can use an online [JSON Validator](https://jsonlint.com/) to check for you.

By default when you run CommandCenter.exe, it will play as Random race vs. a Random race built-in SC2 Easy AI. You can modify which races are played in the configuration file via the "BotRace" and "EnemyRace" options. You can also modify which map to be played by specifying the "MapFile" option. Please note that the MapFile option is relative to your StarCraft II maps directory, which by default is located in your StarCraft_Install_Directory/maps/, and the bot will not run without specifying a valid map file.

If the bot crashes or does other nasty things, please bear with me while I make it more stable :)

# Developer Install / Compile Instructions (Windows)
* Download and install [Visual Studio 2017 or newer](https://www.visualstudio.com/downloads/)
* Install [CMake](https://cmake.org/download/) and do

```bat
:: Get the project.
$ git clone --recursive https://github.com/cpp-sc2/commandcenter.git
$ cd commandcenter

:: Create build directory.
$ mkdir build
$ cd build

:: Create Visual Studio project files.
:: For Visual Studio 2019.
$ cmake ../ -G "Visual Studio 16 2019"
:: For Visual Studio 2017.
$ cmake ../ -G "Visual Studio 15 2017 Win64"

:: Build the project using Visual Studio.
:: The binary "CommandCenter_API.exe" should appear in the build/bin/ directory
$ start CommandCenter.sln

:: Launch the bot with the specified path to a SC2 map.
:: Warning: The CommandCenter/bin/BotConfig.txt file must be in the same directory as the .exe to run properly
$ bin\Debug\CommandCenter.exe Ladder2019Season3/AcropolisLE.SC2Map
```

# Developer Install / Compile Instructions (Linux and OS X)
* OS X: Download and install XCode and Xcode command-line tools.
* Linux: Install 'gcc-c++' with C++14 support and the 'make' utility.
* Install [CMake](https://cmake.org/download/) and do

```bash
# Create build directory.
$ mkdir build && cd build

# Generate a Makefile.
# Use 'cmake -DCMAKE_BUILD_TYPE=Debug ../' if debuginfo is needed
$ cmake ../

# Build the project.
$ VERBOSE=1 cmake --build . --parallel

# Launch the bot with the specified path to a SC2 map.
# Warning: The CommandCenter/bin/BotConfig.txt file must be in the same directory as the .exe to run properly
$ bin/Debug/CommandCenter Ladder2019Season3/AcropolisLE.SC2Map
```

# Bot Development

If you are familiar with the architecture of UAlbertaBot, the logic of CommandCenter is quite similar. The biggest difference is that information relating to the map, baselocation, etc are no longer globally accessible. This data now lives inside the main CCBot class, and must be accessed via a reference to the instance of that class. Because of this, most classes in CommandCenter carry with them a reference to the bot's main CCBot object, from which all game related information, observations, and queries can be made.

An in-depth development guide will be coming soon, but please refer to the [UAlbertaBot wiki](https://github.com/davechurchill/ualbertabot/wiki) for now since the architecture is so similar (minus the build order planner and combat simulator).
