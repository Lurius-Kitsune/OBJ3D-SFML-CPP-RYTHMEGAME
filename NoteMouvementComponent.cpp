#include "NoteMouvementComponent.h"
#include "Note.h"
#include "BeatMapLevel.h"


NoteMouvementComponent::NoteMouvementComponent(Actor* _owner, Actor* _triggerNote, const float _speed)
	: Component(_owner)
{
	speed = _speed;
	triggerNote = _triggerNote;
	direction = Vector2f(0, 1.0f);
}

NoteMouvementComponent::NoteMouvementComponent(Actor* _owner, const NoteMouvementComponent& _other)
	: Component(_owner)
{
	speed = _other.speed;
	triggerNote = _other.triggerNote;
	direction = _other.direction;
}

void NoteMouvementComponent::Tick(const float _deltaTime)
{
	Move(_deltaTime);
}

void NoteMouvementComponent::Move(const float _deltaTime)
{
	if (triggerNote)
	{
		const Vector2f _direction = triggerNote->GetPosition() - owner->GetPosition();
		direction = _direction.normalized();
		const FloatRect& _ownerRect = Cast<Note>(owner)->GetMesh()->GetShape()->GetDrawable()->getGlobalBounds();
		if (_ownerRect.contains(triggerNote->GetPosition()))
		{
			//owner->SetLifeSpan(1.0f);
			triggerNote = nullptr;
			Cast<BeatMapLevel>(M_LEVEL.GetCurrentLevel())->IncrementCombo();
		}
	}
	owner->Move(direction* speed * _deltaTime * 400.0f);
}
