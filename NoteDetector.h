#pragma once
#include "SquareActor.h"
#include "Note.h"
class NoteDetector : public SquareActor
{
	NoteType type;

public:
	NoteDetector() = default;
	NoteDetector(const NoteType _type);
	NoteDetector(const NoteDetector& _other);
};

