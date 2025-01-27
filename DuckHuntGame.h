#pragma once
#include "Game.h"
#include "MeshActor.h"
#include "MusicSample.h"
#include "Duck.h"
#include "Ball.h"

class DuckHuntGame : public Game
{
	MeshActor* background;
	MusicSample* music;

	// Ball
	Ball* ball;
	MeshActor* floor;
	MeshActor* platforme;

public:
	DuckHuntGame();

public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;

	Vector2f ComputeNormal(const FloatRect& _rect);
	float Lengh(const Vector2f& _vector);
};