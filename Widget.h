#pragma once
#include "Actor.h"
#include "RenderType.h"
#include "Slot.h"

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
		u_int renderToken;
		RenderType type;
	protected:
		Slot* slot;
		VisibilityType visibility;
		int zOrder;

	public:
		FORCEINLINE virtual void AddSlot(Slot* _slot)
		{
			slot = _slot;
		}
		FORCEINLINE virtual void RemoveSlot()
		{
			delete slot;
		}
		FORCEINLINE virtual Slot* GetSlot() const
		{
			return slot;
		}
		FORCEINLINE virtual void SetVisibility(const VisibilityType& _visibility)
		{
			visibility = _visibility;
		}
		FORCEINLINE virtual int GetZOrder() const
		{
			return zOrder;
		}
		FORCEINLINE virtual void SetZOrder(const int _zOrder)
		{
			zOrder = _zOrder;
		}
		FORCEINLINE virtual Vector2f GetSize() const = 0;

	public:
		Widget(const string& _name, const RenderType& _type = Screen);
		~Widget();

		virtual void Construct() override;
		virtual void Deconstruct() override;
		virtual void Render(RenderWindow& _window) = 0;
	};
}