#include "BeatMapLevel.h"
#include "GameMode.h"
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
	: Level("BeatMapLevel", new GameMode())
{
	score = nullptr;
	comboData = make_unique<ComboData>();
	comboData->label->SetOriginAtMiddle();
	triggers = map<NoteType, NoteDetector*>();
	track = _track;
	trackInfo = track->GetInfo();
	difficulty = _difficulty;
	finishedBackgroundAnimation = true;
}

void BeatMapLevel::BeginPlay()
{
	Super::BeginPlay();
	windowSize = CAST(Vector2f, GetRenderWindow().getSize());
	//M_CAMERA.CreateCamera<CameraActor>(FloatRect({}, CAST(Vector2f, M_GAME.GetCurrent()->GetWindowSize())), "DefaultCamera");

	InitLevel();
}

void BeatMapLevel::Tick(const float _deltaTime)
{
	track->Update();
	comboData->Animate();
	background->Rotate(degrees(M_TIMER.GetDeltaTime().asSeconds() * 10));
	AnimateBackground();

	if (track->IsFinished())
	{
		track->Stop();
		score->SetScore(0);
		comboData->SetCount(0);
	}
	return Super::Tick(_deltaTime);
}

void BeatMapLevel::OnUnload()
{
	Super::OnUnload();
	track->Stop();
}

void BeatMapLevel::BeginDestroy()
{
	Super::BeginDestroy();
}

void BeatMapLevel::InitLevel()
{
	//Super::InitLevel();
	InitLevelAspect();
	InitTopBar();
	InitNoteTriggerAndSpawner();

	track->Start(difficulty);

	new Timer<Seconds>([&]() { UpdateTime(); }, milliseconds(1000), true, true);
}

void BeatMapLevel::InitLevelAspect()
{
	background = SpawnActor(MeshActor(RectangleShapeData(windowSize, "background"))); //TODO implemant Font
	background->SetOriginAtMiddle();
	background->SetPosition(windowSize / 2.0f);
	background->SetScale({ 1.2f, 2.0f });
	background->SetRotation(degrees(45));
	//background->SetFillColor(Color(255, 255, 255, 100));



	RectangleActor* _separatorLeft = SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	//_separatorLeft->SetFillColor(Color(255, 255, 255, 150));
	_separatorLeft->SetPosition(Vector2f(330.0f, 60.0f));

	RectangleActor* _separatorMiddleLeft = SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	//_separatorMiddleLeft->SetFillColor(Color(255, 255, 255, 150));
	_separatorMiddleLeft->SetPosition(Vector2f(460.0f, 60.0f));

	RectangleActor* _separatorMiddle = SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	//_separatorMiddle->SetFillColor(Color(255, 255, 255, 150));
	_separatorMiddle->SetPosition(Vector2f(570.0f, 60.0f));

	RectangleActor* _separatorMiddleRight = SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	//_separatorMiddleRight->SetFillColor(Color(255, 255, 255, 150));
	_separatorMiddleRight->SetPosition(Vector2f(700.0f, 60.0f));

	RectangleActor* _separatorRight = SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	//_separatorRight->SetFillColor(Color(255, 255, 255, 150));
	_separatorRight->SetPosition(Vector2f(830.0f, 60.0f));

	RectangleActor* _separatorTopNote = SpawnActor(RectangleActor(RectangleShapeData(Vector2f(_separatorRight->GetPosition().x - _separatorLeft->GetPosition().x, 5.0f), "Background"))); //TODO implemant Font
	//_separatorTopNote->SetFillColor(Color(255, 255, 255, 150));
	_separatorTopNote->SetPosition(Vector2f(_separatorLeft->GetPosition().x, 630.0f));

	RectangleActor* _separatorBottomNote = SpawnActor(RectangleActor(RectangleShapeData(Vector2f(_separatorRight->GetPosition().x - _separatorLeft->GetPosition().x, 5.0f), "Background"))); //TODO implemant Font
	//_separatorBottomNote->SetFillColor(Color(255, 255, 255, 150));
	_separatorBottomNote->SetPosition(Vector2f(_separatorLeft->GetPosition().x, 760.0f));

	LabelWidget* _scoreText = M_HUD.CreateWidget<LabelWidget>("Score :", "ScoreText", Screen);
	_scoreText->SetPosition(Vector2f((_separatorLeft->GetPosition().x - _scoreText->GetSize().x) / 2.0f, windowSize.y * 0.25));
	_scoreText->SetCharacterSize(25);
	_scoreText->SetZOrder(3);

	score = M_HUD.CreateWidget<ScoreLabel>("ScoreLabel");
	score->SetPosition(Vector2f((_separatorLeft->GetPosition().x - score->GetSize().x) / 2.0f, _scoreText->GetPosition().y + _scoreText->GetSize().y + 10.0f));
	score->SetCharacterSize(25);
	score->SetZOrder(1);

	LabelWidget* _rangText= M_HUD.CreateWidget<LabelWidget>("Rang :", "rankLabel", Screen);
	_rangText->SetPosition(Vector2f((_separatorLeft->GetPosition().x - _rangText->GetSize().x) / 2.0f, windowSize.y * 0.6));
	_rangText->SetCharacterSize(25);
	_rangText->SetZOrder(3);

	LabelWidget* _rang = M_HUD.CreateWidget<LabelWidget>("F", "RankIcon", Screen); //TODO Implement Rang
	_rang->SetPosition(Vector2f(windowSize.x * 0.1f, windowSize.y * 0.625));
	_rang->SetCharacterSize(100);
	_rang->SetZOrder(3);

	time = M_HUD.CreateWidget<LabelWidget>("0:00 / 0:00", "Timer", Screen); // TODO CHANGE FONT
	time->SetPosition(Vector2f((_separatorRight->GetPosition().x + (windowSize.x - _separatorRight->GetPosition().x) / 2.0f) - time->GetSize().x / 2.0f, windowSize.y * 0.8f));
	time->SetCharacterSize(25);
	time->SetZOrder(3);



	M_HUD.AddToViewport(score);
	M_HUD.AddToViewport(_scoreText);
	M_HUD.AddToViewport(_rangText);
	M_HUD.AddToViewport(_rang);
	M_HUD.AddToViewport(time);
}

