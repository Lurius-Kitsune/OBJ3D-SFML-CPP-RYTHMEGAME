#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(Actor* _owner) : Component(_owner)
{
	current = nullptr;
	allAnimations = map<string, Animation*>();
}

AnimationComponent::AnimationComponent(Actor* _owner, const AnimationComponent* _other) : Component(_owner)
{
	for (const pair<string, Animation*>& _animation : _other->allAnimations)
	{
		allAnimations[_animation.first] = new Animation(*_animation.second);
	}
	current = allAnimations[_other->current->GetName()];
}

AnimationComponent::~AnimationComponent()
{
	for (const pair<string, Animation*>& _animation : allAnimations)
	{
		delete _animation.second;
	}
}


void AnimationComponent::AddAnimation(Animation* _animation)
{
	const string& _animationName = _animation->GetName();
	if (allAnimations.contains(_animationName)) return;

	allAnimations[_animationName] = _animation;
}

void AnimationComponent::AddAnimations(const vector<Animation*>& _animations)
{
	const u_int& _animationsCount = CAST(u_int, _animations.size());
	for (u_int _index = 0; _index < _animationsCount; _index++)
	{
		AddAnimation(_animations[_index]);
	}
}