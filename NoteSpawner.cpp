#include "NoteSpawner.h"
#include "BeatMapLevel.h"
#include "LevelManager.h"

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
	BeatMapLevel* _level = Cast<BeatMapLevel>(M_LEVEL.GetCurrentLevel());
	Note* _note = _level->SpawnActor<Note>(*ref);
	_note->SetPosition(GetPosition());
	_level->AddNoteToQueue(_note);
}
