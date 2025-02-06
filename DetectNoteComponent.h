#pragma once
#include "Component.h"
#include "Note.h"
class DetectNoteComponent : public Component
{
	NoteType detectType;

public:
	DetectNoteComponent(Actor* _owner, const NoteType _type);
	DetectNoteComponent(Actor* _owner, const DetectNoteComponent& _other);

public:
	virtual void Tick(const float _deltaTime) override;
	void DetectNote();

private:
	void GiveScore(const float _precision);
};

