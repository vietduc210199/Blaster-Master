#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprites.h"

#include "SpritesManager.h"


class AnimationsManager
{
	static AnimationsManager* __instance;
	
	CAnimations* animation;
	
	unordered_map<int, vector<LPANIMATION>> animations;
	AnimationsManager()
	{
		animation = CAnimations::GetInstance();

	}

	void LoadResources();
	void LoadAnimations(int idAni, string source);
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

	vector<LPANIMATION> getData(int idani)
	{
		return this->animations[idani];
	}
	CAnimations* getData()
	{
		return this->animation;
	}
};

