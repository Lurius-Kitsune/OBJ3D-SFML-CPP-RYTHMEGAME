#pragma once
#include "Game.h"
#include "BeatMapLevel.h"
#include "MeshActor.h"
#include "Button.h"

class SelectLevel : public Game
{
	vector<Song*> allSounds;
	MeshActor* background;
	Vector2f windowSize;
	vector<Button*> allButtons;

public:
	SelectLevel();
	~SelectLevel();

private:
	void InitSeparator(Song* _song);
	void InitLabel(Song* _song);

public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;
};
