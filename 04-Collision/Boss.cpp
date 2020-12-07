#include "Boss.h"

Boss::~Boss()
{
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!active)
		return;
	CGameObject::Update(dt, coObjects);
	CheckCollisionWeapon();
	CollisionWhenDead(coObjects);
	DeleateWaeponWhenUnactive();

	if (x <= camera->GetPosition().x && state != BOSS_STATE_SLEEP)
		vx = -vx;
	if (x >= camera->GetPosition().x + SCREEN_WIDTH - BOSS_WIDTH && state != BOSS_STATE_SLEEP)
		vx = -vx;
	if (y <= BOSS_ATTACK_HEIGHT)
		vy = 0;
	if (GetTickCount() - dietime_start > (ENEMY_DIE_TIME * 3))
	{
		dietime_start = 0;
		die = 0;
	}

	if (isGettingMSDamage == 1)
	{
		if (GetTickCount() - getMSDamage_start > BOSS_GETTING_MS_DAMAGE_TIME)
			isGettingMSDamage = 0;
	}
	if (state == BOSS_STATE_DIE && die == 0)
	{
		SetPosition(FirstX, FirstY);
		state = BOSS_STATE_BLOOD;
	}
	if (state == BOSS_STATE_BLOOD)
	{
		if (isOnGround == false)
		{
			vy = GRAVITY * dt;
		}
	}
	if (simon->GetPosition().x > x&& state == BOSS_STATE_SLEEP)
	{
		state = BOSS_STATE_AWAKEN;
	}
	if (y <= 100 && state == BOSS_STATE_ATTACK && isWait == true)
	{
		state = BOSS_STATE_FLY;
	}
	if (x >= FirstX - 10 && x <= FirstX + 20 && state == BOSS_STATE_FLY)
	{
		isWait = false;
		vx = 0;
		state = BOSS_STATE_ATTACK;
	}
	if (state == BOSS_STATE_AWAKEN)
	{
		if (y <= BOSS_ATTACK_HEIGHT)
		{
			vy = BOSS_AWAKEN_SPEED_Y;
		}
		else
		{
			vx = 0;
			vy = 0;
			state = BOSS_STATE_ATTACK;
		}
	}
	if (state == BOSS_STATE_ATTACK)
	{
		if (timerAttack < BOSS_ATTACK_TIME)
		{
			timerAttack += dt;
		}
		else
		{
			timerAttack = 0;
			isAttack = true;
		}
		if (isAttack == true)
		{
			if (simon->GetPosition().x < x)
			{
				vx = -BOSS_ATTACK_SPEED_X;
				vy = BOSS_ATTACK_SPEED_Y;
			}
			else
			{
				vx = BOSS_ATTACK_SPEED_X;
				vy = BOSS_ATTACK_SPEED_Y;
			}
			isAttack = false;
			isWait = true;
		}
		if (abs(y - simon->GetPosition().y) <= 5)
		{
			vy = 0;
			if (abs(simon->GetPosition().x - x) >= 5)
			{
				vy = BOSS_FLY_UP_SPEED;
			}
		}
	}

	if (state == BOSS_STATE_FLY)
	{
		if (x < FirstX)
		{
			vx = BOSS_FLY_SPEED_X;
		}
		else
		{
			vx = -BOSS_FLY_SPEED_X;
		}
	}
}


void Boss::CollisionWhenDead(vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BOSS_STATE_BLOOD)
	{
		Collision(coObjects);
	}
	else if (state != BOSS_STATE_BLOOD)
	{
		x += dx;
		y += dy;
	}
}

void Boss::CheckCollisionWeapon()
{
	if (CheckCollision(MS) && isGettingMSDamage == 0)
	{
		StartGetDamageMS();
		if (MS->state == MS_STATE_ATTACK)
		{
			HP -= 1;
		}
		if (MS->state == MS_STATE_ATTACK_2)
		{
			HP -= 1;
		}
		if (MS->state == MS_STATE_ATTACK_3)
		{
			HP -= 2;
		}
	}
	for (int i = 0; i < simonaxe.size(); i++)
	{
		if (CheckCollision(simonaxe.at(i)) && isHurtbyweapon )
		{
			StartGetDamageMS();
			HP -= 2;
			isHurtbyweapon = false;
		}
	}
	for (int i = 0; i < simondagger.size(); i++)
	{
		if (CheckCollision(simondagger.at(i)) && isHurtbyweapon)
		{
			StartGetDamageMS();
			HP -= 2;
			isHurtbyweapon = false;
		}
	}
	for (int i = 0; i < simonholywater.size(); i++)
	{
		if (CheckCollision(simonholywater.at(i)) && isHurtbyweapon)
		{
			StartGetDamageMS();
			HP -= 2;
			isHurtbyweapon = false;
		}
	}
	if (HP <= 0)
	{
		HP = 24;
		StartDieTime();
		simon->SetScores(2000);
		state = BOSS_STATE_DIE;
	}
}

void Boss::DeleateWaeponWhenUnactive()
{
	for (int i = 0; i < simonaxe.size(); i++)
	{
		if (simonaxe.at(i)->GetActive() == false)
		{
			simonaxe.erase(simonaxe.begin() + i);
		}
	}
	for (int i = 0; i < simondagger.size(); i++)
	{
		if (simondagger.at(i)->GetActive() == false)
		{
			simondagger.erase(simondagger.begin() + i);
		}
	}
}

void Boss::CheckCollisionSimon()
{
	if (CheckCollision(simon))
	{
		if (state == BOSS_STATE_BLOOD)
		{
			SetActive(false);
		}
		else
		{
			if (simon->GetUntouchable() == 0)
			{
				if (simon->GetOnStair() == false)
				{
					if (simon->GetHealth() <= 4)
						simon->SetLives(-1);
					simon->StartIsDamaged();
					simon->SetHealth(4);
				}
				simon->StartIsUnTouchable(SIMON_UNTOUCHABLE_TIME);
			}
		}
	}
}

void Boss::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOSS_STATE_DIE:
	case BOSS_STATE_BLOOD:
		vx = 0;
	}
}

void Boss::Render(Camera* camera)
{
	if (active == false)
		return;

	if (state == BOSS_STATE_SLEEP)
	{
		ani = BOSS_ANI_SLEEP;
	}
	else if (state == BOSS_STATE_BLOOD)
	{
		ani = BOSS_ANI_SHINING_BLOOD;
	}
	else if (state == BOSS_STATE_ATTACK || state == BOSS_STATE_FLY || BOSS_STATE_AWAKEN)
	{
		ani = BOSS_ANI_FLY;
	}
	if (die != 0)
	{
		ani = BOSS_ANI_DIE;
	}
	animations[ani]->Render(camera->transform(x, y), 255);
	RenderBoundingBox(camera);
}

void Boss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BOSS_WIDTH;
	bottom = y + BOSS_HEIGHT;
	if (state == BOSS_STATE_BLOOD)
	{
		right = x + BOSS_BLOOD_WIDTH;
		bottom = y + BOSS_BLOOD_HEIGHT;
	}
}

void Boss::CollisionOccurred(vector<LPGAMEOBJECT>* coObjects)
{
}
