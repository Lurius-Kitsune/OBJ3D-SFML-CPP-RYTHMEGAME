#pragma once
#include "Spawner.h"
#include "Note.h"
#include "NoteDetector.h"

class NoteSpawner : public Spawner<Note>
{
	NoteType noteType;

public:
	NoteSpawner(const NoteType& _noteType, NoteDetector* _detector);
	NoteSpawner(const NoteSpawner& _other);

public : 
	virtual void BeginPlay() override;
	virtual void Spawn() override;
};

