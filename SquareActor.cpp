#include "SquareActor.h"

SquareActor::SquareActor(Level* _level, const float _size, const string& _path, const TextureExtensionType& _textureType, const IntRect& _rect)
					   : RectangleActor(_level, RectangleShapeData(Vector2f(_size, _size), _path, _textureType, false, _rect))
{

}

SquareActor::SquareActor(const SquareActor& _other) : RectangleActor(_other)
{

}