#include "Game.h"
#include "GameManager.h"
#include "MargeurythmeGame.h"
#include "BeatMapLevel.h"
#include "SelectLevel.h"
#include "FileManager.h"

using namespace File;

void InitConfig()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Logger::Reset();
}

int main()
{
    InitConfig();

    set<Track*> allTracks = M_FILE.ReadFolder<Track>("Assets\\Tracks");

    M_GAME.Launch(new BeatMapLevel(*allTracks.begin(),"Medium"));

	return EXIT_SUCCESS;
}