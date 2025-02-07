#pragma once
#include "Utilities.h"
#include "Logger.h"
#include "CustomException.h"
#include "SubclassOf.h"
#include "Kismet.h"

#define M_INPUT InputManager::GetInstance()
#define M_TIMER TM_Seconds::GetInstance()
#define M_TEXTURE TextureManager::GetInstance()
#define M_FONT FontManager::GetInstance()
#define M_AUDIO AudioManager::GetInstance()
#define M_LEVEL LevelManager::GetInstance()
#define M_HUD HUD::GetInstance()
#define M_COLLISION CollisionManager::GetInstance()
#define M_FILE FileManager::GetInstance()