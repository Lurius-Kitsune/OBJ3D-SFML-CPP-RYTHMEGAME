#include "CircleActor.h"

CircleActor::CircleActor(Level* _level, const float _radius, const string& _path,
						 const IntRect& _rect, const size_t& _pointCount)
					   : MeshActor(_level, CircleShapeData(_radius, _path, _rect, _pointCount))
{
	
}

CircleActor::CircleActor(const CircleActor& _other) : MeshActor(_other)
{

}