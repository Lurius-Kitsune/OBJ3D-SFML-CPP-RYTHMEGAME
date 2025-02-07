#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "ActorManager.h"
#include "MeshActor.h"

CollisionComponent::CollisionComponent(Actor* _owner, const string& _channelName, const int _status, const CollisionType& _type) : Component(_owner)
{
	channelName = _channelName;
	type = _type;
	status = _status;
	enable = false;
}

CollisionComponent::CollisionComponent(Actor* _owner, const CollisionComponent& _other) : Component(_owner)
{
	channelName = _other.channelName;
	type = _other.type;
	status = _other.status;
	responses = _other.responses;
	enable = _other.enable;
}


void CollisionComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	if (channelName != "NONE")
	{
		CheckCollision();
	}
}

void CollisionComponent::CheckCollision()
{
	if (!enable) return;

	if (!(status & IS_PHYSIC)) return;

	const set<CollisionComponent*>& _allComponent = M_COLLISION.GetAllCollisionComponents();
	const FloatRect& _ownerRect = Cast<MeshActor>(owner)->GetHitbox();

	for (CollisionComponent* _otherComponent : _allComponent)
	{
		if (_otherComponent == this) continue;
		if (M_COLLISION.ContainPair(owner, _otherComponent->owner)) continue;

		const string& _otherName = _otherComponent->GetChannelName();
		if (!responses.contains(_otherName)) continue;

		const CollisionType& _otherResponse = responses.at(_otherName);
		const CollisionType& _ownerResponse = _otherComponent->responses.at(channelName);
		if (_otherResponse == CT_NONE) continue;

		MeshActor* _other = Cast<MeshActor>(_otherComponent->owner);
		const FloatRect& _otherRect = _other->GetHitbox();
		if (const optional<FloatRect> _intersection = _ownerRect.findIntersection(_otherRect))
		{
			CollisionStep _step = ComputeOthersStep(_other, CS_ENTER);
			const CollisionData& _ownerData = { owner, _ownerResponse, *_intersection, _step };
			const CollisionData& _otherData = { _other, _otherResponse, *_intersection, _step };
			M_COLLISION.Collide(_ownerData, _otherData);
		}
		else
		{
			if (othersStep.contains(_otherComponent->owner))
			{
				CollisionStep _step = ComputeOthersStep(_other, CS_EXIT);
				const CollisionData& _ownerData = { owner, _ownerResponse, {}, _step };
				const CollisionData& _otherData = { _other, _otherResponse, {}, _step };
				M_COLLISION.Collide(_ownerData, _otherData);
				othersStep.erase(_other);
			}
		}
	}
}

CollisionStep CollisionComponent::ComputeOthersStep(Actor* _other, const CollisionStep& _step)
{
	if (othersStep.contains(_other) && othersStep[_other] == CS_ENTER || othersStep[_other] == CS_UPDATE)
	{
		othersStep[_other] = CS_UPDATE;
	}
	else
	{
		othersStep[_other] = _step;
	}
	return othersStep[_other];

}