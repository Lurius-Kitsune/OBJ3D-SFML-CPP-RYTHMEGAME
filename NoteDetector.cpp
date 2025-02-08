#include "NoteDetector.h"


NoteDetector::NoteDetector(Level* _level, const NoteType _type)
	: SquareActor(_level, 100.0f, "ArrowCowDetector")
{
	type = _type;
	M_TEXTURE.SetTextureRect(GetMesh()->GetShape()->GetDrawable(), IntRect(Vector2i(702 * type, 0), Vector2i(702, 702)));
	detectComponent = CreateComponent<DetectNoteComponent>(type);
}

NoteDetector::NoteDetector(const NoteDetector& _other)
	: SquareActor(_other)
{
	type = _other.type;
	M_TEXTURE.SetTextureRect(GetMesh()->GetShape()->GetDrawable(), IntRect(Vector2i(702 * type, 0), Vector2i(702, 702)));
	detectComponent = CreateComponent<DetectNoteComponent>(*_other.detectComponent);
}
