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

    vector<Track*> allTracks = FileManager::GetInstance().ReadFolder<Track>("Assets\\Tracks");
    //new BeatMapLevel(*allTracks.begin[0], "Medium")
    //M_GAME.Launch(new BeatMapLevel(allTracks[0], "Medium"));

    M_GAME.Launch(new SelectLevel());

    for (Track* _track : allTracks)
	{
		delete _track;
	}

	return EXIT_SUCCESS;
}