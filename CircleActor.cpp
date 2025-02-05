#include "CircleActor.h"

CircleActor::CircleActor(const float _radius, const string& _path, const IntRect& _rect,
						 const size_t& _pointCount)
					   : MeshActor(CircleShapeData(_radius, _path, _rect, _pointCount))
{
	
}