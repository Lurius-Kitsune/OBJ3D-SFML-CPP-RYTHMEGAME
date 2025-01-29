#include "MargeurythmeGame.h"
#include "Tracks.h"
#include "Level.h"
#include "FileManager.h"

using namespace File;

void MargeurythmeGame::Start()
{
	Super::Start();
	InitInput();


	set<Tracks> _allTracks =  M_FILE.ReadFolder<Tracks>("Assets\\Tracks");
}

bool MargeurythmeGame::Update()
{
	
	return Super::Update();
}

void MargeurythmeGame::Stop()
{
	Super::Stop();
}

void MargeurythmeGame::InitInput()
{
	inputMap[Code::Left] = GameInput::Input::ARROW_LEFT;
	inputMap[Code::Right] = GameInput::Input::ARROW_RIGHT;
	inputMap[Code::Up] = GameInput::Input::ARROW_UP;
	inputMap[Code::Down] = GameInput::Input::ARROW_DOWN;

	//arrowLeft->InitInput();
}
