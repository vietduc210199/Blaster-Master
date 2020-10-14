#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#define ID_TEX_SIMON 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_TORCH 30

#define ID_TEX_ENTRANCESTAGE 100

class TextureManager
{
	static TextureManager * __instance;
	CTextures* TexList;

	TextureManager()
	{
		TexList = CTextures::GetInstance();
	}

	void LoadResources();

public:
	static TextureManager* getInstance() {
		if (__instance==NULL)
		{
			__instance = new TextureManager;
			__instance->LoadResources();
		}
		return __instance;
	}

	CTextures* getData()
	{
		return this->TexList;
	}
};


