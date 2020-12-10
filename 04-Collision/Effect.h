#pragma once
#include "define.h"
#include "GameObject.h"

class Effect : public CGameObject
{
	Camera* camera;
	DWORD dooractive_timer;
public:
	Effect(Camera* camera) :CGameObject()
	{
		this->animations = AnimationsManager::getInstance()->getData(aniType::ANI_EFFECT);
		this->camera = camera;
	}
	void SetType(int a)
	{
		type = a;
	}

	void SetActive(boolean a) { active = a; }
	virtual void Render(Camera* camera);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

