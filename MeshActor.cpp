#include "MeshActor.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "Level.h"

using namespace Camera;

MeshActor::MeshActor(const CircleShapeData& _data, const string& _name)
{
	renderMeshToken = -1;
	mesh = CreateComponent<MeshComponent>(_data);
	collision = CreateComponent<CollisionComponent>();
}

MeshActor::MeshActor(const RectangleShapeData& _data, const string& _name) : Actor(_name)
{
	renderMeshToken = -1;
	mesh = CreateComponent<MeshComponent>(_data);
	collision = CreateComponent<CollisionComponent>();
}

MeshActor::MeshActor(const MeshActor& _other) : Actor(_other)
{
	renderMeshToken = _other.renderMeshToken;
	mesh = CreateComponent<MeshComponent>(*_other.mesh);
	collision = CreateComponent<CollisionComponent>(*_other.collision);
}


void MeshActor::Construct()
{
	Super::Construct();

	const RenderData& _data = RenderData(bind(&MeshActor::RenderMesh, this, _1));
	renderMeshToken = level->GetCameraManager().BindOnRenderWindow(_data);

	if (collision->GetChannelName() != "NONE")
	{
		M_COLLISION.AddCollision(collision);
	}
}

void MeshActor::Deconstruct()
{
	Super::Deconstruct();
	level->GetCameraManager().UnbindOnRenderWindow(renderMeshToken);
	M_COLLISION.RemoveCollision(collision);
}


void MeshActor::RenderMesh(RenderWindow& _window)
{
	_window.draw(*mesh->GetShape()->GetDrawable());
}