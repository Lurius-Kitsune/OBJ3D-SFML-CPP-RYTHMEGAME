#pragma once
#include "CoreMinimal.h"

class Slot //TODO Update
{
	Vector2f position;
	Vector2f size;
	bool autoSize;
	int zOrder;
public:
	//Gets if the slot to be auto-sized
	FORCEINLINE bool GetAutoSize() const
	{
		return autoSize;
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
	FORCEINLINE void SetAutoSize(const bool _status)
	{
		autoSize = _status;
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
	Slot(const Vector2f _position, const Vector2f _size);
};