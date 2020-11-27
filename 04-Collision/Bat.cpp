#include "Bat.h"

Bat::~Bat()
{
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (active == false)
		return;
	CGameObject::Update(dt, coObjects);

	if (state == ENEMY_STATE_SHEART)
	{
		Collision(coObjects);
	}
	if (GetTickCount() - dietime_start > ENEMY_DIE_TIME)
	{
		dietime_start = 0;
		die = 0;
	}
	if (state != ENEMY_STATE_MOVING && die == 0)
	{
		state = ENEMY_STATE_SHEART;
	}	
	if (state == ENEMY_STATE_MOVING)
	{
		if (isStop)
			return;
		if (nx > 0)
			x += dx;
		else
			x -= dx;

		y += dy;
		if (vy < 0 && y < FirstY)
		{
			y = FirstY; vy = -vy;
		}

		if (vy > 0 && y > FirstY + 20)
		{
			y = FirstY + 20; vy = -vy;
		}
	}
	if (state == ENEMY_STATE_SHEART)
	{
		if (isOnGround == false)
		{
			if (vx < 0 && x < FirstX - ENEMY_SHEART_RANGE)
			{
				x = FirstX - ENEMY_SHEART_RANGE; vx = -vx;
			}

			if (vx > 0 && x > FirstX + ENEMY_SHEART_RANGE)
			{
				x = FirstX + ENEMY_SHEART_RANGE; vx = -vx;
			}
			vy = GRAVITY * dt;
			vx = ENEMY_SHEART_SPEED;
		}
	}
}

void Bat::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ENEMY_STATE_IDLE:
		vx = 0;
		break;
	}
}
void Bat::Render(Camera* camera)
{
	if (active != true)
		return;
	int ani = 0;
	if (state == ENEMY_STATE_MOVING)
	{
		if (nx > 0)
		{
			ani = BAT_ANI_FLYING_RIGHT;
		}
		else ani = BAT_ANI_FLYING_LEFT;
	}
	else if (state == ENEMY_STATE_SHEART)
	{
		ani = BAT_ANI_SHEART;
	}
	if (die != 0)
	{
		ani = BAT_ANI_DIE;
	}
	animations[ani]->Render(camera->transform(x, y), 255);
	RenderBoundingBox(camera);
}

void Bat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void Bat::CollisionOccurred(vector<LPGAMEOBJECT>* coObjects)
{
	if (!isStop)
		x += dx;
}
