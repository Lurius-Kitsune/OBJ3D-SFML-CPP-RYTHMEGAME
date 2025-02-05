#include "TriangleActor.h"

TriangleActor::TriangleActor(const float _radius, const string& _path, const IntRect& _rect)
						   : MeshActor(CircleShapeData(_radius, _path, _rect, 3))
{

}