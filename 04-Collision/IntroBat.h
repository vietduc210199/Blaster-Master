#pragma once
#include "GameObject.h"


class IntroBat : public CGameObject
{
	IntroBat(float X = 0, float Y = 0, float VX = 0, float VY = 0);
	~IntroBat();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* listObject = NULL);
	void Render(Camera* camera);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

