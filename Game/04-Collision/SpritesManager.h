#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "TextureManager.h"

#include<iostream>
#include<fstream>
#include<string>
#include<queue>

class SpritesManager
{
	static SpritesManager* __instance;
	CSprites* sprites;

	SpritesManager()
	{
		sprites = CSprites::GetInstance();
	}

	void LoadResources();
public:
	static SpritesManager* getInstance()
	{
		if (__instance == NULL)
		{
			__instance = new SpritesManager;
			__instance->LoadResources();
		}
		return __instance;
	}

	CSprites* getData() {
		return this->sprites;
	}
};

