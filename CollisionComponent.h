#pragma once
#include "Component.h"

enum InteractStatus
{
	IS_NONE = 0,
	IS_QUERY = 1 << 0,
	IS_PHYSIC = 1 << 1,
	IS_ALL = IS_QUERY | IS_PHYSIC
};

enum CollisionType
{
	CT_NONE,
	CT_OVERLAP,
	CT_BLOCK
};

enum CollisionStep
{
	CS_ENTER,
	CS_UPDATE,
	CS_EXIT
};

struct CollisionData
{
	Actor* other;
	CollisionType response;
	FloatRect impactRect;
	CollisionStep step;
};

class CollisionComponent : public Component
{
	string channelName;
	int status;
	CollisionType type;						 
	map<string, CollisionType> responses;	
	map<Actor*, CollisionStep> othersStep;
	bool enable;

public:
	FORCEINLINE string GetChannelName() const
	{
		return channelName;
	}
	FORCEINLINE void AddResponses(const vector<pair<string, CollisionType>>& _responses)
	{
		for (pair<string, CollisionType> _pair : _responses)
		{
			responses.insert(_pair);
		}
	}
	FORCEINLINE void SetInformation(const string& _channelName, const int _status, const CollisionType& _type, const bool _enable = false)
	{
		channelName = _channelName;
		type = _type;
		status = _status;
		enable = _enable;
	}

public:
	CollisionComponent(Actor* _owner, const string& _channelName = "NONE", const int _status = IS_NONE, const CollisionType& _type = CT_NONE);
	CollisionComponent(Actor* _owner, const CollisionComponent& _other);

protected:
	virtual void Tick(const float _deltaTime) override;

private:
	void CheckCollision();
	CollisionStep ComputeOthersStep(Actor* _other, const CollisionStep& _step);
};