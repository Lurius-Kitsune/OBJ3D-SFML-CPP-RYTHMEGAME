#pragma once
#include "MeshActor.h"

class RectangleActor : public MeshActor
{
public:
	RectangleActor(Level* _level, const RectangleShapeData& _data);
	RectangleActor(const RectangleActor& _other);
};