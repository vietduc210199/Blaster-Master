#pragma once
#include "define.h"
#include "GameObject.h"
#include "camera.h"
#include "Simon.h"
#include "MS.h"
#include "Axe.h"
#include "Dagger.h"
#include "HolyWater.h"

class Boss : public CGameObject
{
private:
	CSimon* simon;
	CMS* MS;
	Axe* axe;
	Dagger* dagger;
	Camera* camera;

	DWORD timerWait = 0;
	DWORD timerAttack = 0;
	DWORD getMSDamage_start;

	vector<LPGAMEOBJECT> simondagger;
	vector<LPGAMEOBJECT> simonaxe;
	vector<LPGAMEOBJECT> simonholywater;

	int ani;
	int HP;
	int isGettingMSDamage = 0;
	bool isAttack;
	bool isWait;
	bool isHurtbyweapon;
public:

	Boss(CSimon* simon, CMS* MS, Camera* camera) :CGameObject()
	{
		this->LoadAnimations("ReadFile\\Ani\\Bossani.txt");
		this->simon = simon;
		this->camera = camera;
		this->MS = MS;
		HP = 24;
		type = BOSS;
	}
	~Boss();

	void GetSimonAxe(Axe* axe)
	{
		isHurtbyweapon = true;
		simonaxe.push_back(axe);
	}
	void GetSimonDagger(Dagger* dagger)
	{
		isHurtbyweapon = true;
		simondagger.push_back(dagger);
	}
	void GetSimonHolyWater(HolyWater* holywater)
	{
		isHurtbyweapon = true;
		simonholywater.push_back(holywater);
	}
	void SetFirstPos(int x, int y)
	{
		this->FirstX = x;
		this->FirstY = y;
	}

	int GetHealth()
	{
		return this->HP;
	}

	void StartGetDamageMS() { isGettingMSDamage = 1; getMSDamage_start = GetTickCount(); };
	void DeleateWaeponWhenUnactive();
	void CollisionWhenDead(vector<LPGAMEOBJECT>* coObjects);
	void CheckCollisionWeapon();
	void CheckCollisionSimon();
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
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void CollisionOccurred(vector<LPGAMEOBJECT>* coObjects) override;
};

