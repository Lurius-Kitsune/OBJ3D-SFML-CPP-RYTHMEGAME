#include "MargeurythmeGame.h"

#include "Level.h"

void MargeurythmeGame::Start()
{
	Super::Start();
	InitInput();

	for(u_int _i = 0; _i < 4; _i++)
	{
		Note* _note = Level::SpawnActor(Note(NoteType(_i)));

		_note->SetPosition(Vector2f(60*_i, 0));
		triggers[NoteType(_i)] = Level::SpawnActor(SquareActor(50.0f));
		triggers[NoteType(_i)]->SetPosition(Vector2f(100+ 60 * _i, 700));
		triggers[NoteType(_i)]->SetOriginAtMiddle();
	}

	

	beatMap = new BeatMap("Assets/BeatMap/CrabRave.txt");
	beatMap->Start();
	
}

bool MargeurythmeGame::Update()
{
	LOG(Display, beatMap->GetCurrentTimeAsString());
	beatMap->Update();
	return Super::Update();
}

void MargeurythmeGame::Stop()
{
		Super::Stop();
		delete beatMap;
}

void MargeurythmeGame::InitInput()
{
	inputMap[Code::Left] = GameInput::Input::ARROW_LEFT;
	inputMap[Code::Right] = GameInput::Input::ARROW_RIGHT;
	inputMap[Code::Up] = GameInput::Input::ARROW_UP;
	inputMap[Code::Down] = GameInput::Input::ARROW_DOWN;

	//arrowLeft->InitInput();
}
