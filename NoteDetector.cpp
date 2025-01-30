#include "NoteDetector.h"

NoteDetector::NoteDetector(const NoteType _type)
	: SquareActor(100.0f, "")
{
	type = _type;
	SetOriginAtMiddle();
}

NoteDetector::NoteDetector(const NoteDetector& _other)
	: SquareActor(_other)
{
	type = _other.type;
	SetOriginAtMiddle();
}
