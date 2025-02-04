#pragma once
#include "Game.h"
#include "BeatMapLevel.h"
#include "MeshActor.h"
#include "Button.h"
#include "Canvas.h"

enum TrackInfo
{
	TI_TITLE,
	TI_ARTIST,
	TI_DURATION,
	
	TI_COUNT,
};

class SelectLevel : public Game
{
	using Iterator = unordered_map<Track*, Canvas*>::iterator;

	MeshActor* background;
	Vector2f windowSize;
	vector<Button*> allButtons;
	vector<Track*> allTracks;

	// Description
	unordered_map<Track*,Canvas*> allTracksCanvas;
	Iterator musicIterator; 


	// Right Info
	Canvas* description; 
	map<TrackInfo, Label*> infoLabel;
	u_int trackIndex;

public:
	SelectLevel();
	virtual ~SelectLevel();

public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;

private:
	// Init
	void InitSeparator();
	void InitLabel();
	void InitDescription();
	void InitRectangleTrackInfo(Track* _track);

	// SetLabel
	void SetDescription(Track* _track);
	void ChangeIterator(bool _isUp);

	// WHEEL
	void SelectTrack();
	void WheelCanvas();

	bool CrampIterator(Iterator& _current);
};
