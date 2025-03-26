#pragma once
#include "Slot.h"

namespace UI
{
	class CanvasSlot : public Slot
	{
		bool fillToContent;
		int zOrder;

	public:
		//Gets if the slot to be auto-sized
		FORCEINLINE bool GetFillToContent() const
		{
			return fillToContent;
		}

		//Gets the position of the slot
		FORCEINLINE Vector2f GetPosition() const
		{
			return position;
		}

		//Gets the size of the slot
		FORCEINLINE Vector2f GetSize() const
		{
			return size;
		}
		//Gets the z-order on the slot
		FORCEINLINE int GetZOrder() const
		{
			return zOrder;
		}

		//Sets if the slot to be auto-sized
		FORCEINLINE void SetFillToContent(const bool _status)
		{
			fillToContent = _status;
			UpdateContent();
		}

		//Sets the position of the slot
		FORCEINLINE void SetPosition(const Vector2f& _position)
		{
			position = _position;
		}

		//Sets the size of the slot
		FORCEINLINE void SetSize(const Vector2f& _size)
		{
			size = _size;
		}

		//Sets the z-order on the slot
		FORCEINLINE void SetZOrder(const int& _value)
		{
			zOrder = _value;
		}

	public:
		CanvasSlot(PanelWidget* _parent, Widget* _content);

	private:
		void UpdateContent();
	};
}
