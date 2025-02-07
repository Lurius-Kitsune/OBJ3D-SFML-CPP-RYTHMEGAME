#pragma once
#include "Component.h"

class NoteDetector;

class NoteMouvementComponent : public Component
{
	float speed;
	NoteDetector* triggerNote;
	FloatRect triggerRect;
	bool isFollowingTarget;
	bool isInteractable;
	Vector2f direction;

public:
	FORCEINLINE NoteDetector* GetTriggerNote() const
	{
		return triggerNote;
	}

public:
	NoteMouvementComponent(Actor* _owner, NoteDetector* _triggerNote = nullptr,const float _speed = 1.0f);
	NoteMouvementComponent(Actor* _owner, const NoteMouvementComponent& _other);

	virtual ~NoteMouvementComponent() = default;

public:
	virtual void Tick(const float _deltaTime) override;

private:
	void Move(const float _deltaTime);

};

