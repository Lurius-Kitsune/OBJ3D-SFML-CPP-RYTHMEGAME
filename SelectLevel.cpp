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

SelectLevel::SelectLevel() : Level("level") //Todo trouver un nom
{
	allTracks = {};
	background = nullptr;
	windowSize = Vector2f();
	trackIndex = 0;
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
	RectangleActor* _topSeparation = Level::SpawnActor<RectangleActor>(RectangleShapeData(Vector2f(windowSize.x, 5.0f), "background")); //TODO implemant Font
	//_topSeparation->SetFillColor(Color(255, 255, 255, 150));
	_topSeparation->SetPosition(Vector2f(0.0f, 60.0f));

	RectangleActor* _levelSeparation = Level::SpawnActor<RectangleActor>(RectangleShapeData(Vector2f(5.0f, windowSize.y - 120.0f), "background")); //TODO implemant Font
	//_levelSeparation->SetFillColor(Color(255, 255, 255, 150));
	_levelSeparation->SetPosition(Vector2f(windowSize.x * 0.6f, _topSeparation->GetPosition().y));

	RectangleActor* _bottomSeparation = Level::SpawnActor<RectangleActor>(RectangleShapeData(Vector2f(windowSize.x, 5.0f), "background")); //TODO implemant Font
	//_bottomSeparation->SetFillColor(Color(255, 255, 255, 150));
	_bottomSeparation->SetPosition(Vector2f(0.0f, windowSize.y - 60.0f));
}

void SelectLevel::InitLabel()
{
	LabelWidget* _label = SpawnWidget<LabelWidget>("Select Level", "SelectLevelLabel"); //TODO implemant Font
	_label->SetCharacterSize(35);
	_label->SetZOrder(2);
	_label->SetPosition(Vector2f(windowSize.x * 0.05f, 10.0f));

	//TODO Replace with button
	LabelWidget* _play = SpawnWidget<LabelWidget>("PLAY", "PlayLabel"); //TODO implemant Font
	_play->SetCharacterSize(30);
	_play->SetZOrder(2);
	_play->SetPosition(Vector2f(windowSize.x * 0.875f, windowSize.y - 45.0f));

	//M_HUD.AddToViewport(_label);
	//M_HUD.AddToViewport(_play);
}

void SelectLevel::InitDescription()
{
	description = SpawnWidget<CanvasWidget>("Description", Screen);
	LabelWidget* _title = SpawnWidget<LabelWidget>("TrackTitle","TrackTitleLabel"); //TODO implemant Font
	_title->SetCharacterSize(50);
	_title->SetZOrder(2);
	_title->SetPosition(Vector2f(windowSize.x * 0.65f, windowSize.y * 0.2f));

	LabelWidget* _artist = SpawnWidget<LabelWidget>("TrackTitle","TrackTitleLabel2"); //TODO implemant Font
	_artist->SetCharacterSize(25);
	_artist->SetZOrder(2);
	_artist->SetPosition(Vector2f(windowSize.x * 0.65f, windowSize.y * 0.3f));

	LabelWidget* _duration = SpawnWidget<LabelWidget>("TrackDuration", "TrackDurationLabel"); //TODO implemant Font
	_duration->SetCharacterSize(20);
	_duration->SetZOrder(2);
	_duration->SetPosition(Vector2f(windowSize.x * 0.8f, windowSize.y * 0.4f));

	//TODO Dificulty
	LabelWidget* _easy = SpawnWidget<LabelWidget>("TrackDifficulty", "TrackDifficultyLabel"); //TODO implemant Font
	_easy->SetCharacterSize(20);
	_easy->SetZOrder(2);
	_easy->SetFillColor(Color(50, 189, 22));
	_easy->SetPosition(Vector2f(windowSize.x * 0.65, windowSize.y * 0.5f));


	description->AddChild(_title);
	infoLabel.insert(make_pair(TI_TITLE, _title));
	description->AddChild(_artist);
	infoLabel.insert(make_pair(TI_ARTIST, _artist));
	description->AddChild(_duration);
	infoLabel.insert(make_pair(TI_DURATION, _duration));
	description->AddChild(_easy);

	//M_HUD.AddToViewport(description);
}

