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
	comboData->label->SetOriginAtMiddle();
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
	InitTopBar();
	InitNoteTriggerAndSpawner();

	track->Start(difficulty);

	//new Timer([&]() {IncrementCombo(); }, Time(seconds(5.0f)), true, true);
}

bool BeatMapLevel::Update()
{
	track->Update();
	comboData->Animate();

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
	MeshActor* _background = Level::SpawnActor(MeshActor(RectangleShapeData(CAST(Vector2f, windowSize), "Background"))); //TODO implemant Font
	_background->SetFillColor(Color(255, 255, 255, 100));
	_background->SetFillColor(Color(255, 255, 255, 100));
	RectangleActor* _layerDark = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(windowSize.x * 1.0f, 60.0f), "Background"))); //TODO implemant Font
	_layerDark->SetFillColor(Color(0, 0, 0, 50));

	RectangleActor* _separation = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(windowSize.x * 1.0f, 5.0f), "Background"))); //TODO implemant Font
	_separation->SetFillColor(Color(255, 255, 255, 150));
	_separation->SetPosition(Vector2f(0.0f, 60.0f));

	RectangleActor* _separation2 = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	_separation2->SetFillColor(Color(255, 255, 255, 150));
	_separation2->SetPosition(Vector2f(330.0f, 60.0f));

	RectangleActor* _separation3 = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	_separation3->SetFillColor(Color(255, 255, 255, 150));
	_separation3->SetPosition(Vector2f(460.0f, 60.0f));

	RectangleActor* _separation4 = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	_separation4->SetFillColor(Color(255, 255, 255, 150));
	_separation4->SetPosition(Vector2f(570.0f, 60.0f));

	RectangleActor* _separation5 = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	_separation5->SetFillColor(Color(255, 255, 255, 150));
	_separation5->SetPosition(Vector2f(700.0f, 60.0f));

	RectangleActor* _separation6 = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	_separation6->SetFillColor(Color(255, 255, 255, 150));
	_separation6->SetPosition(Vector2f(700.0f, 60.0f));

	RectangleActor* _separation7 = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	_separation7->SetFillColor(Color(255, 255, 255, 150));
	_separation7->SetPosition(Vector2f(830.0f, 60.0f));

	RectangleActor* _separation8 = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(_separation7->GetPosition().x - _separation2->GetPosition().x, 5.0f), "Background"))); //TODO implemant Font
	_separation8->SetFillColor(Color(255, 255, 255, 150));
	_separation8->SetPosition(Vector2f(_separation2->GetPosition().x, 630.0f));

	RectangleActor* _separation9 = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(_separation7->GetPosition().x - _separation2->GetPosition().x, 5.0f), "Background"))); //TODO implemant Font
	_separation9->SetFillColor(Color(255, 255, 255, 150));
	_separation9->SetPosition(Vector2f(_separation2->GetPosition().x, 760.0f));

	Label* _scoreText = M_HUD.CreateWidget<Label>("Score :", Screen, "Test", TTF);
	_scoreText->SetPosition(Vector2f(windowSize.x * 0.065f, windowSize.y * 0.25));
	_scoreText->SetCharacterSize(25);
	_scoreText->SetZOrder(3);

	score = M_HUD.CreateWidget<ScoreLabel>("Test", TTF); //TODO implemant Font
	score->SetPosition(Vector2f(windowSize.x * 0.052f, windowSize.y * 0.3));
	score->SetCharacterSize(25);
	score->SetZOrder(1);

	Label* _scorePercent = M_HUD.CreateWidget<Label>("(100%)", Screen, "Test", TTF); // TODO Imprlemant Percent
	_scorePercent->SetPosition(Vector2f(windowSize.x * 0.08f, windowSize.y * 0.35));
	_scorePercent->SetCharacterSize(20);
	_scorePercent->SetZOrder(3);

	Label* _rangText= M_HUD.CreateWidget<Label>("Rang :", Screen, "Test", TTF);
	_rangText->SetPosition(Vector2f(windowSize.x * 0.065f, windowSize.y * 0.6));
	_rangText->SetCharacterSize(25);
	_rangText->SetZOrder(3);

	Label* _rang = M_HUD.CreateWidget<Label>("F", Screen, "Test", TTF); //TODO Implement Rang
	_rang->SetPosition(Vector2f(windowSize.x * 0.07f, windowSize.y * 0.65));
	_rang->SetCharacterSize(100);
	_rang->SetZOrder(3);


	M_HUD.AddToViewport(score);
	M_HUD.AddToViewport(_scoreText);
	M_HUD.AddToViewport(_scorePercent);
	M_HUD.AddToViewport(_rangText);
	M_HUD.AddToViewport(_rang);
}

void BeatMapLevel::InitTopBar()
{
	//_layer->SetOutlineColor(Color(, 0, 0, 25));
	

	//new Timer<Seconds>([&]() {IncrementCombo(); }, seconds(5), true, true);
	Label* _levelDifficulty = M_HUD.CreateWidget<Label>(difficulty, Screen, "Test", TTF); //TODO implemant Font
	_levelDifficulty->SetPosition(Vector2f(10.0f, 10.0f));
	_levelDifficulty->SetCharacterSize(25);
	_levelDifficulty->SetZOrder(2);

	Label* _levelName = M_HUD.CreateWidget<Label>(trackInfo.title, Screen, "Test", TTF); //TODO implemant Font
	_levelName->SetPosition(Vector2f(350.0f, 10.0f));
	_levelName->SetCharacterSize(25);
	_levelName->SetZOrder(3);

	//ProgressBar* _progressBar = M_HUD.CreateWidget<ProgressBar>(PT_LEFT, RectangleShapeData(Vector2f(200.0f, 20.0f), ""), "Test", 100.0f, Screen); //TODO implemant Font
	//_progressBar->SetFillColor(Color(0, 255, 0, 255));
	//_progressBar->ChangeValue(50.0f);

	//M_HUD.AddToViewport(_progressBar);
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
	score->AddScore(GetRandomNumberInRange(10, 250)); // TODO REMOVE

	comboData->operator++();
	comboData->label->SetCharacterSize(25);
	comboData->label->SetPosition(Vector2f(windowSize.x * 0.1f, windowSize.y * 0.82));
	comboData->label->SetLifeSpan(GetRandomNumberInRange(1.0f, 3.0f));
	comboData->IncrementScale();
	comboData->label->SetRotation(degrees(GetRandomNumberInRange(-25, 25)));
	comboData->finishedAnimation = false;
}
