#pragma once
#include "Game.h"
#include "BeatMapLevel.h"
#include "MeshActor.h"
#include "Button.h"
#include "Canvas.h"

class SelectLevel : public Game
{
	vector<Track*> allTracks;
	MeshActor* background;
	Vector2f windowSize;
	vector<Button*> allButtons;
	vector<Canvas*> allTracksRectangle;
	u_int trackIndex;

public:
	SelectLevel();
	~SelectLevel();

private:
	void InitSeparator(Track* _track);
	void InitLabel(Track* _track);

	void InitRectangleTrackInfo(Track* _track);

public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;
};