void BeatMapLevel::InitTopBar()
{
	//_layer->SetOutlineColor(Color(, 0, 0, 25));
	RectangleActor* _layerDark = SpawnActor(RectangleActor(RectangleShapeData(Vector2f(windowSize.x * 1.0f, 60.0f), "Background"))); //TODO implemant Font
	//_layerDark->SetFillColor(Color(0, 0, 0, 50));

	RectangleActor* _separation = SpawnActor(RectangleActor(RectangleShapeData(Vector2f(windowSize.x * 1.0f, 5.0f), "Background"))); //TODO implemant Font
	//_separation->SetFillColor(Color(255, 255, 255, 150));
	_separation->SetPosition(Vector2f(0.0f, 60.0f));

	//new Timer<Seconds>([&]() {IncrementCombo(); }, seconds(5), true, true);
	LabelWidget* _levelDifficulty = M_HUD.CreateWidget<LabelWidget>("Difficulty: " + difficulty, "diffInfo", Screen);
	_levelDifficulty->SetPosition(Vector2f(10.0f, 15.0f));
	_levelDifficulty->SetCharacterSize(25);
	_levelDifficulty->SetZOrder(2);

	LabelWidget* _levelName = M_HUD.CreateWidget<LabelWidget>("Title:" +trackInfo.title, "TitleInfo", Screen);
	_levelName->SetPosition(Vector2f(((windowSize.x - _levelName->GetSize().x) / 2.0f), 15.0f));
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
		triggers[NoteType(_i)] = SpawnActor(NoteDetector(NoteType(_i)));
		triggers[NoteType(_i)]->SetPosition(Vector2f(GetWindowSize().x / 3 + 120.0f * _i, 700));
		triggers[NoteType(_i)]->SetOriginAtMiddle();

		noteSpawners[NoteType(_i)] = SpawnActor(NoteSpawner(NoteType(_i), triggers[NoteType(_i)]));
		noteSpawners[NoteType(_i)]->SetPosition(Vector2f(GetWindowSize().x / 3 + 120.0f * _i, 0));
	}
}

void BeatMapLevel::IncrementCombo()
{
	score->AddScore(GetRandomNumberInRange(10, 250)); // TODO REMOVE

	comboData->operator++();
	comboData->label->SetCharacterSize(25);
	comboData->label->SetPosition(Vector2f(windowSize.x * 0.125f, windowSize.y * 0.8));
	comboData->IncrementScale();
	comboData->label->SetRotation(degrees(GetRandomNumberInRange(-25, 25)));
	comboData->finishedAnimation = false;
	background->SetScale({ 1.8f, 2.5f });
	finishedBackgroundAnimation = false;
}

void BeatMapLevel::AnimateBackground()
{
	if (!finishedBackgroundAnimation)
	{
		const float _deltaTime = M_TIMER.GetDeltaTime().asSeconds() / 10;
		background->SetScale(background->GetScale() * (1.0f - _deltaTime));

		if (background->GetScale().x <= 1.2f || background->GetScale().y <= 2.0f)
			finishedBackgroundAnimation = true;
	}
}



string BeatMapLevel::GetTime()
{
	string _timeString;
	static int _time = 0;
	_time++;
	int _minute = _time / 60;
	_timeString += to_string(_minute);

	_timeString += ":";

	if (_time < 10)
	{
		_timeString += "0";
	}
	_timeString += to_string(_time - (_minute * 60));

	return _timeString + " / " + track->GetDurationAsString();
}

void BeatMapLevel::UpdateTime()
{
	time->SetText(GetTime());
}
