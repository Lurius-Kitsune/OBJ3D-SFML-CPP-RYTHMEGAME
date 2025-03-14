#pragma once
#include "Component.h"
#include "Bounds.h"

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
	Bounds impact;
	CollisionStep step;
	string channelName;
};

class CollisionComponent : public Component
{
	int status;
	string channelName;
	CollisionType type;						 
	map<string, CollisionType> responses;	
	map<Actor*, CollisionStep> othersStep;
	Bounds* bounds;

public:
	FORCEINLINE void AddResponses(const vector<pair<string, CollisionType>>& _responses)
	{
		for (pair<string, CollisionType> _pair : _responses)
		{
			responses.insert(_pair);
		}
	}
	FORCEINLINE void SetInformation(const string& _channelName, const int _status, const CollisionType& _type)
	{
		channelName = _channelName;
		type = _type;
		status = _status;
	}
	FORCEINLINE string GetChannelName() const
	{
		return channelName;
	}

	FORCEINLINE Bounds* GetBounds() const
	{
		return bounds;
	}

	FORCEINLINE virtual Component* Clone(Actor* _owner) const override
	{
		return new CollisionComponent(_owner, *this);
	}

public:
	CollisionComponent(Actor* _owner, const string& _channelName = "NONE", const int _status = IS_NONE, const CollisionType& _type = CT_NONE);
	CollisionComponent(Actor* _owner, const CollisionComponent& _other);
	~CollisionComponent();

protected:
	virtual void Construct() override;
	virtual void Deconstruct() override;
	virtual void Tick(const float _deltaTime) override;

private:
	void ComputeCollisions();
	CollisionStep ComputeStep(Actor* _other, const CollisionStep& _step);
	void UpdateBounds();
};