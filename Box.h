#pragma once
#include "CoreMinimal.h"
#include "Widget.h"
#include "HUD.h"

using namespace UI;

struct BoxData
{
	float spaceBetween;
	Vector2f size;

	BoxData()
	{
		spaceBetween = 0;
		size = { 0.0f, 0.0f };
	}

	BoxData(const Vector2f& _size, const float _spaceBetween = 20.0f)
	{
		spaceBetween = _spaceBetween;
		size = _size;
	}
};

class Box : public Widget
{
protected:
	vector<Widget*> widgets;
	BoxData data;

public:
	FORCEINLINE void AddWidget(Widget* _widget, const int _zOrder)
	{
		
	}
	FORCEINLINE void AddWidget(Widget* _widget)
	{
		widgets.push_back(_widget);
		AddChild(_widget, AT_KEEP_RELATIVE);
		Update();
		M_HUD.AddToViewport(_widget);
	}
	FORCEINLINE void RemoveWidget(Widget* _widget)
	{
		using Iterator = vector<Widget*>::iterator;
		for (Iterator _it; _it != widgets.end(); ++_it)
		{
			if (*_it == _widget)
			{
				widgets.erase(_it); 
				break;
			}
		}
		RemoveChild(_widget);
		M_HUD.RemoveFromViewport(_widget);
		Update();
	}

#pragma region Getters
protected: 
	FORCEINLINE u_int GetElementCount() const
	{
		return CAST(u_int, GetChildren().size());
	}

public:
	FORCEINLINE virtual Vector2f GetSize() const override
	{
		return data.size;
	}
#pragma endregion

public:
	Box() = default;
	Box(const BoxData& _data);

public:
	virtual void Update();
};