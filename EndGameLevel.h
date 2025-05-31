#pragma once
#include "Level.h"
#include "CanvasWidget.h"
#include <string>
#include <map>

class MeshActor;

class EndGameLevel : public Level {
public:
	EndGameLevel(int _score, int _combo, float _accuracy);
	virtual ~EndGameLevel();

protected:
	void InitLevel() override;

private:
	void InitBackground();
	void InitResultDisplay();
	void InitButtons();
	string GetRank() const;

	int score;
	int combo;
	float accuracy;
	Vector2f windowSize;
	map<string, CanvasWidget*> allCanvas;
	MeshActor* background;
};