#pragma once
#include "MeshActor.h"

class Bird : public MeshActor
{


public:
	Bird() = default;
	Bird(const Bird& _other);

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
};