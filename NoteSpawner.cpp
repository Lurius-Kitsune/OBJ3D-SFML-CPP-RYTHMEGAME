#include "NoteSpawner.h"

NoteSpawner::NoteSpawner(const NoteType& _noteType, NoteDetector* _detector)
	: Spawner<Note>(new SubclassOf(Note(_noteType, _detector)))
{
	noteType = _noteType;
}

NoteSpawner::NoteSpawner(const NoteSpawner& _other)
	: Spawner<Note>(_other)
{
	noteType = _other.noteType;
}

void NoteSpawner::BeginPlay()
{
	// NOTHING
}

void NoteSpawner::Spawn()
{
	Note _note = ref->GetObject();
	_note.SetPosition(GetPosition());

	Level::SpawnActor<Note>(_note);
}
