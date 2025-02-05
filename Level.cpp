#include "Level.h"
#include "LevelManager.h"

Level::Level(const string& _name, GameMode* _gamemode)
{
	gamemode = _gamemode;
	name = _name;
	window.create(VideoMode({ 1200, 600 }), name);
	window.setVisible(false);

	InitLevel();

	M_LEVEL.RegisterLevel(_name, this);
}

Level::~Level()
{
	delete gamemode;
}

void Level::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	actorManager.Update(_deltaTime);
	gamemode->GetPlayerController()->GetInputManager().Update(window);

	if (!window.isOpen())
	{
		OnUnload();
		M_LEVEL.SetLevel(nullptr);
	}
}

void Level::BeginPlay()
{
	SetActive(true);
	actorManager.BeginPlay(); // TODO Remplacer par construct
}

void Level::OnUnload()
{
	SetActive(false);
	window.clear();
}

void Level::BeginDestroy()
{
	actorManager.BeginDestroy();
}

void Level::UpdateWindow()
{
	window.clear();
	cameraManager.RenderAllCameras(window);
	window.display();
}

void Level::SetActive(const bool _active)
{
	Super::SetActive(_active);
	window.setVisible(_active);
}

void Level::InitLevel()
{
	CreateCamera(gamemode->GetPlayerController()->GetCamera()->GetObject());
}

