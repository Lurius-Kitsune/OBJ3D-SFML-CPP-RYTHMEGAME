#include "ScoreLabel.h"


ScoreLabel::ScoreLabel(const string& _name, const RenderType& _renderType, const int _score, const u_int _scoreMaxDigit)
	: LabelWidget("", _name, _renderType)
{
	score = _score;
	scoreMaxDigit = _scoreMaxDigit;
	SetText(ComputeScoreText());
}

ScoreLabel::ScoreLabel(const ScoreLabel& _other)
	: LabelWidget(_other)
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
