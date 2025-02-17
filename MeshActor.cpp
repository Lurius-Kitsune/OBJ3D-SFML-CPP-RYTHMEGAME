#include "MeshActor.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "Level.h"

MeshActor::MeshActor(Level* _level, const CircleShapeData& _data, const string& _name) : Actor(_level, _name)
{
	mesh = CreateComponent<MeshComponent>(_data);
}

MeshActor::MeshActor(Level* _level, const RectangleShapeData& _data, const string& _name) : Actor(_level, _name)
{
	mesh = CreateComponent<MeshComponent>(_data);
}

MeshActor::MeshActor(const MeshActor& _other) : Actor(_other)
{
	mesh = CreateComponent<MeshComponent>(*_other.mesh);
}


void MeshActor::SetZOrder(const int _zOrder)
{
	Super::SetZOrder(_zOrder);

	GetLevel()->GetCameraManager().SetZOrder(mesh->GetRenderMeshToken(), zOrder);
}