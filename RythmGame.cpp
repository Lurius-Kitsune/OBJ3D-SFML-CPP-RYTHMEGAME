#include "RythmGame.h"
#include "CameraManager.h"
#include "TimerManager.h"
#include "GameManager.h"
#include "MeshActor.h"
#include "RectangleActor.h"
#include "HUD.h"

using namespace Camera;
using namespace UI;

RythmGame::RythmGame()
{
	allLevels = map<string, BeatMapLevel*>();
	background = nullptr;
}

RythmGame::~RythmGame()
{
	for (const pair<string,BeatMapLevel*>& _beatLevel : allLevels)
	{
		delete _beatLevel.second;
	}
}

void RythmGame::Start()
{
	Super::Start();
	const Vector2f _windowSize = CAST(Vector2f, M_GAME.GetCurrent()->GetWindowSize());

	M_CAMERA.CreateCamera<CameraActor>(FloatRect({ 0.0f, 0.0f }, _windowSize), "DefaultCamera");

	background = Level::SpawnActor(MeshActor(RectangleShapeData(_windowSize, "background"))); //TODO implemant Font
	background->SetOriginAtMiddle();
	background->SetPosition(_windowSize / 2.0f);
	background->SetScale({ 1.2f, 2.0f });
	background->SetRotation(degrees(45));
	background->SetFillColor(Color(255, 255, 255, 100));

	RectangleActor* _topSeparation = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(_windowSize.x, 5.0f), "background"))); //TODO implemant Font
	_topSeparation->SetFillColor(Color(255, 255, 255, 150));
	_topSeparation->SetPosition(Vector2f(0.0f, 60.0f));

	RectangleActor* _levelSeparation = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, _windowSize.y - 120.0f), "background"))); //TODO implemant Font
	_levelSeparation->SetFillColor(Color(255, 255, 255, 150));
	_levelSeparation->SetPosition(Vector2f(_windowSize.x * 0.6f, _topSeparation->GetPosition().y));

	RectangleActor* _bottomSeparation = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(_windowSize.x, 5.0f), "background"))); //TODO implemant Font
	_bottomSeparation->SetFillColor(Color(255, 255, 255, 150));
	_bottomSeparation->SetPosition(Vector2f(0.0f, _windowSize.y - 60.0f));

	Label* _label = M_HUD.CreateWidget<Label>("Select Level", Screen, "Test", TTF); //TODO implemant Font
	//_label->SetText("Select Level");
	_label->SetCharacterSize(35);
	_label->SetZOrder(2);
	_label->SetPosition(Vector2f(_windowSize.x * 0.05, 10));

	M_HUD.AddToViewport(_label);
	//allLevels["Test"] = new BeatMapLevel("Song Name !", "Very Hard");
}

bool RythmGame::Update()
{
	Super::Update();
	background->Rotate(degrees(M_TIMER.GetDeltaTime().asSeconds() * 10));


	allLevels["Test"]->Display();
	return IsOver();
}

void RythmGame::Stop()
{
	Super::Stop();


}
