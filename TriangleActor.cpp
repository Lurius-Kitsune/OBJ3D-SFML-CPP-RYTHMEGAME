#include "TriangleActor.h"

TriangleActor::TriangleActor(Level* _level, const float _radius, const string& _path, const IntRect& _rect)
						   : MeshActor(_level, CircleShapeData(_radius, _path, _rect, 3))
{

}

TriangleActor::TriangleActor(const TriangleActor& _other) : MeshActor(_other)
{

}