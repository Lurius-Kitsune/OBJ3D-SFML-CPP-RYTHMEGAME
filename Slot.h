#pragma once
#include "CoreMinimal.h"

namespace UI
{
	class Slot //TODO Update
	{
	protected:
		Vector2f position;
		Vector2f size;
		class PanelWidget* parent;
		class Widget* content;

	public:
		FORCEINLINE PanelWidget* GetParent() const
		{
			return parent;
		}
		FORCEINLINE Widget* GetContent() const
		{
			return content;
		}
		FORCEINLINE Vector2f GetPosition() const
		{
			return position;
		}
		FORCEINLINE Vector2f GetSize() const
		{
			return size;
		}
		FORCEINLINE void SetSize(const Vector2f& _size)
		{
			size = _size;
		}
		FORCEINLINE void SetPosition(const Vector2f& _position)
		{
			position = _position;
		}

	public:
		Slot(PanelWidget* _parent, Widget* _content);
		virtual ~Slot() = default;
	};
}