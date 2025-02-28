#include "BeatMapLevel.h"
#include "LevelManager.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "MeshActor.h"
#include "RectangleActor.h"
#include "ImageWidget.h"
#include "ProgressBarWidget.h"
#include "CameraManager.h"
#include "FileManager.h"
#include "DetectNoteComponent.h"

using namespace File;
using namespace Camera;
using namespace UI;
using namespace Input;

BeatMapLevel::BeatMapLevel(Track* _track, const string& _difficulty)
	: Level ("BeatMapLevel")
{
	score = nullptr;
	comboData = make_unique<ComboData>(this);
	canvas = GetGameMode()->GetHUD()->SpawnWidget<CanvasWidget>("BeatMapLevel", Screen);
	canvas->AddChild(comboData->label);
	comboData->label->SetOriginAtMiddle();
	triggers = map<NoteType, NoteDetector*>();
	track = _track;
	trackInfo = track->GetInfo();
	difficulty = _difficulty;
	finishedBackgroundAnimation = true;
	timeElapsed = 0;
	notes = queue<Note*>();
}

void BeatMapLevel::Load()
{
	Super::Load();
	GetActorManager().AddActor(track);
	track->SetActive(true);
	updateTimeTimer->Reset();
	updateTimeTimer->Start();
	timeElapsed = 0;
}

void BeatMapLevel::Unload()
{
	Super::Unload();
	if (track)
	{
		track->Stop();
		track->SetActive(false);
	}
	track = nullptr;
	score->SetScore(0);
	comboData->SetCount(0);
	updateTimeTimer->Pause();
	//M_LEVEL.SetLevel("SelectLevel");
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
		progressBar->SetValue(progressBar->GetCurrentValue() - track->GetCurrentBeatMap()->GetMissDamage());
	}


	LabelWidget* _noteResultLabel = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>(_text, "NoteResultLabel");
	canvas->AddChild(_noteResultLabel);
	_noteResultLabel->SetFont("Pixel", TTF);
	_noteResultLabel->SetOriginAtMiddle();
	_noteResultLabel->SetPosition(_textPosition);
	_noteResultLabel->SetCharacterSize(25);
	_noteResultLabel->SetZOrder(3);
	_noteResultLabel->SetFillColor(_color);
	new Timer([_noteResultLabel, this]()
		{ 
			canvas->RemoveChild(_noteResultLabel);
			GetGameMode()->GetHUD()->RemoveFromViewport(_noteResultLabel);
		}, seconds(1), true, false);
	GetGameMode()->GetHUD()->AddToViewport(canvas);

}

