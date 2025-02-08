#pragma once
#include "Level.h"
#include "HUD.h"
#include "ScoreLabel.h"
#include "Track.h"
#include "NoteDetector.h"
#include "NoteSpawner.h"
#include "MeshActor.h"


struct ComboData
{
	LabelWidget* label;
	u_int count;
	bool finishedAnimation;
	Vector2f minScale;

	ComboData(Level* _level)
	{
		count = 0;
		label = _level->SpawnWidget<LabelWidget>("X " + to_string(count), "ComboCount");
		label->SetVisibility(Hidden);
		finishedAnimation = false;
		minScale = { 1.0f, 1.0f };
	}

	ComboData& operator++()
	{
		SetCount(++count);
		return *this;
	}

	ComboData operator++(const int _value)
	{
		SetCount(count++);
		return *this;
	}

	ComboData& operator--()
	{
		SetCount(--count);
		return *this;
	}

	ComboData operator--(const int _value)
	{
		SetCount(count--);
		return *this;
	}

	FORCEINLINE void SetCount(const u_int& _count)
	{
		label->SetVisibility(_count == 0 ? Hidden : Visible);
		count = _count;
		label->SetText("X " + to_string(count));
	}
	FORCEINLINE void IncrementScale()
	{
		label->Scale({ 0.1f, 0.1f });
		if (label->GetScale().x <= 3.0f || label->GetScale().y <= 3.0f)
		{
			label->SetScale({ 3.0f, 3.0f });
		}
	}

	void Animate()
	{
		if (!finishedAnimation)
		{
			const float _deltaTime = M_TIMER.GetDeltaTime().asSeconds();
			label->SetScale(label->GetScale() * 0.99f);

			if (label->GetScale().x <= minScale.x || label->GetScale().y <= minScale.y)
				finishedAnimation = true;
		}
	}
};

enum RankType
{
	F,
	B = 60,
	A = 70,
	S = 80,
	SS = 90,
	SSS = 100,
};

struct Rank
{
	vector<RankType> rankType = { RankType::F, RankType::B , RankType::A , RankType::S , RankType::SS , RankType::SSS };
	size_t size = rankType.size();

	string ComputeCurrentRank(ScoreLabel* _scoreLabel, const int _maxScore)
	{
		for (size_t _i = 0; _i < size - 1; _i++)
		{
			if ((_scoreLabel->GetScore() / _maxScore) * 100 > rankType[_i]
				&& (_scoreLabel->GetScore() / _maxScore) * 100 < rankType[_i + 1])
			{
				return GetRankString(rankType[_i]);
			}
		}
	}
	string GetRankString(RankType _rank)
	{
		switch (_rank)
		{
		case  RankType::F:
			return "F";
		case RankType::B:
			return "B";
		case  RankType::A:
			return "A";
		case RankType::S:
			return "S";
		case RankType::SS:
			return "SS";
		case RankType::SSS:
			return "SSS";
		default:
			break;
		}
	}

};

class BeatMapLevel : public Level
{
	ScoreLabel* score;
	MeshActor* background;
	LabelWidget* time;
	unique_ptr<ComboData> comboData;
	Vector2f windowSize;
	map<NoteType, NoteDetector*> triggers;
	map<NoteType, NoteSpawner*> noteSpawners;
	queue<Note*> notes;

	Track* track;
	TrackData trackInfo;
	string difficulty;
	
	bool finishedBackgroundAnimation;
	//float advancementPercent;

public:
	FORCEINLINE map<NoteType, NoteDetector*>& GetNoteDetectors()
	{
		return triggers;
	}
	FORCEINLINE NoteDetector* GetNoteDetector(const NoteType& _noteType)
	{
		return triggers[_noteType];
	}

	FORCEINLINE map<NoteType, NoteSpawner*>& GetNoteSpawners()
	{
		return noteSpawners;
	}
	FORCEINLINE NoteSpawner* GetNoteSpawner(const NoteType& _noteType)
	{
		return noteSpawners[_noteType];
	}

	FORCEINLINE void AddNoteToQueue(Note* _note)
	{
		notes.push(_note);
	}

	FORCEINLINE Note* GetNote()
	{
		if (notes.empty()) return nullptr;
		Note* _note = notes.front();
		notes.pop();
		LOG(Display, "Note poped");
		return _note;
	}


public:
	BeatMapLevel(Track* _track, const string& _difficulty);
public:

	virtual void Load() override;
	/*virtual bool Update() override;*/
	virtual void Unload() override;
	void ComputeNoteResult(const NoteResult& _noteResult, NoteDetector* _noteDetector);

private:
	void InitLevelAspect(); //TODO change name Methode
	void InitTopBar();
	void InitNoteTriggerAndSpawner();
	void AnimateBackground();
	string GetTime();
	void UpdateTime();

	void IncrementCombo();
	void ResetCombo();
	void AddScore(const NoteResult& _noteResult);

	pair<string, Keyboard::Key> GetKey(const NoteType& _noteType);

	virtual void InitLevel() override;
};

