#pragma once
#include "Label.h"

using namespace UI;

class ScoreLabel : public Label
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
		text->SetString(ComputeScoreText());
	}

	FORCEINLINE void AddScore(const int _score)
	{
		score += _score;
		score = score >= pow(10, scoreMaxDigit) ? pow(10, scoreMaxDigit) - 1 : score;
		text->SetString(ComputeScoreText());
	}

public:
	ScoreLabel(const string& _path, const FontExtensionType& _fontType);
	ScoreLabel(const ScoreLabel& _other);

private:

	string ComputeScoreText();
};

