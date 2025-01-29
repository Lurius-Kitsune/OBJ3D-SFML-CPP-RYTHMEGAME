#include "SelectLevel.h"
#include "CameraManager.h"
#include "TimerManager.h"
#include "GameManager.h"
#include "MeshActor.h"
#include "ActorManager.h"
#include "RectangleActor.h"
#include "HUD.h"

using namespace Camera;
using namespace UI;

SelectLevel::SelectLevel()
{
	allSounds = {};
	background = nullptr;
	windowSize = Vector2f();
}

SelectLevel::~SelectLevel()
{
	for (Song* _song : allSounds)
	{
		delete _song;
	}
}

void SelectLevel::InitSeparator(Song* _song)
{
	RectangleActor* _topSeparation = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(windowSize.x, 5.0f), "background"))); //TODO implemant Font
	_topSeparation->SetFillColor(Color(255, 255, 255, 150));
	_topSeparation->SetPosition(Vector2f(0.0f, 60.0f));

	RectangleActor* _levelSeparation = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 120.0f), "background"))); //TODO implemant Font
	_levelSeparation->SetFillColor(Color(255, 255, 255, 150));
	_levelSeparation->SetPosition(Vector2f(windowSize.x * 0.6f, _topSeparation->GetPosition().y));

	RectangleActor* _bottomSeparation = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(windowSize.x, 5.0f), "background"))); //TODO implemant Font
	_bottomSeparation->SetFillColor(Color(255, 255, 255, 150));
	_bottomSeparation->SetPosition(Vector2f(0.0f, windowSize.y - 60.0f));
}

void SelectLevel::InitLabel(Song* _song)
{
	Label* _label = M_HUD.CreateWidget<Label>("Select Level", Screen, "Test", TTF); //TODO implemant Font
	_label->SetCharacterSize(35);
	_label->SetZOrder(2);
	_label->SetPosition(Vector2f(windowSize.x * 0.05f, 10.0f));

	Label* _title = M_HUD.CreateWidget<Label>(_song->GetTitle(), Screen, "Test", TTF); //TODO implemant Font
	_title->SetCharacterSize(50);
	_title->SetZOrder(2);
	_title->SetPosition(Vector2f(windowSize.x * 0.65f, windowSize.y * 0.2f));

	Label* _artist = M_HUD.CreateWidget<Label>(_song->GetArtist(), Screen, "Test", TTF); //TODO implemant Font
	_artist->SetCharacterSize(25);
	_artist->SetZOrder(2);
	_artist->SetPosition(Vector2f(windowSize.x * 0.65f, windowSize.y * 0.3f));

	Label* _duration = M_HUD.CreateWidget<Label>(to_string(_song->GetDuration().asSeconds()), Screen, "Test", TTF); //TODO implemant Font
	_duration->SetCharacterSize(20);
	_duration->SetZOrder(2);
	_duration->SetPosition(Vector2f(windowSize.x * 0.8f, windowSize.y * 0.4f));

	Label* _easy = M_HUD.CreateWidget<Label>("Easy", Screen, "Test", TTF); //TODO implemant Font
	_easy->SetCharacterSize(20);
	_easy->SetZOrder(2);
	_easy->SetFillColor(Color(50, 189, 22));
	_easy->SetPosition(Vector2f(windowSize.x * 0.65, windowSize.y * 0.5f));

	//TODO Replace with button
	Label* _play = M_HUD.CreateWidget<Label>("PLAY", Screen, "Test", TTF); //TODO implemant Font
	_play->SetCharacterSize(30);
	_play->SetZOrder(2);
	_play->SetPosition(Vector2f(windowSize.x * 0.875f, windowSize.y - 45.0f));

	M_HUD.AddToViewport(_label);
	M_HUD.AddToViewport(_title);
	M_HUD.AddToViewport(_artist);
	M_HUD.AddToViewport(_duration);
	M_HUD.AddToViewport(_easy);
	M_HUD.AddToViewport(_play);
}

void SelectLevel::Start()
{
	Super::Start();
	windowSize = CAST(Vector2f, M_GAME.GetCurrent()->GetWindowSize());

	M_CAMERA.CreateCamera<CameraActor>(FloatRect({ 0.0f, 0.0f }, windowSize), "DefaultCamera");

	background = Level::SpawnActor(MeshActor(RectangleShapeData(windowSize, "background"))); //TODO implemant Font
	background->SetOriginAtMiddle();
	background->SetPosition(windowSize / 2.0f);
	background->SetScale({ 1.2f, 2.0f });
	background->SetRotation(degrees(45));
	background->SetFillColor(Color(255, 255, 255, 100));

	allSounds.push_back(new Song("CrabRave"));

	//TODO Replace with selected Sound
	for (Song* _song : allSounds)
	{
		allButtons.push_back(new Button("Button", Screen, _song));
		InitSeparator(_song);
		InitLabel(_song);
	}


	M_ACTOR.BeginPlay();
	//allLevels["Test"] = new BeatMapLevel("Song Name !", "Very Hard");
}

bool SelectLevel::Update()
{
	Super::Update();
	background->Rotate(degrees(M_TIMER.GetDeltaTime().asSeconds() * 10));

	return IsOver();
}

void SelectLevel::Stop()
{
	Super::Stop();


}