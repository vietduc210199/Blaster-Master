#pragma once
#include "define.h"
#include "GameObject.h"

class Ghoul : public CGameObject
{
public:
	Ghoul() :CGameObject()
	{
		this->LoadAnimations("ReadFile\\Ani\\Ghoulani.txt");
		SetState(ENEMY_STATE_MOVING);
		type = GHOUL;
		active = true;
	}
	~Ghoul();
	bool GetStop()
	{
		return isStop;
	}
	void SetStop(bool a) { isStop = a; }
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render(Camera* camera);

	RECT GetBound()
	{
		RECT rect;
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		return rect;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void CollisionOccurred(vector<LPGAMEOBJECT>* coObjects) override;
};

