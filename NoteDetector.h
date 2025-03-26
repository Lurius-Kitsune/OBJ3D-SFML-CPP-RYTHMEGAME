#pragma once
#include "SquareActor.h"
#include "Note.h"
#include "DetectNoteComponent.h"
class NoteDetector : public SquareActor
{
	NoteType type;
	DetectNoteComponent* detectComponent;

public:
	FORCEINLINE DetectNoteComponent* GetDetectComponent() const 
	{ 
		return detectComponent; 
	}
public:
	NoteDetector() = default;
	NoteDetector(Level* _level, const NoteType _type);
	NoteDetector(const NoteDetector& _other);
};

