#pragma once
#include "Actor.h"
#include "RenderType.h"

namespace UI
{
	enum VisibilityType
	{
		Hidden,
		Collapsed,
		Disabled,
		UninteractibleSelf,
		UninteractibleSelfAndChildren,
		Visible,
	};

	class Widget : public Actor
	{
		int zOrder;
		u_int renderToken;
		RenderType type;
	protected:
		VisibilityType visibility;

	public:
		FORCEINLINE void SetVisibility(const VisibilityType& _visibility)
		{
			visibility = _visibility;
		}
		FORCEINLINE void SetZOrder(const int _zOrder)
		{
			zOrder = _zOrder;
		}

	public:
		Widget(const string& _name, const RenderType& _type = Screen);

		virtual void Construct() override;
		virtual void Deconstruct() override;
		virtual void Render(RenderWindow& _window) = 0;
	};
}