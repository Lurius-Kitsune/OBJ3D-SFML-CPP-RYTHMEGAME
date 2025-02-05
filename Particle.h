#pragma once
#include "MeshActor.h"

struct Particle
{
	float lifeTime;
	Vector2f velocity;
};

class ParticleSystem : public Drawable, public Transformable
{
	VertexArray	vertices;

public:
	FORCEINLINE Vertex& GetVertexByIndex(const u_int& _index)
	{
		return vertices[_index];
	}

public:
	ParticleSystem(const u_int& _count, const PrimitiveType& _type = PrimitiveType::Points);

public:
	void draw(RenderTarget& target, RenderStates states) const override;
};

class ParticleActor : public MeshActor
{
	float maxLifeTime;
	vector<Particle> particles;
	ParticleSystem* system;

public:
	ParticleActor(const u_int& _count, const float _maxLifeTime = 1.0f,
				  const Color& _color = Color::White, const PrimitiveType& _type = PrimitiveType::Points);
	ParticleActor(const ParticleActor& _other);
	~ParticleActor();

	virtual void Tick(const float _deltaTime) override;

private:
	void Reset(Particle& _particle);
};