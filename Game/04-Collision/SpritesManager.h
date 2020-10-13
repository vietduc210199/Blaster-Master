#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
class SpritesManager
{
	static SpritesManager* __instance;
	CSprites* sprites;

	SpritesManager()
	{
		sprites = CSprites::GetInstance();
	}

	void LoadSprites();
public:
	static SpritesManager* getInstance()
	{
		if (__instance == NULL)
		{
			__instance = new SpritesManager;
			__instance->LoadSprites();
		}
		return __instance;
	}

	CSprites* getData() {
		return this->sprites;
	}
};

