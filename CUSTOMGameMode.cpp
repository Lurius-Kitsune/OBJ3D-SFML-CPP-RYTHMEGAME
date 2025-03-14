#include "CUSTOMGameMode.h"
#include "LevelManager.h"
#include "CUSTOMLevel.h"
#include "ImageWidget.h"
#include "Level.h"

CUSTOMGameMode::CUSTOMGameMode(Level* _level, const string& _name) : GameMode(_level, _name)
{
	
}


CUSTOMGameMode::CUSTOMGameMode(const CUSTOMGameMode& _other) : GameMode(_other)
{
	
}
