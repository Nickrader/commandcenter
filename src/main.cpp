#include "Common.h"
#include "CCBot.h"
#include "JSONTools.h"
#include "Util.h"

#include "sc2utils/sc2_manage_process.h"
#include "sc2api/sc2_api.h"

int main(int argc, char* argv[])
{
    sc2::Coordinator coordinator;
    if (!coordinator.LoadSettings(argc, argv))
    {
        std::cout << "Unable to find or parse settings." << std::endl;
        return 1;
    }

    std::string config = JSONTools::ReadFile("BotConfig.txt");
    if (config.length() == 0)
    {
        std::cerr << "Config file could not be found, and is required for starting the bot\n";
        std::cerr << "Please read the instructions and try again\n";

	std::cerr << "Error could also be caused by not being in directory of bot_executable, when invoking executable.  Try changing directory before launching bot.\n";
	
        exit(-1);
    }

    std::ifstream file("BotConfig.txt");
    json j;
    file >> j;

    /*if (parsingFailed)
    {
        std::cerr << "Config file could not be parsed, and is required for starting the bot\n";
        std::cerr << "Please read the instructions and try again\n";
        exit(-1);
    }*/

    std::string botRaceString;
    std::string enemyRaceString;
    std::string mapString;
    int stepSize = 1;
    sc2::Difficulty enemyDifficulty = sc2::Difficulty::Easy;

    if (j.count("SC2API") && j["SC2API"].is_object())
    {
        const json & info = j["SC2API"];
        JSONTools::ReadString("BotRace", info, botRaceString);
        JSONTools::ReadString("EnemyRace", info, enemyRaceString);
        JSONTools::ReadString("MapFile", info, mapString);
        JSONTools::ReadInt("StepSize", info, stepSize);
        JSONTools::ReadInt("EnemyDifficulty", info, enemyDifficulty);
    }
    else
    {
        std::cerr << "Config file has no 'Game Info' object, required for starting the bot\n";
        std::cerr << "Please read the instructions and try again\n";
        exit(-1);
    }

    // Add the custom bot, it will control the players.
    CCBot bot;


    // WARNING: Bot logic has not been thorougly tested on step sizes > 1
    //          Setting this = N means the bot's onFrame gets called once every N frames
    //          The bot may crash or do unexpected things if its logic is not called every frame
    const std::string wine = "/home/ransak/.local/share/lutris/runners/wine/wine-ge-8-26-x86_64/bin/wine64";
    //    const std::string wine = "/usr/bin/wine"; // 

    // {"start","/d","/path/to/Support64/","/unix","/path/to/SC2Switcher"}
    const std::vector<std::string> runner = {
        "start", "/d", "/home/ransak/Games/battlenet/drive_c/Program Files (x86)/StarCraft II/Support64/", "/unix",
        "/home/ransak/Games/battlenet/drive_c/Program Files (x86)/StarCraft II/Support64/SC2Switcher_x64.exe"};
    coordinator.SetLutris(wine, runner);


    //    const std::string SC2SWITCHER = "/home/ransak/Games/battlenet/drive_c/Program Files (x86)/StarCraft II/Support64/SC2Switcher_x64.exe";
    // coordinator.SetProcessPath(SC2SWITCHER);
    coordinator.SetStepSize(stepSize);
    coordinator.SetRealtime(false);

    coordinator.SetParticipants({
        sc2::CreateParticipant(Util::GetRaceFromString(botRaceString), &bot),
        sc2::CreateComputer(Util::GetRaceFromString(enemyRaceString), enemyDifficulty)
    });

    // Start the game.
    coordinator.LaunchStarcraft();
    coordinator.StartGame(mapString);

    // Step forward the game simulation.
    while (true)
    {
        coordinator.Update();
    }

    return 0;
}
