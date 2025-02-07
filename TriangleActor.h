#pragma once
#include "MeshActor.h"

class TriangleActor : public MeshActor
{
public:
	TriangleActor(Level* _level, const float _radius, const string& _path = "", const IntRect& _rect = {});
	TriangleActor(const TriangleActor& _other);
};