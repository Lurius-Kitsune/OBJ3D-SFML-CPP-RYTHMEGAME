#include "MargeurythmeGame.h"

#include "Level.h"
#include "FileManager.h"
#include "ActorManager.h"
#include "CameraManager.h"

using namespace File;

void MargeurythmeGame::Start()
{
	Super::Start();
	InitInput();
	allTracks =  M_FILE.ReadFolder<Track>("Assets\\Tracks");
	M_CAMERA.CreateCamera<CameraActor>(FloatRect({ 0.0f, 0.0f }, CAST(Vector2f, GetWindowSize())), "DefaultCamera");
	for(u_int _i = 0; _i < 4; _i++)
	{
		Note* _note = Level::SpawnActor(Note(NoteType(_i)));
		
		_note->SetPosition(Vector2f(60*_i, 0));
		triggers[NoteType(_i)] = Level::SpawnActor(NoteDetector(NoteType(_i)));
		triggers[NoteType(_i)]->SetPosition(Vector2f(60.0f+120.0f * _i, 700));
		triggers[NoteType(_i)]->SetOriginAtMiddle();
	}

	Track* _song = *allTracks.begin();
	beatMap = &_song->GetBeatMaps()["Medium"];
	_song->Start("Medium");
	
}

bool MargeurythmeGame::Update()
{
	if (beatMap)
	{
		beatMap->Update();
	}
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
