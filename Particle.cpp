#include "Particle.h"

ParticleSystem::ParticleSystem(const u_int& _count, const PrimitiveType& _type)
{
	vertices = VertexArray(_type, _count);
}

void ParticleSystem::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = nullptr;
	target.draw(vertices, states);
}


ParticleActor::ParticleActor(const u_int& _count, const float _maxLifeTime, const Color& _color, const PrimitiveType& _type)
						   : MeshActor(VertexArrayData(_count, _type), "Particle")
{
	maxLifeTime = _maxLifeTime;
	particles = vector<Particle>(_count);
	system = new ParticleSystem(_count, _type);
}

ParticleActor::ParticleActor(const ParticleActor& _other) : MeshActor(_other)
{
	maxLifeTime = _other.maxLifeTime;
	particles = _other.particles;
	system = new ParticleSystem(*_other.system);
}

ParticleActor::~ParticleActor()
{
	delete system;
}

void ParticleActor::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	int _index = 0;
	for (Particle& _particle : particles)
	{
		_particle.lifeTime -= _deltaTime;
		Vertex& _vertex = system->GetVertexByIndex(_index++);

		if (_particle.lifeTime <= 0.0f)
		{
			Reset(_particle);
			_vertex.position = GetPosition();
		}

		_vertex.position += _particle.velocity * _deltaTime;
		float ratio = _particle.lifeTime / maxLifeTime;
		_vertex.color.a = CAST(uint8_t, ratio * 255);
	}
}

void ParticleActor::Reset(Particle& _particle)
{
	const Angle& _angle = degrees(GetRandomNumberInRange(0.0f, 360.0f));
	const float _speed = GetRandomNumberInRange(50.0f, 100.0f);
	_particle.velocity = Vector2f(_speed, _angle);
	_particle.lifeTime = GetRandomNumberInRange(1.0f, 3.0f);
}