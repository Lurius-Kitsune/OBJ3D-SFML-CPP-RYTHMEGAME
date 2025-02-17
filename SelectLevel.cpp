#include "SelectLevel.h"
#include "CameraManager.h"
#include "TimerManager.h"
#include "FileManager.h"
#include "ActorManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "MeshActor.h"
#include "ButtonWidget.h"
#include "HUD.h"

using namespace Camera;
using namespace UI;
using namespace File;
using namespace Input;

SelectLevel::SelectLevel() : Level("SelectLevel") //Todo trouver un nom
{
	allTracks = {};
	background = nullptr;
	windowSize = Vector2f();
	trackIndex = 0;
	description = nullptr;
}

SelectLevel::~SelectLevel()
{
	for (Track* _song : allTracks)
	{
		delete _song;
	}
}

void SelectLevel::InitSeparator()
{
	ImageWidget* _topSeparation = SpawnActor<ImageWidget>(RectangleShapeData(Vector2f(windowSize.x, 5.0f), "background")); //TODO implemant Font
	//_topSeparation->SetFillColor(Color(255, 255, 255, 150));
	allCanvas["SelectLevel"]->AddChild(_topSeparation);
	_topSeparation->SetPosition(Vector2f(0.0f, 60.0f));

	ImageWidget* _levelSeparation = SpawnActor<ImageWidget>(RectangleShapeData(Vector2f(5.0f, windowSize.y - 120.0f), "background")); //TODO implemant Font
	//_levelSeparation->SetFillColor(Color(255, 255, 255, 150));
	allCanvas["SelectLevel"]->AddChild(_levelSeparation);
	_levelSeparation->SetPosition(Vector2f(windowSize.x * 0.6f, _topSeparation->GetPosition().y));

	ImageWidget* _bottomSeparation = SpawnActor<ImageWidget>(RectangleShapeData(Vector2f(windowSize.x, 5.0f), "background")); //TODO implemant Font
	//_bottomSeparation->SetFillColor(Color(255, 255, 255, 150));
	allCanvas["SelectLevel"]->AddChild(_bottomSeparation);
	_bottomSeparation->SetPosition(Vector2f(0.0f, windowSize.y - 60.0f));

}

void SelectLevel::InitLabel()
{
	LabelWidget* _label = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("Select Level", "SelectLevelLabel"); //TODO implemant Font
	allCanvas["SelectLevel"]->AddChild(_label);
	_label->SetFont("Pixel", TTF);
	_label->SetCharacterSize(35);
	_label->SetZOrder(2);
	_label->SetPosition(Vector2f(windowSize.x * 0.05f, 10.0f));

	ButtonWidget* _button = GetGameMode()->GetHUD()->SpawnWidget<ButtonWidget>(RectangleShapeData(Vector2f(100.0f, 50.0f), "background"), "PlayButton", Screen);
	allCanvas["SelectLevel"]->AddChild(_button);
	_button->SetPosition(Vector2f(windowSize.x * 0.875f, windowSize.y - 45.0f));
	_button->BindOnClickAction([&]()
		{
			M_LEVEL.SetLevel(new BeatMapLevel((*musicIterator).first, "Medium"));
		});
	_button->BindOnHoverAction([_button]()
		{
			_button->SetOutline(2.0f, Color(255, 255, 255, 255));
		});
	_button->BindOnUnhoverAction([_button]()
		{
			_button->SetOutline(0.0f, Color(255, 255, 255, 255));
		});
	LabelWidget* _play = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("PLAY", "PlayLabel"); //TODO implemant Font
	allCanvas["SelectLevel"]->AddChild(_play);
	_play->SetCharacterSize(30);
	_play->SetZOrder(2);
	_play->SetPosition(Vector2f(windowSize.x * 0.875f, windowSize.y - 45.0f));
	_play->SetFont("Pixel", TTF);

}

