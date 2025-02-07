#include "BeatMapLevel.h"
#include "GameManager.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "MeshActor.h"
#include "RectangleActor.h"
#include "CameraManager.h"
#include "HUD.h"
#include "FileManager.h"
#include "DetectNoteComponent.h"

using namespace File;
using namespace Camera;
using namespace UI;
using namespace Input;

BeatMapLevel::BeatMapLevel(Track* _track, const string& _difficulty)
{
	score = nullptr;
	comboData = make_unique<ComboData>();
	comboData->label->SetOriginAtMiddle();
	triggers = map<NoteType, NoteDetector*>();
	track = _track;
	trackInfo = track->GetInfo();
	difficulty = _difficulty;
	finishedBackgroundAnimation = true;

	notes = queue<Note*>();
}

void BeatMapLevel::Start()
{
	Super::Start();
	windowSize = CAST(Vector2f, M_GAME.GetCurrent()->GetWindowSize());
	M_CAMERA.CreateCamera<CameraActor>(FloatRect({}, CAST(Vector2f, M_GAME.GetCurrent()->GetWindowSize())), "DefaultCamera");

	InitLevelAspect();
	InitTopBar();
	InitNoteTriggerAndSpawner();

	track->Start(difficulty);

	new Timer<Seconds>([&]() { UpdateTime(); }, milliseconds(1000), true, true);

	//new Timer([&]() {IncrementCombo(); }, Time(seconds(5.0f)), true, true);
}

bool BeatMapLevel::Update()
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
	return Super::Update();
}

void BeatMapLevel::Stop()
{
	Super::Stop();
	track->Stop();
}

void BeatMapLevel::ComputeNoteResult(const NoteResult& _noteResult, NoteDetector* _noteDetector)
{
	AddScore(_noteResult);
	if(_noteResult < NR_GOOD)
	{
		ResetCombo();
	}
	else
	{
		IncrementCombo();
	}

	string _text;
	Color _color;
	const Vector2f& _textPosition = _noteDetector->GetPosition() - Vector2f(0, _noteDetector->GetHitbox().size.y /2);
	if(_noteResult == NR_PERFECT)
	{
		_text = "PERFECT";
		_color = Color::Yellow;
	}
	else if(_noteResult == NR_GOOD)
	{
		_text = "GOOD";
		_color = Color::Green;
	}
	else if(_noteResult == NR_TOOEARLY)
	{
		_text = "TOO EARLY";
		_color = Color::Red;
	}
	else if(_noteResult == NR_TOOLATE)
	{
		_text = "TOO LATE";
		_color = Color::Red;
	}
	else if(_noteResult == NR_MISS)
	{
		_text = "MISS";
		_color = Color::Magenta;
	}


	Label* _noteResultLabel = M_HUD.CreateWidget<Label>(_text, Screen, "Test", TTF);
	_noteResultLabel->SetOriginAtMiddle();
	_noteResultLabel->SetPosition(_textPosition);
	_noteResultLabel->SetCharacterSize(25);
	_noteResultLabel->SetZOrder(3);
	_noteResultLabel->SetFillColor(_color);
	new Timer([_noteResultLabel]()
		{ 
			M_HUD.RemoveFromViewport(_noteResultLabel);
		}, seconds(1), true, false);

	M_HUD.AddToViewport(_noteResultLabel);

}

