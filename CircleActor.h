#pragma once
#include "MeshActor.h"

class CircleActor : public MeshActor
{
public:
	CircleActor(Level* _level, const float _radius, const string& _path = "", const IntRect& _rect = {},
				const size_t& _pointCount = 30);
	CircleActor(const CircleActor& _other);
};