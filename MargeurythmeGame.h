#pragma once
#include "Game.h"
#include "NoteReceiver.h"
#include "GameInput.h"
#include "BeatMap.h"

class MargeurythmeGame : public Game
{

	// 4 button Input arrowLeft, arrowRight, arrowUp, arrowDown
	NoteReceiver* arrowLeft;
	BeatMap* beatMap;

	map<Code, GameInput::Input> inputMap;

	map<NoteType, MeshActor*> triggers;

public:
	FORCEINLINE map<NoteType, MeshActor*>& GetTriggers()
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

