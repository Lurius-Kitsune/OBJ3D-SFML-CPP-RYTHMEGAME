#pragma once
#include "BeatMapLevel.h"
#include "MeshActor.h"
#include "ButtonWidget.h"
#include "CanvasWidget.h"

enum TrackInfo
{
	TI_TITLE,
	TI_ARTIST,
	TI_DURATION,
	
	TI_COUNT,
};

class SelectLevel : public Level
{
	using Iterator = unordered_map<Track*, ImageWidget*>::iterator;

	MeshActor* background;
	Vector2f windowSize;
	vector<ButtonWidget*> allButtons;
	vector<Track*> allTracks;

	// Description
	unordered_map<Track*, ImageWidget*> allTracksCanvas;
	Iterator musicIterator; 

	map<string, CanvasWidget*> allCanvas;

	// Right Info
	CanvasWidget* description;
	map<TrackInfo, LabelWidget*> infoLabel;
	u_int trackIndex; //. TODO Remove

public:
	SelectLevel();
	virtual ~SelectLevel();

private:
	// Init
	void InitSeparator();
	void InitLabel();
	void InitDescription();
	void InitInput();
	void InitRectangleTrackInfo(Track* _track);

	// SetLabel
	void SetDescription(Track* _track);
	void ChangeIterator(bool _isUp);

	void SelectTrack();
	void WheelCanvas();

	bool CrampIterator(Iterator& _current);
public:
	virtual void Load() override;
	virtual void Unload() override;

protected:
	virtual void InitLevel() override;

	//virtual void Start() override;
	//virtual bool Update() override;
	//virtual void Stop() override;
};
