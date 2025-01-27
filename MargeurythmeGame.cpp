#include "MargeurythmeGame.h"
#include "BeatMap.h"
#include "Level.h"

void MargeurythmeGame::Start()
{
	Super::Start();
	InitInput();

	for(u_int _i = 0; _i < 4; _i++)
	{
		Note* _note = Level::SpawnActor(Note(NoteType(_i)));

		_note->SetPosition(Vector2f(60*_i, 0));
	}

	BeatMap* _beatMap = new BeatMap("Assets/BeatMap/CrabRave.txt");
	_beatMap->Start();
	delete _beatMap;
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
