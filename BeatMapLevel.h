#pragma once
#include "Level.h"
#include "HUD.h"
#include "ScoreLabel.h"
#include "TimerManager.h"
#include "Track.h"
#include "NoteDetector.h"
#include "NoteSpawner.h"
#include "MeshActor.h"
#include "CanvasWidget.h"
#include "ProgressBarWidget.h"

struct ComboData
{
	LabelWidget* label;
	u_int count;
	bool finishedAnimation;
	Vector2f minScale;
	Timer<Seconds>* timer;

	ComboData(Level* _level)
	{
		count = 0;
		label = _level->GetGameMode()->GetHUD()->SpawnWidget<LabelWidget>("X " + to_string(count), "ComboCount");
		label->SetVisibility(Hidden);
		timer = new Timer<Seconds>([&]() {Animate(); }, seconds(0.0001f), false, true);
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
		timer->Start();
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
		else
		{
			timer->Pause();
			timer->Reset();
		}
	}
};

struct StatsData
{
	int perfectCount;
	int goodCount;
	int tooLateCount;
	int tooEarlyCount;
	int missCount;

	StatsData() = default;

	void Reset()
	{
		perfectCount = 0;
		goodCount = 0;
		tooLateCount = 0;
		tooEarlyCount = 0;
		missCount = 0;
	};
};

enum RankType
{
	RT_F,
	RT_B = 50,
	RT_A = 60,
	RT_S = 80,
	RT_SS = 90,
	RT_SSS = 100,
};

struct Rank
{
	LabelWidget* rankLabel;
	vector<RankType> rankType = { RankType::RT_F, RankType::RT_B , RankType::RT_A , RankType::RT_S , RankType::RT_SS , RankType::RT_SSS };
	size_t size = rankType.size();

	string ComputeCurrentRank(ScoreLabel* _scoreLabel, const int _maxScore)
	{
		const float& _percent = static_cast<float>(_scoreLabel->GetScore()  * 100) / _maxScore;
		for (size_t _i = 0; _i < size - 1; _i++)
		{
			if (_percent > rankType[_i] && _percent <= rankType[_i + 1])
			{
				return GetRankString(rankType[_i]);
			}
		}
		if (_percent >= rankType[size - 1]) return GetRankString(rankType[size - 1]);
		return "F";
	}
	string GetRankString(RankType _rank)
	{
		switch (_rank)
		{
		case  RankType::RT_F:
			return "F";
		case RankType::RT_B:
			return "B";
		case  RankType::RT_A:
			return "A";
		case RankType::RT_S:
			return "S";
		case RankType::RT_SS:
			return "SS";
		case RankType::RT_SSS:
			return "SSS";
		default:
			return "?";
			break;
		}
	}

};

enum ECanvasUI
{
	CUI_Game,
	CUI_Result,
};
class BeatMapLevel : public Level
{
	ScoreLabel* score;
	MeshActor* background;
	LabelWidget* time;
	unique_ptr<ComboData> comboData;
	unique_ptr<Rank> rank;
	Vector2f windowSize;
	map<NoteType, NoteDetector*> triggers;
	map<NoteType, NoteSpawner*> noteSpawners;
	queue<Note*> notes;

	Track* track;
	TrackData trackInfo;
	string difficulty;
	unique_ptr<StatsData> stats;
	
	ProgressBarWidget* progressBar;

	bool finishedBackgroundAnimation;
	Timer<Seconds>* updateTimeTimer;
	int timeElapsed;
	map<ECanvasUI, CanvasWidget*> allCanvas;
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

	FORCEINLINE bool IsDead()const
	{
		return progressBar->GetCurrentValue() <= 0;
	}
public:
	BeatMapLevel(Track* _track, const string& _difficulty);
public:

	virtual void Load() override;
	/*virtual bool Update() override;*/
	virtual void Unload() override;
	void ComputeNoteResult(const NoteResult& _noteResult, NoteDetector* _noteDetector);

private:
	virtual void InitLevel() override;
	MeshActor* InitBackground();
	CanvasWidget* InitResultCanvas();

	void InitResultAspect(CanvasWidget* _canvas);

	CanvasWidget* InitGameCanvas();

	void InitLevelAspect(CanvasWidget* _canvas);
	void InitTopBar(CanvasWidget* _canvas);
	void InitNoteTriggerAndSpawner();

	void AnimateBackground();



	string GetTimeInString();
	void UpdateTime();

	void RemoveLife();
	void AddLife(const int _value = 1);

	void IncrementCombo();
	void ResetCombo();
	void AddScore(const NoteResult& _noteResult);

	pair<string, Keyboard::Key> GetKey(const NoteType& _noteType);

};

