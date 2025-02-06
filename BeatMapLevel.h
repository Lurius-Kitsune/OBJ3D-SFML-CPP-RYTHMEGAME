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
	Label* label;
	u_int count;
	bool finishedAnimation;
	Vector2f minScale;

	ComboData()
	{
		count = 0;
		label = M_HUD.CreateWidget<Label>("X " + to_string(count), Screen, "Test", TTF);
		label->SetVisibility(Hidden);
		finishedAnimation = false;
		minScale = { 1.0f, 1.0f };
		M_HUD.AddToViewport(label);
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
		label->GetText()->SetString("X " + to_string(count));
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



class BeatMapLevel : public Game
{
	ScoreLabel* score;
	MeshActor* background;
	Label* time;
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
		return _note;
	}


public:
	BeatMapLevel(Track* _track, const string& _difficulty);
public:

	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;
	void IncrementCombo();
	void ResetCombo();
	void AddScore(const NoteResult& _noteResult);
	

private:
	void InitLevelAspect(); //TODO change name Methode
	void InitTopBar();
	void InitNoteTriggerAndSpawner();
	void AnimateBackground();
	string GetTime();
	void UpdateTime();

	pair<string, Keyboard::Key> GetKey(const NoteType& _noteType);
};

