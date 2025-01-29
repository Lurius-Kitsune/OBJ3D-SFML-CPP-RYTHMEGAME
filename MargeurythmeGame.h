#pragma once
#include "Game.h"
#include "NoteDetector.h"
#include "GameInput.h"
#include "BeatMap.h"

class MargeurythmeGame : public Game
{

	BeatMap* beatMap;

	//map<Code, GameInput::Input> inputMap;

	map<NoteType, NoteDetector*> triggers;

public:
	FORCEINLINE map<NoteType, NoteDetector*>& GetNoteDetector()
	{
		return triggers;
	}

public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;

private:
	void InitInput();
};

