#include "EndGameLevel.h"
#include "MeshActor.h"
#include "ButtonWidget.h"
#include "LabelWidget.h"
#include "CanvasWidget.h"
#include "AudioManager.h"

using namespace Camera;
using namespace UI;
using namespace Input;

EndGameLevel::EndGameLevel(int _score, int _combo, float _accuracy)
	: Level("ResultLevel"), score(_score), combo(_combo), accuracy(_accuracy) 
{
}

EndGameLevel::~EndGameLevel() {}

void EndGameLevel::InitLevel()
{
	Super::InitLevel();
	windowSize = GetWindowSize();

	allCanvas.insert({ "ResultScreen", GetGameMode()->GetHUD()->SpawnWidget<CanvasWidget>("ResultScreen", Screen) });

	InitBackground();
	InitResultDisplay();
	InitButtons();

	GetGameMode()->GetHUD()->AddToViewport(allCanvas["ResultScreen"]);
}

void EndGameLevel::InitBackground()
{
	background = SpawnActor<MeshActor>(RectangleShapeData(windowSize, "result_background"));
	background->SetOriginAtMiddle();
	background->SetPosition(windowSize / 2.0f);
	background->SetScale({ 2.0f, 2.0f });
	background->SetRotation(degrees(45));
}

void EndGameLevel::InitResultDisplay()
{
	static int highScore = 0;
	bool isNewHighScore = score > highScore;
	if (isNewHighScore) {
		highScore = score;
	}

	// Rank
	LabelWidget* _rankLabel = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>(GetRank(), "RankLabel");
	_rankLabel->SetFont("Pixel", TTF);
	_rankLabel->SetCharacterSize(100);
	_rankLabel->SetZOrder(2);
	_rankLabel->SetPosition(Vector2f(windowSize.x * 0.1f, windowSize.y * 0.2f));
	allCanvas["ResultScreen"]->AddChild(_rankLabel);

	// Score
	LabelWidget* _score = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("Score: " + std::to_string(score), "ScoreLabel");
	_score->SetFont("Pixel", TTF);
	_score->SetCharacterSize(40);
	_score->SetZOrder(2);
	_score->SetPosition(Vector2f(windowSize.x * 0.1f, windowSize.y * 0.4f));
	allCanvas["ResultScreen"]->AddChild(_score);

	// High Score Label
	if (isNewHighScore) {
		LabelWidget* _highScoreLabel = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("New High Score!", "HighScoreLabel");
		_highScoreLabel->SetFont("Pixel", TTF);
		_highScoreLabel->SetCharacterSize(40);
		_highScoreLabel->SetZOrder(2);
		_highScoreLabel->SetPosition(Vector2f(windowSize.x * 0.1f, windowSize.y * 0.45f));
		allCanvas["ResultScreen"]->AddChild(_highScoreLabel);
	}

	// Combo
	LabelWidget* _combo = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("Combo: " + std::to_string(combo), "ComboLabel");
	_combo->SetFont("Pixel", TTF);
	_combo->SetCharacterSize(40);
	_combo->SetZOrder(2);
	_combo->SetPosition(Vector2f(windowSize.x * 0.1f, windowSize.y * 0.5f));
	allCanvas["ResultScreen"]->AddChild(_combo);

	// Accuracy
	LabelWidget* _accuracy = GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("Accuracy: " + std::to_string(static_cast<int>(accuracy * 100)) + "%", "AccuracyLabel");
	_accuracy->SetFont("Pixel", TTF);
	_accuracy->SetCharacterSize(40);
	_accuracy->SetZOrder(2);
	_accuracy->SetPosition(Vector2f(windowSize.x * 0.1f, windowSize.y * 0.6f));
	allCanvas["ResultScreen"]->AddChild(_accuracy);
}

void EndGameLevel::InitButtons()
{
	// Retry Button
	ButtonWidget* _retry = GetGameMode()->GetHUD()->SpawnWidget<ButtonWidget>(RectangleShapeData(Vector2f(200.0f, 50.0f), "RetryButton"), "RetryButton", Screen);
	_retry->SetPosition(Vector2f(windowSize.x * 0.6f, windowSize.y * 0.5f));
	_retry->BindOnClickAction([&]() {
		M_LEVEL.SetLevel(new BeatMapLevel(lastTrack, "Medium"));
		});
	_retry->BindOnHoverAction([_retry]() {
		_retry->SetOutline(2.0f, Color(255, 255, 255));
		});
	_retry->BindOnUnhoverAction([_retry]() {
		_retry->SetOutline(0.0f, Color(255, 255, 255));
		});
	allCanvas["ResultScreen"]->AddChild(_retry);

	// Back to Menu
	ButtonWidget* _menu = GetGameMode()->GetHUD()->SpawnWidget<ButtonWidget>(RectangleShapeData(Vector2f(200.0f, 50.0f), "MenuButton"), "MenuButton", Screen);
	_menu->SetPosition(Vector2f(windowSize.x * 0.6f, windowSize.y * 0.6f));
	_menu->BindOnClickAction([&]() {
		M_LEVEL.SetLevel(new SelectLevel());
		});
	_menu->BindOnHoverAction([_menu]() {
		_menu->SetOutline(2.0f, Color(255, 255, 255));
		});
	_menu->BindOnUnhoverAction([_menu]() {
		_menu->SetOutline(0.0f, Color(255, 255, 255));
		});
	allCanvas["ResultScreen"]->AddChild(_menu);
}

string EndGameLevel::GetRank() const
{
	if (accuracy >= 1.0f) return "SS";
	if (accuracy >= 0.95f) return "S";
	if (accuracy >= 0.9f) return "A";
	if (accuracy >= 0.8f) return "B";
	if (accuracy >= 0.7f) return "C";
	return "D";
}