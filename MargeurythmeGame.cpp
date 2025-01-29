#include "MargeurythmeGame.h"

#include "Song.h"
#include "Level.h"

void MargeurythmeGame::Start()
{
	Super::Start();
	InitInput();

	for(u_int _i = 0; _i < 4; _i++)
	{
		Note* _note = Level::SpawnActor(Note(NoteType(_i)));

		_note->SetPosition(Vector2f(60*_i, 0));
		triggers[NoteType(_i)] = Level::SpawnActor(NoteDetector(NoteType(_i)));
		triggers[NoteType(_i)]->SetPosition(Vector2f(60.0f+120.0f * _i, 700));
		triggers[NoteType(_i)]->SetOriginAtMiddle();
	}
	Song* _song = new Song("CrabRave");
	beatMap = &_song->GetBeatMaps()["Medium"];
	_song->Start("Medium");
	
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
}

void MargeurythmeGame::InitInput()
{
	/*inputMap[Code::Left] = GameInput::Input::ARROW_LEFT;
	inputMap[Code::Right] = GameInput::Input::ARROW_RIGHT;
	inputMap[Code::Up] = GameInput::Input::ARROW_UP;
	inputMap[Code::Down] = GameInput::Input::ARROW_DOWN;*/

	//arrowLeft->InitInput();
}