void SelectLevel::InitInput()
{
	ActionMap* _actionMap = M_INPUT.CreateActionMap("SelectLevel");
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

	CanvasWidget* _trackInfo = SpawnWidget<CanvasWidget>("TrackSelection", Screen);
	ImageWidget* _background = SpawnWidget<ImageWidget>(RectangleShapeData(Vector2f(windowSize.x * 0.58f, 50.0f), "background"),"background", World); //TODO implemant Font
	const Vector2f& _backgroundSize = _background->GetSize();
	_background->SetZOrder(0);

	LabelWidget* _title = SpawnWidget<LabelWidget>(_track->GetTitle(),"TitleLabel"); //TODO implemant Font
	_title->SetCharacterSize(20);
	_title->SetZOrder(2);
	_title->SetPosition(Vector2f(_backgroundSize.x * 0.01f, 0.0f));

	LabelWidget* _artist = SpawnWidget<LabelWidget>(_track->GetArtist(),"ArtistLabel"); //TODO implemant Font
	_artist->SetCharacterSize(20);
	_artist->SetZOrder(2);
	_artist->SetPosition(Vector2f(_backgroundSize.x * 0.01f, _backgroundSize.y * 0.5f));

	LabelWidget* _duration = SpawnWidget<LabelWidget>(_track->GetDurationAsString(), "DurationLabel"); //TODO implemant Font
	_duration->SetCharacterSize(20);
	_duration->SetZOrder(2);
	_duration->SetPosition(Vector2f(_backgroundSize.x * 0.5f, _backgroundSize.y * 0.25f));

	_trackInfo->AddChild(_background);
	_trackInfo->AddChild(_title);
	_trackInfo->AddChild(_artist);
	_trackInfo->AddChild(_duration);

	_trackInfo->SetVisibility(VisibilityType::Hidden);
	_trackInfo->SetPosition(Vector2f(windowSize.x * 0.01f, 70.0f * allTracksCanvas.size()));
	allTracksCanvas.insert(make_pair(_track, _trackInfo));
	//M_HUD.AddToViewport(_trackInfo);
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
	//WheelCanvas();

}

void SelectLevel::SelectTrack()
{
	CanvasWidget* _selectCanvas = (*musicIterator).second;
	_selectCanvas->SetVisibility(VisibilityType::Visible);
	_selectCanvas->SetPosition(Vector2f(windowSize.x * 0.01f, 140.0f));
	//_selectCanvas->UpdateWidgets();
	//_selectCanvas->GetFirstWidgetOf<UI::ImageWidget>()->SetOutline(2.0f, Color(255, 255, 255)); //TODO trouver solution
}

void SelectLevel::WheelCanvas()
{
	Iterator _current = musicIterator;
	SelectTrack();
	const u_int& _allTracksCanvasSize = CAST(u_int, allTracksCanvas.size()); 
	for (u_int _index = 1; _index < _allTracksCanvasSize + 1; _index++)
	{
		if(!CrampIterator(_current)) ++_current;
		if (_index == 2)
		{
			++_index;
			if (_current == musicIterator)
			{
				if (!CrampIterator(_current))
				{
					++_current;
					++_index;
				}
			}
			
		}
		CanvasWidget* _currentCanvas = (*_current).second;
		//_currentCanvas->GetFirstWidgetOf<UI::ImageWidget>()->SetOutline(2.0f, Color(255, 255, 255, 0));
		_currentCanvas->SetPosition(Vector2f(windowSize.x * 0.01f, 70.0f * _index));
		//_currentCanvas->UpdateWidgets();
		_currentCanvas->SetVisibility(VisibilityType::Visible);
	}
	
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
	////M_INPUT.BindAction([&]() { ChangeIterator(true); }, Code::Z);
	////M_INPUT.BindAction([&]() { ChangeIterator(false); }, Code::S);
	////(*musicIterator).first->PlayExtrait();
	//WheelCanvas();
}

void SelectLevel::Unload()
{
	Super::Unload();
	M_INPUT.GetActionMapByName("SelectLevel")->Disable();
}

void SelectLevel::InitLevel()
{
	windowSize = GetWindowSize();

	////M_CAMERA.CreateCamera<CameraActor>(FloatRect({ 0.0f, 0.0f }, windowSize), "DefaultCamera");

	background = Level::SpawnActor<MeshActor>(RectangleShapeData(windowSize, "background")); //TODO implemant Font
	background->SetOriginAtMiddle();
	background->SetPosition(windowSize / 2.0f);
	background->SetScale({ 1.2f, 2.0f });
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


	//M_INPUT.BindAction([&]() { ChangeIterator(true); }, Code::Z);
	//M_INPUT.BindAction([&]() { ChangeIterator(false); }, Code::S);
	(*musicIterator).first->PlayExtrait();
	//WheelCanvas();
}

//bool SelectLevel::Update()
//{
//	Super::Update();
//	// Background
//	background->Rotate(degrees(M_TIMER.GetDeltaTime().asSeconds() * 10));
//	// Description
//	SetDescription((*musicIterator).first);
//	// Wheel
//	
//
//	return IsOver();
//}
