#include "BeatMapLevel.h"
#include "GameManager.h"
#include "TimerManager.h"
#include "MeshActor.h"
#include "RectangleActor.h"
#include "CameraManager.h"
#include "HUD.h"

using namespace Camera;
using namespace UI;

BeatMapLevel::BeatMapLevel(const string& _name, const string& _difficulty)
{
	name = _name;
	difficulty = _difficulty;
	windowSize = M_GAME.GetCurrent()->GetWindowSize();

	M_CAMERA.CreateCamera<CameraActor>(FloatRect({}, CAST(Vector2f, M_GAME.GetCurrent()->GetWindowSize())), "DefaultCamera");

	MeshActor* _background = SpawnActor(MeshActor(RectangleShapeData(CAST(Vector2f, windowSize), "background"))); //TODO implemant Font
	_background->SetFillColor(Color(255, 255, 255, 100));
	_background->SetFillColor(Color(255, 255, 255, 100));
	RectangleActor* _layerDark = SpawnActor(RectangleActor(RectangleShapeData(Vector2f(windowSize.x * 1.0f, 60.0f)))); //TODO implemant Font
	_layerDark->SetFillColor(Color(0, 0, 0, 50));

	RectangleActor* _separation = SpawnActor(RectangleActor(RectangleShapeData(Vector2f(windowSize.x * 1.0f, 5.0f)))); //TODO implemant Font
	_separation->SetFillColor(Color(255, 255, 255, 150));
	_separation->SetPosition(Vector2f(0.0f, 60.0f));

	//_layer->SetOutlineColor(Color(, 0, 0, 25));
	score = M_HUD.CreateWidget<ScoreLabel>("Test", TTF); //TODO implemant Font
	score->SetPosition(Vector2f(windowSize.x - 200.0f, 10)); 
	score->SetCharacterSize(25);
	score->SetZOrder(1);

	new Timer<Seconds>([&]() {SpawnCombo(); }, seconds(5), true, true);
	Label* _levelDifficulty = M_HUD.CreateWidget<Label>(difficulty, Screen, "Test", TTF); //TODO implemant Font
	_levelDifficulty->SetPosition(Vector2f(10.0f, 10.0f));
	_levelDifficulty->SetCharacterSize(25);
	_levelDifficulty->SetZOrder(2);

	Label* _levelName = M_HUD.CreateWidget<Label>(name, Screen, "Test", TTF); //TODO implemant Font
	_levelName->SetPosition(Vector2f(350.0f, 10.0f));
	_levelName->SetCharacterSize(25);
	_levelName->SetZOrder(3);

	M_HUD.AddToViewport(score);
	M_HUD.AddToViewport(_levelDifficulty);
	M_HUD.AddToViewport(_levelName);
}

void BeatMapLevel::Display()
{
	BaseDisplay();
}

void BeatMapLevel::BaseDisplay()
{
	
}

void BeatMapLevel::SpawnCombo(const u_int& _comboCout, const Color& _color)
{
	u_int _finalComboCount = _comboCout;
	if (_finalComboCount == 0)
	{
		_finalComboCount = GetRandomNumberInRange(0, 50);
	}
	Color _finalColor = _color;
	if (_finalColor == Color(0, 0, 0))
	{
		_finalColor = Color(GetRandomNumberInRange(0, 255),
			GetRandomNumberInRange(0, 255),
			GetRandomNumberInRange(0, 255));
	}
	Label* _combo = M_HUD.CreateWidget<Label>("X " + to_string(_finalComboCount), Screen, "Test", TTF);
	_combo->SetFillColor(_finalColor);
	_combo->SetCharacterSize(20);
	_combo->SetPosition(Vector2f(GetRandomNumberInRange(10.0f, windowSize.x * 0.1f), GetRandomNumberInRange(35.0f, windowSize.y - 35.0f)));
	_combo->SetLifeSpan(GetRandomNumberInRange(1.0f, 3.0f));
	_combo->SetRotation(radians(GetRandomNumberInRange(-(priv::pi / 4.0f), (priv::pi / 4.0f))));
}
