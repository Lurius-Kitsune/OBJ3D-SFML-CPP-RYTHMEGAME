#include "CUSTOMPawn.h"
#include "Level.h"
#include "InputManager.h"

using namespace Input;

CUSTOMPawn::CUSTOMPawn(Level* _level, const string& _name) : Pawn(_level, _name)
{
	mesh = CreateComponent<MeshComponent>(RectangleShapeData(Vector2f(50.0f, 50.0f)));

	camera = CreateComponent<CameraComponent>(_level->GetWindowSize() / 2.0f, _level->GetWindowSize());
	_level->GetCameraManager().Register(camera);
}

CUSTOMPawn::CUSTOMPawn(const CUSTOMPawn& _other) : Pawn(_other)
{
	mesh = CreateComponent<MeshComponent>(*_other.mesh);
	camera = CreateComponent<CameraComponent>(*_other.camera);
}


void CUSTOMPawn::SetupInputController(Input::InputManager& _inputManager)
{
	ActionMap* _moveInputs = _inputManager.CreateActionMap("PlayerMovement");
	
	_moveInputs->AddActions(
	{
		new Action("Up", ActionData(KeyPressed, Z), [&]()
		{
			LOG(Warning, "Z");
			//movement->AddVelocity(Vector2f(0.0f, 1.0f));
		}),
		new Action("Down", ActionData(KeyHold, S), [&]()
		{
			LOG(Warning, "S");
			//movement->AddVelocity(Vector2f(0.0f, -1.0f));
		}),
		new Action("Left", ActionData(KeyHold, Q), [&]()
		{
			LOG(Warning, "Q");
			//movement->AddVelocity(Vector2f(-1.0f, 0.0f));
		}),
		new Action("Right", ActionData(KeyHold, D), [&]()
		{
			LOG(Warning, "D");
			//movement->AddVelocity(Vector2f(1.0f, 0.0f));
		}),
		//new Action("Test", ActionData(KeyPressed, T), [&]()
		//{
		//	LOG(Warning, "suprr");
		//	_inputManager.GetActionMapByName("PlayerMovement")->DeleteAction("Up");
		//	//movement->AddVelocity(Vector2f(1.0f, 0.0f));
		//}),
		//new Action("Test25", ActionData(KeyPressed, I), [&]()
		//{
		//	LOG(Warning, "suprr25");
		//	_inputManager.GetActionMapByName("PlayerMovement")->DeleteAction("Down");
		//	//movement->AddVelocity(Vector2f(1.0f, 0.0f));
		//}),
		//	new Action("Test2", ActionData(KeyPressed, P), [&]()
		//{
		//	LOG(Warning, "suprr action map !");
		//	_inputManager.DeleteActionMap("PlayerMovement");
		//	//movement->AddVelocity(Vector2f(1.0f, 0.0f));
		//}),
	});

	_moveInputs->Enable();
}