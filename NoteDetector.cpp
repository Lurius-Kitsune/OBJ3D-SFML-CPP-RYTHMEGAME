#include "NoteDetector.h"

NoteDetector::NoteDetector(const NoteType _type)
	: SquareActor(100.0f, "ArrowCowDetector")
{
	type = _type;
	M_TEXTURE.SetTextureRect(GetMesh()->GetShape()->GetDrawable(), IntRect(Vector2i(702 * type, 0), Vector2i(702, 702)));
	SetOriginAtMiddle();
}

NoteDetector::NoteDetector(const NoteDetector& _other)
	: SquareActor(_other)
{
	type = _other.type;
	M_TEXTURE.SetTextureRect(GetMesh()->GetShape()->GetDrawable(), IntRect(Vector2i(702 * type, 0), Vector2i(702, 702)));
	SetOriginAtMiddle();
}