void BeatMapLevel::InitLevelAspect()
{
	background = Level::SpawnActor(MeshActor(RectangleShapeData(windowSize, "background"))); //TODO implemant Font
	background->SetOriginAtMiddle();
	background->SetPosition(windowSize / 2.0f);
	background->SetScale({ 1.2f, 2.0f });
	background->SetRotation(degrees(45));
	background->SetFillColor(Color(255, 255, 255, 100));



	RectangleActor* _separatorLeft = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	_separatorLeft->SetFillColor(Color(255, 255, 255, 150));
	_separatorLeft->SetPosition(Vector2f(330.0f, 60.0f));

	RectangleActor* _separatorMiddleLeft = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	_separatorMiddleLeft->SetFillColor(Color(255, 255, 255, 150));
	_separatorMiddleLeft->SetPosition(Vector2f(460.0f, 60.0f));

	RectangleActor* _separatorMiddle = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	_separatorMiddle->SetFillColor(Color(255, 255, 255, 150));
	_separatorMiddle->SetPosition(Vector2f(570.0f, 60.0f));

	RectangleActor* _separatorMiddleRight = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	_separatorMiddleRight->SetFillColor(Color(255, 255, 255, 150));
	_separatorMiddleRight->SetPosition(Vector2f(700.0f, 60.0f));

	RectangleActor* _separatorRight = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background"))); //TODO implemant Font
	_separatorRight->SetFillColor(Color(255, 255, 255, 150));
	_separatorRight->SetPosition(Vector2f(830.0f, 60.0f));

	RectangleActor* _separatorTopNote = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(_separatorRight->GetPosition().x - _separatorLeft->GetPosition().x, 5.0f), "Background"))); //TODO implemant Font
	_separatorTopNote->SetFillColor(Color(255, 255, 255, 150));
	_separatorTopNote->SetPosition(Vector2f(_separatorLeft->GetPosition().x, 630.0f));

	RectangleActor* _separatorBottomNote = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(_separatorRight->GetPosition().x - _separatorLeft->GetPosition().x, 5.0f), "Background"))); //TODO implemant Font
	_separatorBottomNote->SetFillColor(Color(255, 255, 255, 150));
	_separatorBottomNote->SetPosition(Vector2f(_separatorLeft->GetPosition().x, 760.0f));

	Label* _scoreText = M_HUD.CreateWidget<Label>("Score :", Screen, "Test", TTF);
	_scoreText->SetPosition(Vector2f((_separatorLeft->GetPosition().x - _scoreText->GetSize().x) / 2.0f, windowSize.y * 0.25));
	_scoreText->SetCharacterSize(25);
	_scoreText->SetZOrder(3);

	score = M_HUD.CreateWidget<ScoreLabel>("Test", TTF); //TODO implemant Font
	score->SetPosition(Vector2f((_separatorLeft->GetPosition().x - score->GetSize().x) / 2.0f, _scoreText->GetPosition().y + _scoreText->GetSize().y + 10.0f));
	score->SetCharacterSize(25);
	score->SetZOrder(1);

	Label* _rangText= M_HUD.CreateWidget<Label>("Rang :", Screen, "Test", TTF);
	_rangText->SetPosition(Vector2f((_separatorLeft->GetPosition().x - _rangText->GetSize().x) / 2.0f, windowSize.y * 0.6));
	_rangText->SetCharacterSize(25);
	_rangText->SetZOrder(3);

	Label* _rang = M_HUD.CreateWidget<Label>("F", Screen, "Test", TTF); //TODO Implement Rang
	_rang->SetPosition(Vector2f(windowSize.x * 0.1f, windowSize.y * 0.625));
	_rang->SetCharacterSize(100);
	_rang->SetZOrder(3);

	time = M_HUD.CreateWidget<Label>("0:00 / 0:00", Screen, "Faut Changer la font c'est de la merde pour le temps", TTF);
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
	RectangleActor* _layerDark = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(windowSize.x * 1.0f, 60.0f), "Background"))); //TODO implemant Font
	_layerDark->SetFillColor(Color(0, 0, 0, 50));

	RectangleActor* _separation = Level::SpawnActor(RectangleActor(RectangleShapeData(Vector2f(windowSize.x * 1.0f, 5.0f), "Background"))); //TODO implemant Font
	_separation->SetFillColor(Color(255, 255, 255, 150));
	_separation->SetPosition(Vector2f(0.0f, 60.0f));

	//new Timer<Seconds>([&]() {IncrementCombo(); }, seconds(5), true, true);
	Label* _levelDifficulty = M_HUD.CreateWidget<Label>("Difficulty: " + difficulty, Screen, "Test", TTF); //TODO implemant Font
	_levelDifficulty->SetPosition(Vector2f(10.0f, 15.0f));
	_levelDifficulty->SetCharacterSize(25);
	_levelDifficulty->SetZOrder(2);

	Label* _levelName = M_HUD.CreateWidget<Label>("Title:" +trackInfo.title, Screen, "Test", TTF); //TODO implemant Font
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
	ActionMap* _actMap = M_INPUT.CreateActionMap("NoteTrigger");
	for (u_int _i = 0; _i < 4; _i++)
	{
		/*Note* _note = Level::SpawnActor(Note(NoteType(_i)));

		_note->SetPosition(Vector2f(400.0f + 120.0f * _i, 0));*/
		NoteDetector* _noteDetect = Level::SpawnActor(NoteDetector(NoteType(_i)));
		triggers[NoteType(_i)] = _noteDetect;
		triggers[NoteType(_i)]->SetPosition(Vector2f(GetWindowSize().x / 3 + 120.0f * _i, 700));
		triggers[NoteType(_i)]->SetOriginAtMiddle();
		pair<string, Keyboard::Key> _key = GetKey(NoteType(_i));
		ActionData _actData = ActionData(KeyPressed, _key.second);
		_actMap->AddAction(_key.first, _actData, [_noteDetect]() {_noteDetect->GetDetectComponent()->DetectNote(); });

		noteSpawners[NoteType(_i)] = Level::SpawnActor(NoteSpawner(NoteType(_i), triggers[NoteType(_i)]));
		noteSpawners[NoteType(_i)]->SetPosition(Vector2f(GetWindowSize().x / 3 + 120.0f * _i, 0));
		
	}
	_actMap->Enable();
}

void BeatMapLevel::IncrementCombo()
{
	comboData->operator++();
	comboData->label->SetCharacterSize(25);
	comboData->label->SetPosition(Vector2f(windowSize.x * 0.125f, windowSize.y * 0.8));
	comboData->IncrementScale();
	comboData->label->SetRotation(degrees(GetRandomNumberInRange(-25, 25)));
	comboData->finishedAnimation = false;
	background->SetScale({ 1.8f, 2.5f });
	finishedBackgroundAnimation = false;
}

void BeatMapLevel::ResetCombo()
{
	comboData->SetCount(0);
}

void BeatMapLevel::AddScore(const NoteResult& _noteResult)
{
	score->AddScore(_noteResult);
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
	time->SetString(GetTime());
}

pair<string, Keyboard::Key> BeatMapLevel::GetKey(const NoteType& _noteType)
{
	switch (_noteType)
	{
	case NoteType::NT_UP:
		return make_pair("ArrowUp", Keyboard::Key::Z);
	case NoteType::NT_DOWN:
		return make_pair("ArrowDown", Keyboard::Key::S);
	case NoteType::NT_LEFT:
		return make_pair("ArrowLeft", Keyboard::Key::Q);
	case NoteType::NT_RIGHT:
		return make_pair("ArrowRight", Keyboard::Key::D);
	default:
		return make_pair("", Keyboard::Key::Unknown);
	}
}
