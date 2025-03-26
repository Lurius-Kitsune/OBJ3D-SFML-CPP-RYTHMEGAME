#include "RectangleActor.h"

RectangleActor::RectangleActor(Level* _level, const RectangleShapeData& _data) : MeshActor(_level, _data)
{

}

RectangleActor::RectangleActor(const RectangleActor& _other) : MeshActor(_other)
{

}