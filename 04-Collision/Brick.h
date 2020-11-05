#pragma once
#include "GameObject.h"
#include "Simon.h"
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16


class CBrick : public CGameObject
{
	int multwidth;

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
		boolean active = true;
		void SetActive(boolean a) { active = a; }
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
