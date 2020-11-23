#pragma once
#include <iostream>
#include <memory>
#include "GameObject.h"
#include "MS.h"

#define SIMON_WALKING_SPEED		0.07f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.22f
#define SIMON_JUMP_DEFLECT_SPEED 0.1f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define PULL_UP_SIMON_AFTER_SITTING 10.0f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_SQUAT		500

#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_ATTACK 500
#define SIMON_STATE_SIT 600

#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1

#define SIMON_ANI_WALKING_RIGHT			2
#define SIMON_ANI_WALKING_LEFT			3
#define SIMON_ANI_ATTACK_RIGHT				4
#define SIMON_ANI_ATTACK_LEFT				5
#define SIMON_ANI_JUMP_RIGHT 6
#define SIMON_ANI_JUMP_LEFT 7
#define SIMON_ANI_SIT_RIGHT 8
#define SIMON_ANI_SIT_LEFT 9
#define SIMON_ANI_DIE		99		

//#define SIMON_PULL_SIT 18.0f
#define SIMON_IDLE_BBOX_WIDTH  16
#define SIMON_IDLE_BBOX_HEIGHT 30
#define SIMON_SIT_BBOX_HEIGHT 23

#define SIMON_JUMP_TIME 500
#define SIMON_ATTACK_TIME 300


class CSimon: public CGameObject
{
	int jump;
	int jumpmove;
	int attack;
	int sitattack;
	int right;
	int changecolor;
	int autowalking;
	int isDamaged;
	int isUntouchable;
	int alpha;
	int numweapon;
	int startpoint;
	int endpoint;
	int untouchabletime;
	int health;
	float autowalkingtime;
	bool active = true;
	bool sit = false;
	bool jumping = false;
	bool isOnStair = false;
	bool isStairUp = true;
	bool isThrowDagger = false;
	bool isThrowAxe = false;
	bool isThrowHolyWater = true;
	bool autowalkingdoor = false;
	bool isEatCross;
	bool isEatClock;
	DWORD jump_start;
	DWORD attack_start;
	DWORD sitattack_start;
	DWORD changecolor_start;
	DWORD autowalking_start;
	DWORD autowalkingdoor_start;
	DWORD isDamaged_start;
	DWORD isUntouchable_start;

public: 
	CSimon() : CGameObject()
	{
		this->LoadAnimations("ReadFile\\Ani\\simonani.txt");
		numweapon = 1;
		health = 16;
		jump = 0;
		attack = 0;
		sitattack = 0;
		changecolor = 0;
		autowalking = 0;
		isDamaged = 0;
		isUntouchable = 0;
		isOnGround = true;
		alpha = 255;
		level = SIMON_LEVEL_MS_1;
	}
	int GetLevel()
	{
		return this->level;
	}
	int GetChangeColorTime()
	{
		return changecolor;
	}
	int GetAttackTime()
	{
		return this->attack;
	}
	int GetJumpTime()
	{
		return this->jump;
	}
	int GetJumpMoveTime()
	{
		return this->jumpmove;
	}
	int GetAutoWalkingTime()
	{
		return this->autowalking;
	}
	int GetIsDamaged()
	{
		return isDamaged;
	}
	int GetUntouchable()
	{
		return this->isUntouchable;
	}
	int GetAlpha()
	{
		return this->alpha;
	}
	int GetNumWeapon()
	{
		return numweapon;
	}
	int GetStartPoint()
	{
		return startpoint;
	}
	int GetEndPOint()
	{
		return endpoint;
	}
	int GetHealth()
	{
		return health;
	}
	boolean GetSit()
	{
		return sit;
	}
	boolean GetOnGround()
	{
		return isOnGround;
	}
	boolean GetOnStair()
	{
		return isOnStair;
	}
	boolean GetStairUp()
	{
		return isStairUp;
	}
	boolean GetEatCross()
	{
		return isEatCross;
	}
	boolean GetEatClock()
	{
		return isEatClock;
	}
	boolean GetActive() 
	{ 
		return active; 
	};
	boolean GetThrowDagger() { return isThrowDagger; }
	boolean GetThrowAxe() { return isThrowAxe; }
	boolean GetThrowHolyWater() { return isThrowHolyWater; }
	void SetState(int state);
	void SetLevel(int level)	
	{
		CGameObject::SetLevel(level);
	}
	void SetOnStair(bool a) {
		isOnStair = a;
	};
	void SetStairUp(bool a) {
		isStairUp = a;
	};
	void SetActive(boolean a) 
	{
		active = a;
	}
	void SetOnGround(boolean a)
	{
		isOnGround = a;
	}
	void SetAlpha(int a)
	{
		alpha = a;
	}
	void SetEatCross(bool a) {
		isEatCross = a;
	}
	void SetEatClock(bool a) {
		isEatClock = a;
	}
	void SetThrowDagger(bool a)
	{
		isThrowDagger = a;
	}
	void SetThrowAxe(bool a)
	{
		isThrowAxe = a;
	}
	void SetThrowHolyWater(bool a)
	{
		isThrowHolyWater = a;
	}
	void SetNumWeapon(int a)
	{
		numweapon = a;
	}
	void SetStartPoint(int a);
	void SetEndPoint(int a);
	void SetHealth(int a)
	{
		health = health - a;
	}
	void SetHealthToZero()
	{
		health = 0;
	}
	void StartJump() { jump = 1; jump_start = GetTickCount(); }
	void StartJumpMove() { jumpmove = 1; jump_start = GetTickCount(); }
	void StartAttack() 
	{ 
		attack = 1; attack_start = GetTickCount(); 
		RestartAttack();
	}
	void StartSitAttack() {
		sitattack = 1; sitattack_start = GetTickCount();
		RestartAttack();
	}
	void RestartAttack()
	{
		animations[SIMON_ANI_ATTACK_RIGHT]->SetCurrentcFrame(-1);
		animations[SIMON_ANI_ATTACK_LEFT]->SetCurrentcFrame(-1);
		animations[SIMON_ANI_SIT_ATTACK_RIGHT]->SetCurrentcFrame(-1);
		animations[SIMON_ANI_SIT_ATTACK_LEFT]->SetCurrentcFrame(-1);
	}
	void StartChangeColor() { changecolor = 1; changecolor_start = GetTickCount(); vx = 0; }
	void StartAutoWalking(float a) { autowalking = 1; autowalking_start = GetTickCount(); autowalkingtime = a; }
	void StartIsDamaged() { isDamaged = 1; isDamaged_start = GetTickCount(); RestartAttack(); }
	void StartIsUnTouchable(int a) { isUntouchable = 1; isUntouchable_start = GetTickCount(); untouchabletime = a; }
	void SetSit(boolean a) { sit = a; };
	void SetJump(int a) { jump = a; }

	void SitDown();
	void StandUp();


	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render(Camera* camera);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};