#pragma once
#include "Singleton.h"
#include "Game.h"

class GameManager : public Singleton<GameManager>
{
	Game* currentGame;

public:
	FORCEINLINE Game* GetCurrent() const
	{
		return currentGame;
	}

public:
	~GameManager();

	virtual void Launch(Game* _currentGame);
};