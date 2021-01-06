#pragma once
#include "GameObject.h"

#define HELICOPTER_SPEED_X 0.02f
#define HELICOPTER_SPEED_Y 0.008f

class HeliCopter : public CGameObject
{
public:
	HeliCopter(float X = 0, float Y = 0);
	virtual ~HeliCopter();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* listObject = NULL);
	void Render(Camera* camera);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

