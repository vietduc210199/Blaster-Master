#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprites.h"

#include "SpritesManager.h"

class AnimationsManager
{
	static AnimationsManager* __instance;
	
	CAnimations* animations;

	AnimationsManager()
	{
		animations = CAnimations::GetInstance();
	}

	void LoadResources();
public:
	static AnimationsManager* getInstance()
	{
		if (__instance == NULL)
		{
			__instance = new AnimationsManager;
			__instance->LoadResources();
		}
		return __instance;
	}

	CAnimations* getData()
	{
		return this->animations;
	}
};

