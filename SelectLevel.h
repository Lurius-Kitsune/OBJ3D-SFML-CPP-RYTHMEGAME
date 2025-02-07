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
	using Iterator = unordered_map<Track*, CanvasWidget*>::iterator;

	MeshActor* background;
	Vector2f windowSize;
	vector<ButtonWidget*> allButtons;
	vector<Track*> allTracks;

	// Description
	unordered_map<Track*, CanvasWidget*> allTracksCanvas;
	Iterator musicIterator; 


	// Right Info
	CanvasWidget* description;
	map<TrackInfo, LabelWidget*> infoLabel;
	u_int trackIndex;

public:
	SelectLevel();
	virtual ~SelectLevel();

private:
	// Init
	void InitSeparator();
	void InitLabel();
	void InitDescription();
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