void SelectLevel::InitDescription()
{
	description = GetGameMode()->GetHUD()->SpawnWidget<CanvasWidget>("Description", Screen);
	LabelWidget* _title = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("TrackTitle","TrackTitleLabel"); //TODO implemant Font
	description->AddChild(_title);
	_title->SetFont("Pixel", TTF);
	_title->SetCharacterSize(50);
	_title->SetZOrder(2);
	_title->SetPosition(Vector2f(windowSize.x * 0.65f, windowSize.y * 0.2f));

	LabelWidget* _artist = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("TrackTitle","TrackTitleLabel2"); //TODO implemant Font
	description->AddChild(_artist);
	_artist->SetFont("Pixel", TTF);
	_artist->SetCharacterSize(25);
	_artist->SetZOrder(2);
	_artist->SetPosition(Vector2f(windowSize.x * 0.65f, windowSize.y * 0.3f));

	LabelWidget* _duration = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("TrackDuration", "TrackDurationLabel"); //TODO implemant Font
	description->AddChild(_duration);
	_duration->SetFont("Pixel", TTF);
	_duration->SetCharacterSize(20);
	_duration->SetZOrder(2);
	_duration->SetPosition(Vector2f(windowSize.x * 0.8f, windowSize.y * 0.4f));

	//TODO Dificulty
	LabelWidget* _easy = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("TrackDifficulty", "TrackDifficultyLabel"); //TODO implemant Font
	description->AddChild(_easy);
	_easy->SetFont("Pixel", TTF);
	_easy->SetCharacterSize(20);
	_easy->SetZOrder(2);
	_easy->SetFillColor(Color(50, 189, 22));
	_easy->SetPosition(Vector2f(windowSize.x * 0.65, windowSize.y * 0.5f));


	infoLabel.insert(make_pair(TI_TITLE, _title));
	infoLabel.insert(make_pair(TI_ARTIST, _artist));
	infoLabel.insert(make_pair(TI_DURATION, _duration));
	allCanvas["SelectLevel"]->AddChild(description);
	//M_HUD.AddToViewport(description);
}

void SelectLevel::InitInput()
{
	ActionMap* _actionMap = GetGameMode()->GetPlayerController()->GetInputManager().CreateActionMap("UI");
	Action* _upAction = new Action("GoUp", ActionData(KeyHold, Key::Z), [&]()
		{
			ChangeIterator(true);
		});
	_upAction->AddData(ActionData(KeyHold, Key::Up));
	Action* _downAction = new Action("GoDown", ActionData(KeyHold, Key::S), [&]()
		{
			ChangeIterator(false);
		});
	_downAction->AddData(ActionData(KeyHold, Key::Down));
	_actionMap->AddActions({ _upAction , _downAction });
	_actionMap->Enable();
}

void SelectLevel::InitRectangleTrackInfo(Track* _track)
{
	if (allTracksCanvas.contains(_track)) return;
	ImageWidget* _background = GetGameMode()->GetHUD()->SpawnWidget<ImageWidget>(RectangleShapeData(Vector2f(windowSize.x * 0.58f, 50.0f), "background"),"background", World); 
	const Vector2f& _backgroundSize = _background->GetSize();

	LabelWidget* _title = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>(_track->GetTitle(),"TitleLabel"); 
	_background->AddChild(_title, AT_KEEP_RELATIVE);
	_title->SetFont("Pixel", TTF);
	_title->SetCharacterSize(20);
	_title->SetZOrder(2);
	_title->SetPosition(Vector2f(_backgroundSize.x * 0.01f, 0.0f));

	LabelWidget* _artist = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>(_track->GetArtist(),"ArtistLabel"); 
	_background->AddChild(_artist, AT_KEEP_RELATIVE);
	_artist->SetFont("Pixel", TTF);
	_artist->SetCharacterSize(20);
	_artist->SetZOrder(2);
	_artist->SetPosition(Vector2f(_backgroundSize.x * 0.01f, _backgroundSize.y * 0.5f));

	LabelWidget* _duration = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>(_track->GetDurationAsString(), "DurationLabel"); 
	_background->AddChild(_duration, AT_KEEP_RELATIVE);
	_duration->SetFont("Pixel", TTF);
	_duration->SetCharacterSize(20);
	_duration->SetZOrder(2);
	_duration->SetPosition(Vector2f(_backgroundSize.x * 0.5f, _backgroundSize.y * 0.25f));


	_background->SetVisibility(VisibilityType::Visible);
	allTracksCanvas.insert(make_pair(_track, _background));
	_background->SetZOrder(0);
	allCanvas["SelectLevel"]->AddChild(_background);
}

void SelectLevel::SetDescription(Track* _track)
{
	infoLabel[TI_TITLE]->SetText(_track->GetTitle());
	infoLabel[TI_ARTIST]->SetText(_track->GetArtist());
	infoLabel[TI_DURATION]->SetText(_track->GetDurationAsString());
}

