#include "SelectLevel.h"
#include "CameraManager.h"
#include "TimerManager.h"
#include "GameManager.h"
#include "FileManager.h"
#include "HUD.h"
#include "MeshActor.h"
#include "ActorManager.h"
#include "Image.h"
#include "InputManager.h"
#include "AudioManager.h"

using namespace Camera;
using namespace UI;
using namespace File;

SelectLevel::SelectLevel()
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

void SelectLevel::InitLabel()
{
	Label* _label = M_HUD.CreateWidget<Label>("Select Level", Screen, "Test", TTF); //TODO implemant Font
	_label->SetCharacterSize(35);
	_label->SetZOrder(2);
	_label->SetPosition(Vector2f(windowSize.x * 0.05f, 10.0f));

	//TODO Replace with button
	Label* _play = M_HUD.CreateWidget<Label>("PLAY", Screen, "Test", TTF); //TODO implemant Font
	_play->SetCharacterSize(30);
	_play->SetZOrder(2);
	_play->SetPosition(Vector2f(windowSize.x * 0.875f, windowSize.y - 45.0f));

	M_HUD.AddToViewport(_label);
	M_HUD.AddToViewport(_play);
}

void SelectLevel::InitDescription()
{
	description = M_HUD.CreateWidget<Canvas>("Description", Screen);
	Label* _title = M_HUD.CreateWidget<Label>("TrackTitle", Screen, "Test", TTF); //TODO implemant Font
	_title->SetCharacterSize(50);
	_title->SetZOrder(2);
	_title->SetPosition(Vector2f(windowSize.x * 0.65f, windowSize.y * 0.2f));

	Label* _artist = M_HUD.CreateWidget<Label>("TrackTitle", Screen, "Test", TTF); //TODO implemant Font
	_artist->SetCharacterSize(25);
	_artist->SetZOrder(2);
	_artist->SetPosition(Vector2f(windowSize.x * 0.65f, windowSize.y * 0.3f));

	Label* _duration = M_HUD.CreateWidget<Label>("TrackDuration", Screen, "Test", TTF); //TODO implemant Font
	_duration->SetCharacterSize(20);
	_duration->SetZOrder(2);
	_duration->SetPosition(Vector2f(windowSize.x * 0.8f, windowSize.y * 0.4f));

	//TODO Dificulty
	Label* _easy = M_HUD.CreateWidget<Label>("TrackDifficulty", Screen, "Test", TTF); //TODO implemant Font
	_easy->SetCharacterSize(20);
	_easy->SetZOrder(2);
	_easy->SetFillColor(Color(50, 189, 22));
	_easy->SetPosition(Vector2f(windowSize.x * 0.65, windowSize.y * 0.5f));


	description->AddWidget(_title);
	infoLabel.insert(make_pair(TI_TITLE, _title));
	description->AddWidget(_artist);
	infoLabel.insert(make_pair(TI_ARTIST, _artist));
	description->AddWidget(_duration);
	infoLabel.insert(make_pair(TI_DURATION, _duration));
	description->AddWidget(_easy);

	M_HUD.AddToViewport(description);
}

void SelectLevel::InitRectangleTrackInfo(Track* _track)
{
	if (allTracksCanvas.contains(_track)) return;

	Canvas* _trackInfo = M_HUD.CreateWidget<Canvas>("TrackSelection", Screen);
	UI::Image* _background = M_HUD.CreateWidget<UI::Image>("background", RectangleShapeData(Vector2f(windowSize.x * 0.58f, 50.0f), "background"), World); //TODO implemant Font
	const Vector2f& _backgroundSize = _background->GetSize();
	_background->SetZOrder(0);

	Label* _title = M_HUD.CreateWidget<Label>(_track->GetTitle(), Screen, "Test", TTF); //TODO implemant Font
	_title->SetCharacterSize(20);
	_title->SetZOrder(2);
	_title->SetPosition(Vector2f(_backgroundSize.x * 0.01f, 0.0f));

	Label* _artist = M_HUD.CreateWidget<Label>(_track->GetArtist(), Screen, "Test", TTF); //TODO implemant Font
	_artist->SetCharacterSize(20);
	_artist->SetZOrder(2);
	_artist->SetPosition(Vector2f(_backgroundSize.x * 0.01f, _backgroundSize.y * 0.5f));

	Label* _duration = M_HUD.CreateWidget<Label>(_track->GetDurationAsString(), Screen, "Test", TTF); //TODO implemant Font
	_duration->SetCharacterSize(20);
	_duration->SetZOrder(2);
	_duration->SetPosition(Vector2f(_backgroundSize.x * 0.5f, _backgroundSize.y * 0.25f));

	_trackInfo->AddWidget(_background);
	_trackInfo->AddWidget(_title);
	_trackInfo->AddWidget(_artist);
	_trackInfo->AddWidget(_duration);

	_trackInfo->Hide();
	allTracksCanvas.insert(make_pair(_track, _trackInfo));
	
	M_HUD.AddToViewport(_trackInfo);
}

void SelectLevel::SetDescription(Track* _track)
{
	infoLabel[TI_TITLE]->SetString(_track->GetTitle());
	infoLabel[TI_ARTIST]->SetString(_track->GetArtist());
	infoLabel[TI_DURATION]->SetString(_track->GetDurationAsString());
}

void SelectLevel::ChangeIterator(bool _isUp)
{
	M_AUDIO.Stop();
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
	Canvas* _selectCanvas = (*musicIterator).second;
	_selectCanvas->Show();
	_selectCanvas->SetPosition(Vector2f(windowSize.x * 0.01f, 140.0f));
	_selectCanvas->UpdateWidgets();
	_selectCanvas->GetFirstWidgetOf<UI::Image>()->SetOutline(2.0f, Color(255, 255, 255));
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
		Canvas* _currentCanvas = (*_current).second;
		_currentCanvas->GetFirstWidgetOf<UI::Image>()->SetOutline(2.0f, Color(255, 255, 255, 0));
		_currentCanvas->SetPosition(Vector2f(windowSize.x * 0.01f, 70.0f * _index));
		_currentCanvas->UpdateWidgets();
		_currentCanvas->Show();
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

	allTracks = M_FILE.ReadFolder<Track>("Assets\\Tracks");
	Track* _track = allTracks[trackIndex];

	allButtons.push_back(new Button("Button", Screen, _track));

	InitSeparator();
	InitLabel();
	InitDescription();

	for (Track* _track : allTracks)
	{
		InitRectangleTrackInfo(_track);
	}

	musicIterator = allTracksCanvas.begin();


	M_ACTOR.BeginPlay();
	//M_INPUT.BindAction([&]() { ChangeIterator(true); }, Code::Z);
	//M_INPUT.BindAction([&]() { ChangeIterator(false); }, Code::S);
	(*musicIterator).first->PlayExtrait();
	WheelCanvas();
}

bool SelectLevel::Update()
{
	Super::Update();
	// Background
	background->Rotate(degrees(M_TIMER.GetDeltaTime().asSeconds() * 10));
	// Description
	SetDescription((*musicIterator).first);
	// Wheel
	

	return IsOver();
}

void SelectLevel::Stop()
{
	Super::Stop();


}