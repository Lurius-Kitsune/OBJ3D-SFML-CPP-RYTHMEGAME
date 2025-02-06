#pragma once
#include "CoreMinimal.h"
#include "SquareActor.h"
#include "NoteMouvementComponent.h"

enum NoteType
{
	NT_UP,
	NT_DOWN,
	NT_LEFT,
	NT_RIGHT,
	NT_TRIGGER,
	NT_LEFTCLICK,
	NT_RIGHTCLICK,

	NT_COUNT
};


enum NoteResult
{
	NR_MISS = 0,
	NR_TOOEARLY = 50,
	NR_GOOD = 100,
	NR_PERFECT = 250,
	NR_TOOLATE = 50,

	NR_COUNT
};

class Note : public SquareActor
{
	NoteType type;
	NoteMouvementComponent* mouvementComponent;


public:
	FORCEINLINE NoteType GetType() const
	{
		return type;
	}
public:
	Note() = default;
	Note(const NoteType _type, Actor* _actor = nullptr);
	Note(const Note& _other);

};

