#pragma once
#include "GameObject.h"
#include "Simon.h"
#define BRICK_BBOX_WIDTH 32
#define BRICK_BBOX_HEIGHT 32


class CBrick : public CGameObject
{
	
	public:
		CBrick()
		{
			this->LoadAnimations("ReadFile\\Ani\\Brickani.txt");
			//this->AddAnimation(1000);
		}
		boolean active = true;
		void SetActive(boolean a) { active = a; }
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
