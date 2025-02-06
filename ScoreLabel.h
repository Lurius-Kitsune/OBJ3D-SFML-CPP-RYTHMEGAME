#pragma once
#include "LabelWidget.h"

using namespace UI;

class ScoreLabel : public LabelWidget
{
	int score;
	u_int scoreMaxDigit;

public:
	FORCEINLINE int GetScore() const
	{
		return score;
	}

	FORCEINLINE void SetScore(const int _score)
	{
		score = _score >= pow(10, scoreMaxDigit) ? pow(10, scoreMaxDigit) - 1 : _score;
		SetText(ComputeScoreText());
	}

	FORCEINLINE void AddScore(const int _score)
	{
		score += _score;
		score = score >= pow(10, scoreMaxDigit) ? pow(10, scoreMaxDigit) - 1 : score;
		SetText(ComputeScoreText());
	}

public:
	ScoreLabel(const string& _name, const RenderType& _renderType = Screen,  const int _score = 0, const u_int _scoreMaxDigit = 7);
	ScoreLabel(const ScoreLabel& _other);

private:

	string ComputeScoreText();
};

