#include "MeshComponent.h"
#include "Actor.h"
#include "Level.h"

MeshComponent::MeshComponent(Actor* _owner, const CircleShapeData& _data) : Component(_owner)
{
	renderMeshToken = -1;
	shape = new ShapeObject(_data);
}

MeshComponent::MeshComponent(Actor* _owner, const RectangleShapeData& _data) : Component(_owner)
{
	renderMeshToken = -1;
	shape = new ShapeObject(_data);
}

MeshComponent::MeshComponent(Actor* _owner, const MeshComponent& _other) : Component(_owner) 
{
	renderMeshToken = _other.renderMeshToken;
	shape = new ShapeObject(*_other.shape);
}

MeshComponent::~MeshComponent()
{
	delete shape;
}


void MeshComponent::Construct()
{
	Super::Construct();

	if (Cast<Widget>(owner)) return;
	const RenderData& _data = RenderData(bind(&MeshComponent::RenderMesh, this, _1));
	renderMeshToken = owner->GetLevel()->GetCameraManager().BindOnRenderWindow(_data);
}

void MeshComponent::Deconstruct()
{
	Super::Deconstruct();

	if (Cast<Widget>(owner)) return;
	owner->GetLevel()->GetCameraManager().UnbindOnRenderWindow(renderMeshToken);
}


void MeshComponent::SetOriginAtMiddle()
{
	GetOwner()->SetOrigin(shape->GetDrawable()->getGeometricCenter());
}

void MeshComponent::RenderMesh(RenderWindow& _window)
{
	if (!IsActive()) return;
	_window.draw(*shape->GetDrawable());
}