void SelectLevel::ChangeIterator(bool _isUp)
{
	//M_AUDIO.Stop();
	if (_isUp)
	{
		if (musicIterator == --allTracksCanvas.end())
		{
			musicIterator = allTracksCanvas.begin();
		}
		else
		{
			++musicIterator;
		}
	}
	else
	{
		if (musicIterator == allTracksCanvas.begin())
		{
			musicIterator = --allTracksCanvas.end() ;
		}
		else
		{
			--musicIterator;
		}
	}
	(*musicIterator).first->PlayExtrait();
	WheelCanvas();

}

void SelectLevel::SelectTrack()
{
	ImageWidget* _selectCanvas = (*musicIterator).second;
	_selectCanvas->SetVisibility(VisibilityType::Visible);
	_selectCanvas->SetPosition(Vector2f(windowSize.x * 0.01f, 140.0f));
	//_selectCanvas->GetFirstWidgetOf<UI::ImageWidget>()->SetOutline(2.0f, Color(255, 255, 255)); //TODO trouver solution
}

void SelectLevel::WheelCanvas()
{
	Iterator _current = musicIterator;
	SelectTrack();
	const u_int& _allTracksCanvasSize = static_cast<u_int>(allTracksCanvas.size());
	u_int _index = 1;
	for (u_int i = 0; i < _allTracksCanvasSize; ++i)
	{
		if (_current == allTracksCanvas.end())
		{
			_current = allTracksCanvas.begin();
		}
		if (_current != musicIterator)
		{
			ImageWidget* _currentCanvas = (*_current).second;
			_currentCanvas->SetPosition(Vector2f(windowSize.x * 0.01f, 140.0f + 70.0f * _index));
			_currentCanvas->SetVisibility(VisibilityType::Visible);
			++_index;
		}
		++_current;
	}
	SetDescription((*musicIterator).first);
}

bool SelectLevel::CrampIterator(Iterator& _current)
{
	if (_current == --allTracksCanvas.end())
	{
		_current = allTracksCanvas.begin();
		return true;
	}
	return false;
}

void SelectLevel::Load()
{
	Super::Load();

	////cameraManager.AddCamera(new CameraActor(FloatRect({ 0.0f, 0.0f }, windowSize), "DefaultCamera"));
	//background = SpawnActor<MeshActor>(RectangleShapeData(windowSize, "background")); //TODO implemant Font
	//background->SetOriginAtMiddle();
	//background->SetPosition(windowSize / 2.0f);
	//background->SetScale({ 1.2f, 2.0f });
	//background->SetRotation(degrees(45));
	////background->SetFillColor(Color(255, 255, 255, 100));
	//Track* _track = allTracks[trackIndex];

	////allButtons.push_back(new ButtonWidget("ButtonOkay", Screen));

	//musicIterator = allTracksCanvas.begin();
	////(*musicIterator).first->PlayExtrait();
	//WheelCanvas();
}

void SelectLevel::Unload()
{
	Super::Unload();
}

void SelectLevel::InitLevel()
{
	Super::InitLevel();
	windowSize = GetWindowSize();
	allCanvas.insert(make_pair("SelectLevel", GetGameMode()->GetHUD()->SpawnWidget<CanvasWidget>("SelectLevel", Screen)));
	background = SpawnActor<MeshActor>(RectangleShapeData(windowSize, "background")); //TODO implemant Font
	background->SetOriginAtMiddle();
	background->SetPosition(windowSize / 2.0f);
	background->SetScale({ 3.0f, 3.0f });
	background->SetRotation(degrees(45));
	//background->SetFillColor(Color(255, 255, 255, 100));

	vector<string> _trackFolder = M_FILE.ReadFolder("Assets\\Tracks");
	for (string _track : _trackFolder)
	{
		allTracks.push_back(SpawnActor<Track>(_track));
	}
	Track* _track = allTracks[trackIndex];

	//allButtons.push_back(new ButtonWidget("Button", Screen, _track));

	InitSeparator();
	InitLabel();
	InitDescription();
	if (ActionMap* _input = M_INPUT.GetActionMapByName("SelectLevel"))
	{
		_input->Enable();
	}
	else
	{
		InitInput();
	}

	for (Track* _track : allTracks)
	{
		InitRectangleTrackInfo(_track);
	}

	musicIterator = allTracksCanvas.begin();
	(*musicIterator).first->PlayExtrait();
	WheelCanvas();
	GetGameMode()->GetHUD()->AddToViewport(allCanvas["SelectLevel"]);
}

//bool SelectLevel::Update()
//{
//	Super::Update();
//	// Background
//	background->Rotate(degrees(M_TIMER.GetDeltaTime().asSeconds() * 10));
//	// Description
//	
//
//	return IsOver();
//}
