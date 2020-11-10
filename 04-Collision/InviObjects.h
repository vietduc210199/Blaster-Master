#pragma once
#include "define.h"
#include "camera.h"
#include "GameObject.h"

class InviObjects : public CGameObject
{
	boolean active = true;
public:
	InviObjects() :CGameObject()
	{
		isTouchable = true;
	}

	void SetTouchable(boolean a)
	{
		isTouchable = a;
	}
	void SetType(int a)
	{
		type = a;
	}
	int GetType()
	{
		return type;
	}
	void SetActive(boolean a) { active = a; }
	virtual void Render(Camera* camera);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

