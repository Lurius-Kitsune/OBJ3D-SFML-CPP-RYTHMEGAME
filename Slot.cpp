#include "Slot.h"

Slot::Slot(const Vector2f _position, const Vector2f _size)
{
	position = _position;
	size = _size;
	autoSize = false;
	zOrder = 0;
}
