#include "MeshActor.h"
#include "CameraManager.h"
#include "Level.h"

using namespace Camera;

MeshActor::MeshActor(const CircleShapeData& _data, const string& _name)
{
	mesh = CreateComponent<MeshComponent>(_data);
	renderMeshToken = -1;
}

MeshActor::MeshActor(const RectangleShapeData& _data, const string& _name) : Actor(_name)
{
	mesh = CreateComponent<MeshComponent>(_data);
	renderMeshToken = -1;
}

MeshActor::MeshActor(const VertexArrayData& _data, const string& _name) : Actor(_name)
{
	mesh = CreateComponent<MeshComponent>(_data);
	renderMeshToken = -1;
}

MeshActor::MeshActor(const MeshActor& _other) : Actor(_other)
{
	mesh = CreateComponent<MeshComponent>(_other.mesh);
	renderMeshToken = _other.renderMeshToken;
}


void MeshActor::Construct()
{
	Super::Construct();

	const RenderData& _data = RenderData(bind(&MeshActor::RenderMesh, this, placeholders::_1));
	renderMeshToken = level->GetCameraManager().BindOnRenderWindow(_data);
	
}

void MeshActor::Deconstruct()
{
	Super::Deconstruct();
	level->GetCameraManager().UnbindOnRenderWindow(renderMeshToken);
}


void MeshActor::RenderMesh(RenderWindow& _window)
{
	_window.draw(*mesh->GetShape()->GetDrawable());
}