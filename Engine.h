#pragma once
#include "InputManager.h"

class Engine
{
	RenderWindow window;
	Input::InputManager inputManager;

public:
	Engine();

public:
	void Start();
	void Update();
	void Stop();
};