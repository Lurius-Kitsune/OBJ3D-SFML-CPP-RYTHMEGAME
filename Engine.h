#pragma once
#include "Singleton.h"
#include "InputManager.h"

using namespace Input;

class Engine : public Singleton<Engine>
{
	RenderWindow window;
	InputManager inputManager;

public:
	Engine();

public:
	void Start();
	void Update();
	void Stop();

	void UpdateWindow();

};