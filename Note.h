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

class Note : public SquareActor
{
	NoteType type;
	NoteMouvementComponent* mouvementComponent;

public:
	Note() = default;
	Note(const NoteType _type);
	Note(const Note& _other);

};

