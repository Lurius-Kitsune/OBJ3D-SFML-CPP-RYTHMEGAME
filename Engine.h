#pragma once
#include "Singleton.h"
#include "InputManager.h"
#include "Level.h"

using namespace Input;

class Engine : public Singleton<Engine>
{
	RenderWindow window;
	InputManager inputManager;
	Color backgroundColor;

public:
	Engine();

public:
	void Start();
	void Update();
	void UpdateWindow();
	void Stop();
};