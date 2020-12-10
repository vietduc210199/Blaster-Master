#pragma once
#include "define.h"
#include "camera.h"
#include "GameObject.h"


class Dagger :public CGameObject
{
private:
	Camera* camera;
public:
	Dagger(Camera* camera, int nx) :CGameObject()
	{
		this->animations = AnimationsManager::getInstance()->getData(aniType::ANI_DAGGER);
		this->camera = camera;
		this->nx = nx;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render(Camera* camera);
	void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

