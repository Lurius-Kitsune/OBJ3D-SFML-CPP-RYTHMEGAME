#include "Note.h"
#include "TextureManager.h"


Note::Note(const NoteType _type, Actor* _actor)
	: SquareActor(50.0f, "ArrowCow")
{
	type = _type;
	M_TEXTURE.SetTextureRect(GetMesh()->GetShape()->GetDrawable(), IntRect(Vector2i(702 * type, 0), Vector2i(702, 702)));
	mouvementComponent= CreateComponent<NoteMouvementComponent>(_actor);
}

Note::Note(const Note& _other)
	: SquareActor(_other)
{
	type = _other.type;
	M_TEXTURE.SetTextureRect(GetMesh()->GetShape()->GetDrawable(), IntRect(Vector2i(702 * type, 0), Vector2i(702, 702)));
	mouvementComponent = CreateComponent<NoteMouvementComponent>(*_other.mouvementComponent);
}

