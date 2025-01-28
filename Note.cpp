#include "Note.h"
#include "TextureManager.h"
#include "NoteMouvementComponent.h"

Note::Note(const NoteType _type)
	: SquareActor(50.0f, "ArrowCow")
{
	type = _type;
	M_TEXTURE.SetTextureRect(GetMesh()->GetShape()->GetDrawable(), IntRect(Vector2i(702 * type, 0), Vector2i(702, 702)));
	CreateComponent<NoteMouvementComponent>();
}

Note::Note(const Note& _other)
	: SquareActor(_other)
{
	type = _other.type;
	M_TEXTURE.SetTextureRect(GetMesh()->GetShape()->GetDrawable(), IntRect(Vector2i(702 * type, 0), Vector2i(702, 702)));
}

