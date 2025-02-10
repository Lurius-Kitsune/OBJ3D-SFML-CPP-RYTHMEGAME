#include "CUSTOMLevel.h"
#include "CUSTOMGameMode.h"
#include "ImageWidget.h"
#include "Particle.h"

CUSTOMLevel::CUSTOMLevel(const string& _name) : Level(_name)
{
	gameModeRef = CUSTOMGameMode(this, "CustomGameMode");
}


void CUSTOMLevel::InitLevel()
{
	Super::InitLevel();

	SubclassOf<CameraActor> _cameraRef = CameraActor(this, "Camera");
	CameraActor* _camera = SpawnCamera<CameraActor>(_cameraRef);
	if (RootComponent* _root = _camera->GetComponent<RootComponent>())
	{
		_root->SetPosition(Vector2f(0.0f, 0.0f));
	}

	if (MeshActor* _mesh = SpawnActor<MeshActor>(RectangleShapeData({ 50.f, 50.f }, "Wall", JPG)))
	{
		_mesh->SetPosition(Vector2f(100.0f, 0.0f));
	}

	SpawnActor<ParticleActor>(1000, 3.0f);
}