void BeatMapLevel::InitLevelAspect()
{
	background = SpawnActor<MeshActor>(RectangleShapeData(windowSize, "Background"));
	background->SetOriginAtMiddle();
	background->SetPosition(windowSize / 2.0f);
	background->SetScale({ 2.0f, 2.0f });
	background->SetRotation(degrees(90));
	//background->SetFillColor(Color(255, 255, 255, 100));

	function<Vector2f(const int)> _lambdaPosition = [&](const int _i) {
		return Vector2f(windowSize.x / 3 + 120.0f * _i -  55.0f , 60.0f);
		};

	const Vector2f& _size = _lambdaPosition(4) - _lambdaPosition(0) + Vector2f(0.0f, windowSize.y - 60.0f);
	ImageWidget* _layerDark = SpawnActor<ImageWidget>(RectangleShapeData(_size, "Background"));
	canvas->AddChild(_layerDark);
	_layerDark->SetPosition(_lambdaPosition(0));
	_layerDark->SetFillColor(Color(0, 0, 0, 25));

	ImageWidget* _separatorLeft = SpawnActor<ImageWidget>(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background")); 
	canvas->AddChild(_separatorLeft);
	_separatorLeft->SetFillColor(Color(255, 255, 255, 150));
	_separatorLeft->SetPosition(_lambdaPosition(0));

	ImageWidget* _separatorMiddleLeft = SpawnActor<ImageWidget>(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background")); 
	canvas->AddChild(_separatorMiddleLeft);
	_separatorMiddleLeft->SetFillColor(Color(255, 255, 255, 150));
	_separatorMiddleLeft->SetPosition(_lambdaPosition(1));

	ImageWidget* _separatorMiddle = SpawnActor<ImageWidget>(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background")); 
	canvas->AddChild(_separatorMiddle);
	_separatorMiddle->SetFillColor(Color(255, 255, 255, 150));
	_separatorMiddle->SetPosition(_lambdaPosition(2));

	ImageWidget* _separatorMiddleRight = SpawnActor<ImageWidget>(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background")); 
	canvas->AddChild(_separatorMiddleRight);
	_separatorMiddleRight->SetFillColor(Color(255, 255, 255, 150));
	_separatorMiddleRight->SetPosition(_lambdaPosition(3));

	ImageWidget* _separatorRight = SpawnActor<ImageWidget>(RectangleShapeData(Vector2f(5.0f, windowSize.y - 60.0f), "Background")); 
	canvas->AddChild(_separatorRight);
	_separatorRight->SetFillColor(Color(255, 255, 255, 150));
	_separatorRight->SetPosition(_lambdaPosition(4));

	ImageWidget* _separatorTopNote = SpawnActor<ImageWidget>(RectangleShapeData(Vector2f(_separatorRight->GetPosition().x - _separatorLeft->GetPosition().x, 5.0f), "Background")); 
	canvas->AddChild(_separatorTopNote);
	_separatorTopNote->SetFillColor(Color(255, 255, 255, 150));
	_separatorTopNote->SetPosition(Vector2f(_separatorLeft->GetPosition().x, 430.0f));

	ImageWidget* _separatorBottomNote = SpawnActor<ImageWidget>(RectangleShapeData(Vector2f(_separatorRight->GetPosition().x - _separatorLeft->GetPosition().x, 5.0f), "Background")); 
	canvas->AddChild(_separatorBottomNote);
	_separatorBottomNote->SetFillColor(Color(255, 255, 255, 150));
	_separatorBottomNote->SetPosition(Vector2f(_separatorLeft->GetPosition().x, 560.0f));

	LabelWidget* _scoreText = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("Score :", "Score Text");
	canvas->AddChild(_scoreText);
	_scoreText->SetFont("Pixel", TTF);
	_scoreText->SetPosition(Vector2f((_separatorLeft->GetPosition().x - _scoreText->GetSize().x) / 2.0f, windowSize.y * 0.25));
	_scoreText->SetCharacterSize(25);
	_scoreText->SetZOrder(3);

	score = GetGameMode()->GetHUD()->SpawnWidget<ScoreLabel>("Score");
	canvas->AddChild(score);
	score->SetFont("Pixel", TTF);
	score->SetPosition(Vector2f((_separatorLeft->GetPosition().x - score->GetSize().x) / 2.0f, _scoreText->GetPosition().y + _scoreText->GetSize().y + 10.0f));
	score->SetCharacterSize(25);
	score->SetZOrder(1);

	LabelWidget* _rankText= GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("Rang :", "RankLabelInfo");
	canvas->AddChild(_rankText);
	_rankText->SetFont("Pixel", TTF);
	_rankText->SetPosition(Vector2f((_separatorLeft->GetPosition().x - _rankText->GetSize().x) / 2.0f, windowSize.y * 0.6));
	_rankText->SetCharacterSize(25);
	_rankText->SetZOrder(3);

	LabelWidget* _rang = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("F", "Rank"); //TODO Implement Rang
	canvas->AddChild(_rang);
	_rang->SetFont("Pixel", TTF);
	_rang->SetPosition(Vector2f(windowSize.x * 0.1f, windowSize.y * 0.625));
	_rang->SetCharacterSize(100);
	_rang->SetZOrder(3);

	time = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("0:00 / 0:00", "TimeLabel");
	canvas->AddChild(time);
	time->SetFont("Pixel", TTF);
	time->SetPosition(Vector2f((_separatorRight->GetPosition().x + (windowSize.x - _separatorRight->GetPosition().x) / 2.0f) - time->GetSize().x / 2.0f, windowSize.y * 0.8f));
	time->SetCharacterSize(25);
	time->SetZOrder(3);
}

void BeatMapLevel::InitTopBar()
{

	//_layer->SetOutlineColor(Color(, 0, 0, 25));
	ImageWidget* _layerDark = SpawnActor<ImageWidget>(RectangleShapeData(Vector2f(windowSize.x * 1.0f, 60.0f), "Background")); 
	canvas->AddChild(_layerDark);
	_layerDark->SetFillColor(Color(0, 0, 0, 75));

	ImageWidget* _separation = SpawnActor<ImageWidget>(RectangleShapeData(Vector2f(windowSize.x * 1.0f, 5.0f), "Background")); 
	canvas->AddChild(_separation);
	_separation->SetFillColor(Color(255, 255, 255, 150));
	_separation->SetPosition(Vector2f(0.0f, 60.0f));

	LabelWidget* _levelDifficulty = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("Difficulty: " + difficulty, "DifficultyInfoLabel");
	canvas->AddChild(_levelDifficulty);
	_levelDifficulty->SetFont("Pixel", TTF);
	_levelDifficulty->SetPosition(Vector2f(10.0f, 15.0f));
	_levelDifficulty->SetCharacterSize(25);
	_levelDifficulty->SetZOrder(2);

	LabelWidget* _levelName = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("Title:" +trackInfo.title, "TrackInfoLabel");
	canvas->AddChild(_levelName);
	_levelName->SetFont("Pixel", TTF);
	_levelName->SetPosition(Vector2f(((windowSize.x - _levelName->GetSize().x) / 2.0f), 15.0f));
	_levelName->SetCharacterSize(25);
	_levelName->SetZOrder(3);

	progressBar = GetGameMode()->GetHUD()->SpawnWidget<ProgressBarWidget>(PT_LEFT, RectangleShapeData(Vector2f(200.0f, 20.0f), ""), 100.0f, "Test",  Screen);
	canvas->AddChild(progressBar);
	progressBar->SetZOrder(3);
	progressBar->SetFillColor(Color(0, 255, 0, 255));
	progressBar->GetForeground()->SetTexture("lifeBar");
	progressBar->ChangeValue(100.0f);
	progressBar->SetTexture("White", PNG);
	progressBar->SetFillColor(Color(255, 0, 0, 100));
	progressBar->SetPosition(_layerDark->GetSize() - Vector2f(210.0f, 30.0f));
}

void BeatMapLevel::InitNoteTriggerAndSpawner()
{
	ActionMap* _actMap = GetGameMode()->GetPlayerController()->GetInputManager().CreateActionMap("NoteTrigger");
	for (u_int _i = 0; _i < 4; _i++)
	{
		/*Note* _note = Level::SpawnActor(Note(NoteType(_i)));

		_note->SetPosition(Vector2f(400.0f + 120.0f * _i, 0));*/
		NoteDetector* _noteDetect = SpawnActor<NoteDetector>(NoteType(_i));
		triggers[NoteType(_i)] = _noteDetect;
		triggers[NoteType(_i)]->SetPosition(Vector2f(windowSize.x / 3 + 120.0f * _i, 500));
		triggers[NoteType(_i)]->SetOriginAtMiddle();
		pair<string, Keyboard::Key> _key = GetKey(NoteType(_i));
		ActionData _actData = ActionData(KeyPressed, _key.second);
		_actMap->AddAction(_key.first, _actData, [_noteDetect]() {_noteDetect->GetDetectComponent()->DetectNote(); });

		noteSpawners[NoteType(_i)] = SpawnActor<NoteSpawner>(NoteType(_i), triggers[NoteType(_i)]);
		noteSpawners[NoteType(_i)]->SetPosition(Vector2f(windowSize.x / 3 + 120.0f * _i, 0));
		
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



string BeatMapLevel::GetTimeInString()
{
	string _timeString;
	timeElapsed++;
	int _minute = timeElapsed / 60;
	_timeString += to_string(_minute);

	_timeString += ":";

	if (timeElapsed < 10)
	{
		_timeString += "0";
	}
	_timeString += to_string(timeElapsed - (_minute * 60));

	return _timeString + " / " + track->GetDurationAsString();
}

void BeatMapLevel::UpdateTime()
{
	time->SetText(GetTimeInString());
	if (!track) return;
	if (timeElapsed >= track->GetDuration().asSeconds())
	{
		track->Stop();
		track->SetActive(false);
		M_LEVEL.SetLevel("SelectLevel");
	}
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

void BeatMapLevel::InitLevel()
{
	Super::InitLevel();
	windowSize = GetWindowSize();
	//cameraManager.<CameraActor>(FloatRect({}, CAST(Vector2f, windowSize)), "DefaultCamera");
	InitLevelAspect();
	InitTopBar();
	InitNoteTriggerAndSpawner();
	track->Start(difficulty);
	GetGameMode()->GetHUD()->AddToViewport(canvas);
	updateTimeTimer = new Timer<Seconds>([&]() 
		{ 
			UpdateTime(); 
			background->Rotate(degrees(M_TIMER.GetDeltaTime().asSeconds() * 10));
			AnimateBackground();
		}, milliseconds(1000), true, true);
}
