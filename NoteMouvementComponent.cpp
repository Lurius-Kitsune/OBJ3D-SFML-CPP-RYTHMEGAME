#include "NoteMouvementComponent.h"
#include "Note.h"
#include "BeatMapLevel.h"
#include "NoteDetector.h"

NoteMouvementComponent::NoteMouvementComponent(Actor* _owner, NoteDetector* _triggerNote, const float _speed)
	: Component(_owner)
{
	speed = _speed;
	triggerNote = _triggerNote;
	triggerRect = triggerNote->GetHitbox();
	isInteractable = true;
	isFollowingTarget = true;
	direction = Vector2f(0, 1.0f);
}

NoteMouvementComponent::NoteMouvementComponent(Actor* _owner, const NoteMouvementComponent& _other)
	: Component(_owner)
{
	speed = _other.speed;
	triggerNote = _other.triggerNote;
	triggerRect = _other.triggerRect;
	direction = _other.direction;
}

void NoteMouvementComponent::Tick(const float _deltaTime)
{
	Move(_deltaTime);
}

void NoteMouvementComponent::Move(const float _deltaTime)
{
	BeatMapLevel* _level = Cast<BeatMapLevel>(M_LEVEL.GetCurrentLevel());
	const FloatRect& _ownerRect = Cast<Note>(owner)->GetMesh()->GetShape()->GetDrawable()->getGlobalBounds();
	if (isFollowingTarget)
	{
		const Vector2f _direction = triggerNote->GetPosition() - owner->GetPosition();
		direction = _direction.normalized();
		if (triggerRect.contains(owner->GetPosition()))
		{
			isFollowingTarget = false;
		}
	}
	else if (isInteractable && !triggerRect.contains(owner->GetPosition()))
	{
		Note* _note = _level->GetNote();
		new Timer(bind(&Actor::Destroy, _note), seconds(1.0f), true);
		_level->ComputeNoteResult(NR_MISS, triggerNote);
		isInteractable = false;
	}
	owner->Move(direction* speed * _deltaTime * 400.0f);
}
