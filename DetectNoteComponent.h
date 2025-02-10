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
	virtual Component* Clone(Actor* _owner) const override;
private:
	void InterpretResult(const float _precision, const bool _isAfter);
};

