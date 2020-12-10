#pragma once
#include "define.h"
#include "camera.h"
#include "GameObject.h"

class HolyWater : public CGameObject
{
private:
	float firstPos;
	DWORD fire_timer;
	Camera* camera;
public:
	HolyWater(float pos, Camera* camera, int nx) :CGameObject()
	{
		this->animations = AnimationsManager::getInstance()->getData(aniType::ANI_HOLYWATER);
		firstPos = pos;
		this->camera = camera;
		this->nx = nx;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render(Camera* camera);
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

