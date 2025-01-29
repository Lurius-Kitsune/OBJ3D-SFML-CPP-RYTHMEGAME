#include "ScoreLabel.h"

ScoreLabel::ScoreLabel(const string& _path, const FontExtensionType& _fontType)
	: Label("0", Screen, _path, _fontType)
{
	score = 0;
	scoreMaxDigit = 7;
	text->SetString(ComputeScoreText());
}

ScoreLabel::ScoreLabel(const ScoreLabel& _other)
	: Label(_other)
{
	score = _other.score;
	scoreMaxDigit = _other.scoreMaxDigit;
}


string ScoreLabel::ComputeScoreText()
{
	stringstream _ss;
	_ss << setw(scoreMaxDigit) << setfill('0') << score;

    return _ss.str();
}
