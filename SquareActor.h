#pragma once
#include "RectangleActor.h"

class SquareActor : public RectangleActor
{
public:
	SquareActor(Level* _level, const float _size, const string& _path = "", const TextureExtensionType& _textureType = PNG, const IntRect& _rect = {});
	SquareActor(const SquareActor& _other);
};