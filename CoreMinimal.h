#pragma once
#include "Utilities.h"
#include "Logger.h"
#include "CustomException.h"
#include "SubclassOf.h"

#define M_GAME GameManager::GetInstance()
#define M_ACTOR ActorManager::GetInstance()
#define M_CAMERA CameraManager::GetInstance()
#define M_TIMER TM_Seconds::GetInstance()
#define M_TEXTURE TextureManager::GetInstance()
#define M_FONT FontManager::GetInstance()
#define M_AUDIO AudioManager::GetInstance()