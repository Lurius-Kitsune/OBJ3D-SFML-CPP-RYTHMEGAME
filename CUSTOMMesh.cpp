#include "CUSTOMMesh.h"
#include "Level.h"
CUSTOMMesh::CUSTOMMesh(Level* _level, const RectangleShapeData& _data, const string& _name) : MeshActor(_level, _data, _name)
{
	canMove = true;

	collision = CreateComponent<CollisionComponent>();
	collision->SetInformation("test-movement", IS_ALL, CT_OVERLAP);
	collision->AddResponses({ {"test", CT_BLOCK}, {"ActorCollision",CT_BLOCK} });

}

CUSTOMMesh::CUSTOMMesh(Level* _level, const CircleShapeData& _data, const string& _name) : MeshActor(_level, _data, _name)
{
	canMove = true;

	collision = CreateComponent<CollisionComponent>();
	collision->SetInformation("test-movement", IS_ALL, CT_OVERLAP);
	collision->AddResponses({ {"test", CT_BLOCK}, { "ActorCollision",CT_BLOCK } });
}


void CUSTOMMesh::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	if (canMove)
	{
		SetPosition(CAST(Vector2f, Mouse::getPosition()));
	}
}

void CUSTOMMesh::CollisionEnter(const CollisionData& _data)
{
	if (_data.response == CT_BLOCK)
	{
		canMove = false;
	}
}