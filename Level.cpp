#include "Level.h"
#include "LevelManager.h"
#include "ActorManager.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "GameMode.h"

Level::Level(const string& _name)
{
	isLoaded = false;
	name = _name;
	actorManager = ActorManager();
	cameraManager = Camera::CameraManager();
	collisionManager = CollisionManager();
	audioManager = AudioManager();
	gameMode = nullptr;

	window.create(VideoMode({ 1200, 600 }), _name);
	window.setVisible(false);

	M_LEVEL.RegisterLevel(_name, this);
}


void Level::UpdateWindow()
{
	window.clear();
	cameraManager.Render(window, GetGameMode()->IsSplitScreen());
	window.display();
}

void Level::InitLevel()
{
	CameraActor* _camera = SpawnActor<CameraActor>("DefaultCamera");
	cameraManager.Register(_camera->GetCamera());
}

void Level::Update(const float _deltaTime)
{
	UpdateWindow();
	actorManager.Update(_deltaTime);

	if (!window.isOpen())
	{
		M_LEVEL.SetLevel(nullptr);
	}
}

void Level::Load()
{
	if (!isLoaded)
	{
		InitLevel();
		isLoaded = true;
	}

	window.setVisible(true);
	actorManager.BeginPlay();
}

void Level::Unload()
{
	window.setVisible(false);
	window.clear();
	actorManager.BeginDestroy();
}