#pragma once
#include "ImageWidget.h"
#include "AnimationComponent.h"

namespace UI
{
	class GIFWidget : public ImageWidget
	{
		AnimationComponent* animation;

	public:
		FORCEINLINE void AddAnimation(Animation* _animation)
		{
			animation->AddAnimation(_animation);
		}
		FORCEINLINE void AddAnimations(const vector<Animation*>& _animations)
		{
			animation->AddAnimations(_animations);
		}

	public:
		GIFWidget(Level* _level, const RectangleShapeData& _data, const string& _name = "Image", const RenderType& _type = Screen);
		GIFWidget(Level* _level, const CircleShapeData& _data, const string& _name = "Image", const RenderType& _type = Screen);
		GIFWidget(const GIFWidget& _other);

		virtual void BeginPlay() override;
	};
}