#pragma once
#include "Singleton.h"
#include "InputManager.h"
#include "Level.h"

class Engine : public Singleton<Engine>
{
	RenderWindow window;
	Input::InputManager inputManager;
	Color backgroundColor;

public:
	Engine();

public:
	void Start();
	void Update();
	void UpdateWindow();
	void Stop();
};