#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "camera.h"
#include "define.h"



class CBrick : public CGameObject
{
	int multwidth;
	boolean active = true;

	public:
		CBrick()
		{
			this->LoadAnimations("ReadFile\\Ani\\Brickani.txt");
			//this->AddAnimation(1000);
			type = eType::BRICK;
			state = eType::BRICK_STATE_NORMAL;
		}
		void SetMulwidth(int a)
		{
			this->multwidth = a;
		}
		void SetType(int a)
		{
			type = a;
		}
		
	void SetActive(boolean a) { active = a; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render(Camera* camera);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
