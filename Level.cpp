#include "Level.h"
#include "LevelManager.h"

Level::Level(const string& _name)
{
	isLoaded = false;
	window.create(VideoMode({ 1200, 600 }), _name);
	window.setVisible(false);
	name = _name;
	actorManager = ActorManager();
	cameraManager = CameraManager();
	gamemodeRef = GameMode();
	gamemode = nullptr;

	M_LEVEL.RegisterLevel(_name, this);
}


void Level::Update(const float _deltaTime)
{
	actorManager.Update(_deltaTime);
	//TODO change
	GetGameMode()->GetPlayerController()->GetInputManager().Update(window);

	if (!window.isOpen())
	{
		M_LEVEL.SetLevel(nullptr);
	}
}

void Level::UpdateWindow()
{
	window.clear();
	cameraManager.RenderAllCameras(window);
	window.display();
}

void Level::Load()
{
	if (!isLoaded)
	{
		InitLevel();
	}

	window.setVisible(true);
}

void Level::Unload()
{
	window.setVisible(false);
	window.clear();
}

void Level::InitLevel()
{
	isLoaded = true;
	//CreateCamera(gamemode->GetPlayerController()->GetCamera()->GetObject());
}