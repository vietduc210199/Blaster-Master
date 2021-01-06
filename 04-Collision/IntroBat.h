#pragma once
#include "GameObject.h"


class IntroBat : public CGameObject
{
public:
	IntroBat(float X, float Y, float VX, float VY);
	~IntroBat();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* listObject = NULL);
	void Render(Camera* camera);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

