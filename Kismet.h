#pragma once
#include "Utilities.h"

class Actor;

struct HitInfo
{
	Vector2f position;
	float distance;
	Actor* actor;

	bool operator!=(const HitInfo& _hitInfo) const
	{
		return (actor != _hitInfo.actor && distance != _hitInfo.distance && position != _hitInfo.position);
	}
};

bool Raycast(const Vector2f& _origin, const Vector2f& _direction, const float _maxDistance,
			 HitInfo& _hitInfo, const vector<Actor*>& _ignoredActors = vector<Actor*>(),
			 const float _precision = 0.01f);

vector<HitInfo> RaycastAll(const Vector2f& _origin, const Vector2f& _direction, const float _maxDistance,
						   const vector<Shape*>& _ignoredShapes, const float _precision = 0.01f);
 
bool BoxCast(const FloatRect& _boxRect, HitInfo& _hitInfo, const vector<Actor*>& _ignoredActors);