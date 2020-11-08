#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Game.h"



class CMS :public CGameObject
{
public:
	int attack;
	CGameObject* simon;
	DWORD attack_start;
	int attackStart;
	boolean active = false;
	int level;

public:
	int MSUpDropTime;
	CMS() :CGameObject()
	{
		this->LoadAnimations("ReadFile\\Ani\\MSani.txt");
		attack = 0;
		MSUpDropTime = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render(camera* camera);
	void SetState(int state);
	void SetActive(boolean a)
	{
		active = a;
	}
	void StartAttack() {
		attack = 1;
		attack_start = GetTickCount();
		for (int i = 0; i < 6; i++)
		{
			animations[i]->SetCurrentcFrame(-1);
		}
	}
	void GetSimon(CGameObject* Simon) {
		this->simon = Simon;
	}
	void AdjustMSPos();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

