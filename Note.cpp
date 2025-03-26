#include "Note.h"
#include "TextureManager.h"
#include "NoteDetector.h"

Note::Note(Level* _level, const NoteType _type, NoteDetector* _actor)
	: SquareActor(_level, 100.0f, "ArrowCow")
{
	type = _type;
	M_TEXTURE.SetTextureRect(GetMesh()->GetShape()->GetDrawable(), IntRect(Vector2i(702 * type, 0), Vector2i(702, 702)));
	mouvementComponent= CreateComponent<NoteMouvementComponent>(_actor);
	SetOriginAtMiddle();
}

Note::Note(const Note& _other)
	: SquareActor(_other)
{
	type = _other.type;
	M_TEXTURE.SetTextureRect(GetMesh()->GetShape()->GetDrawable(), IntRect(Vector2i(702 * type, 0), Vector2i(702, 702)));
	mouvementComponent = CreateComponent<NoteMouvementComponent>(*_other.mouvementComponent);
	SetOriginAtMiddle();
}

