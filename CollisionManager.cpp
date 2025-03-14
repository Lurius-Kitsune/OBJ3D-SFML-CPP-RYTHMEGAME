#include "CollisionManager.h"
#include "Actor.h"

void CollisionManager::Collide(const CollisionData& _ownerData, const CollisionData& _otherData)
{
	if (_otherData.step == CS_ENTER)
	{
		_ownerData.other->CollisionEnter(_otherData);
		_otherData.other->CollisionEnter(_ownerData);
	}
	else if (_otherData.step == CS_UPDATE)
	{
		_ownerData.other->CollisionUpdate(_otherData);
		_otherData.other->CollisionUpdate(_ownerData);
	}
	else if (_otherData.step == CS_EXIT)
	{
		_ownerData.other->CollisionExit(_otherData);
		_otherData.other->CollisionExit(_ownerData);
	}

	AddCollisionPair(_ownerData.other, _otherData.other);
}
