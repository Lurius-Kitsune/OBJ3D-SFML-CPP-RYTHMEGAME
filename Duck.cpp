#include "Duck.h"
#include "TimerManager.h"
#include "Level.h"
#include "AudioManager.h"

Duck::Duck(const Vector2f& _size, const string& _path, const IntRect& _rect) : MeshActor(RectangleShapeData(_size, _path, PNG, false, _rect), "Duck")
{
	movement = CreateComponent<MovementComponent>();
	animation = CreateComponent<AnimationComponent>();

	//CreateSocket("Socket");
}

Duck::Duck(const Duck& _other) : MeshActor(_other)
{
	movement = CreateComponent<MovementComponent>(_other.movement);
	animation = CreateComponent<AnimationComponent>();
}


void Duck::Construct()
{
	Super::Construct();

	const float _timeBetween = 0.01f;
	const Vector2i& _spriteSize = Vector2i(41, 39);
	const vector<SpriteData>& _spritesData =
	{
		{ _timeBetween, Vector2i(0, 8), _spriteSize },
		{ _timeBetween, Vector2i(43, 8), _spriteSize },
		{ _timeBetween, Vector2i(85, 8), _spriteSize },
		{ _timeBetween, Vector2i(127, 8), _spriteSize },
		{ _timeBetween, Vector2i(0, 48), _spriteSize },
		{ _timeBetween, Vector2i(43, 48), _spriteSize },
		{ _timeBetween, Vector2i(85, 48), _spriteSize },
		{ _timeBetween, Vector2i(127, 48), _spriteSize },
		{ _timeBetween, Vector2i(0, 86), _spriteSize },
		{ _timeBetween, Vector2i(43, 86), _spriteSize },
		{ _timeBetween, Vector2i(85, 86), _spriteSize },
		{ _timeBetween, Vector2i(127, 86), _spriteSize },
	};
	//const SpriteData& _spriteData = { 0.2f, Vector2i(), Vector2i(80, 50) };
	AnimationData _animationData = AnimationData(2.0f, _spritesData);
	_animationData.notifies[6] = []() 
	{
		M_AUDIO.PlaySample<SoundSample>("couin", WAV);
	};

	animation->AddAnimation(new Animation("Default", GetMesh()->GetShape(), _animationData));
	animation->SetCurrentAnimation("Default");
	animation->StartAnimation();
}

void Duck::Deconstruct()
{
	Super::Deconstruct();
	animation->StopAnimation();
}

void Duck::BeginPlay()
{
	Super::BeginPlay();
}