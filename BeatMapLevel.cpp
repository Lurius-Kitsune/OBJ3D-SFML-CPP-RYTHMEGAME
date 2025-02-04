#include "BeatMapLevel.h"
#include "GameManager.h"
#include "TimerManager.h"
#include "MeshActor.h"
#include "RectangleActor.h"
#include "CameraManager.h"
#include "HUD.h"
#include "FileManager.h"
#include "ProgressBar.h"

using namespace File;
using namespace Camera;
using namespace UI;

BeatMapLevel::BeatMapLevel(Track* _track, const string& _difficulty)
{
	score = nullptr;
	comboData = make_unique<ComboData>();
	triggers = map<NoteType, NoteDetector*>();
	track = _track;
	trackInfo = track->GetInfo();
	difficulty = _difficulty;
}

void BeatMapLevel::Start()
{
	Super::Start();
	windowSize = M_GAME.GetCurrent()->GetWindowSize();
	M_CAMERA.CreateCamera<CameraActor>(FloatRect({}, CAST(Vector2f, M_GAME.GetCurrent()->GetWindowSize())), "DefaultCamera");

	InitLevelAspect();
	InitHUD();
	InitNoteTriggerAndSpawner();

	track->Start(difficulty);

	//new Timer([&]() {IncrementCombo(); }, Time(seconds(5.0f)), true, true);
}

bool BeatMapLevel::Update()
{
	track->Update();

	if (track->IsFinished())
	{
		track->Stop();
		score->SetScore(0);
		comboData->SetCount(0);
	}
	return Super::Update();
}

void BeatMapLevel::Stop()
{
	Super::Stop();
	track->Stop();
}

void BeatMapLevel::InitLevelAspect()
{
	MeshActor* _background = Level::SpawnActor(MeshActor(RectangleShapeData(CAST(Vector2f, windowSize), "background"))); //TODO implemant Font
	_background->SetFillColor(Color(255, 255, 255, 100));
	_background->SetFillColor(Color(255, 255, 255, 100));
	RectangleActor* _layerDark = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(windowSize.x * 1.0f, 60.0f)))); //TODO implemant Font
	_layerDark->SetFillColor(Color(0, 0, 0, 50));

	RectangleActor* _separation = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(windowSize.x * 1.0f, 5.0f)))); //TODO implemant Font
	_separation->GetMesh()->GetShape()->GetDrawable()->setTexture(nullptr);
	_separation->SetFillColor(Color(255, 255, 255, 150));
	_separation->SetPosition(Vector2f(0.0f, 60.0f));
}

void BeatMapLevel::InitHUD()
{
	//_layer->SetOutlineColor(Color(, 0, 0, 25));
	score = M_HUD.CreateWidget<ScoreLabel>("Test", TTF); //TODO implemant Font
	score->SetPosition(Vector2f(windowSize.x - 200.0f, 10));
	score->SetCharacterSize(25);
	score->SetZOrder(1);

	//new Timer<Seconds>([&]() {IncrementCombo(); }, seconds(5), true, true);
	Label* _levelDifficulty = M_HUD.CreateWidget<Label>(difficulty, Screen, "Test", TTF); //TODO implemant Font
	_levelDifficulty->SetPosition(Vector2f(10.0f, 10.0f));
	_levelDifficulty->SetCharacterSize(25);
	_levelDifficulty->SetZOrder(2);

	Label* _levelName = M_HUD.CreateWidget<Label>(trackInfo->title, Screen, "Test", TTF); //TODO implemant Font
	_levelName->SetPosition(Vector2f(350.0f, 10.0f));
	_levelName->SetCharacterSize(25);
	_levelName->SetZOrder(3);

	M_HUD.AddToViewport(score);
	M_HUD.AddToViewport(_levelDifficulty);
	M_HUD.AddToViewport(_levelName);
}

void BeatMapLevel::InitNoteTriggerAndSpawner()
{
	for (u_int _i = 0; _i < 4; _i++)
	{
		/*Note* _note = Level::SpawnActor(Note(NoteType(_i)));

		_note->SetPosition(Vector2f(400.0f + 120.0f * _i, 0));*/
		triggers[NoteType(_i)] = Level::SpawnActor(NoteDetector(NoteType(_i)));
		triggers[NoteType(_i)]->SetPosition(Vector2f(GetWindowSize().x / 3 + 120.0f * _i, 700));
		triggers[NoteType(_i)]->SetOriginAtMiddle();

		noteSpawners[NoteType(_i)] = Level::SpawnActor(NoteSpawner(NoteType(_i), triggers[NoteType(_i)]));
		noteSpawners[NoteType(_i)]->SetPosition(Vector2f(GetWindowSize().x / 3 + 120.0f * _i, 0));
	}
}

void BeatMapLevel::IncrementCombo()
{

	Color _finalColor = Color(GetRandomNumberInRange(0, 255),
		GetRandomNumberInRange(0, 255),
		GetRandomNumberInRange(0, 255));

	score->AddScore(GetRandomNumberInRange(10, 250)); // TODO REMOVE

	comboData->operator++();
	comboData->label->SetFillColor(_finalColor);
	comboData->label->SetCharacterSize(20);
	comboData->label->SetPosition(Vector2f(GetRandomNumberInRange(10.0f, windowSize.x * 0.1f), GetRandomNumberInRange(35.0f, windowSize.y - 35.0f)));
	comboData->label->SetLifeSpan(GetRandomNumberInRange(1.0f, 3.0f));
	comboData->label->SetRotation(radians(GetRandomNumberInRange(-(priv::pi / 4.0f), (priv::pi / 4.0f))));
}
