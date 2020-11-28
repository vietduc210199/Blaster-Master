#include "Ghoul.h"
#include "Brick.h"

Ghoul::~Ghoul()
{
}

void Ghoul::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ENEMY_STATE_IDLE:
		vx = 0;
		break;
	}
}

void Ghoul::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (active == false)
		return;
	CGameObject::Update(dt, coObjects);
	vy = GRAVITY * dt;
	
	
	if (state != ENEMY_STATE_MOVING && die != 0)
	{
		vy = GRAVITY * 2 * dt;
		if (isOnGround == false)
		{
			if (vx < 0 && x < FirstX - ENEMY_SHEART_RANGE)
			{
				x = FirstX - ENEMY_SHEART_RANGE; vx = -vx;
			}
			else if (vx > 0 && x > FirstX + ENEMY_SHEART_RANGE)
			{
				x = FirstX + ENEMY_SHEART_RANGE; vx = -vx;
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
					vx = -ENEMY_SHEART_SPEED;
				}
			}
			else vx = 0;
		}
		
	}
	else if (state == ENEMY_STATE_MOVING)
	{

		if (isStop == false)
		{
			if (nx > 0)
				vx = GHOUL_SPEED;
			else vx = -GHOUL_SPEED;
		}
	}
	if (GetTickCount() - dietime_start > ENEMY_DIE_TIME)
	{
		dietime_start = 0;
		die = 0;
		if (just_die == 1)
			this->SetActive(false);
	}
	Collision(coObjects);
}

void Ghoul::Render(Camera* camera)
{
	if (active != true)
		return;
	int ani = 0;
	if (state == ENEMY_STATE_MOVING)
	{
		if (nx > 0)
		{
			ani = GHOUL_ANI_WALKING_RIGHT;
		}
		else ani = GHOUL_ANI_WALKING_LEFT;
	}
	else if (state == ENEMY_STATE_SHEART)
	{
		ani = GHOUL_ANI_SHEART;
	}
	else if (state == ENEMY_STATE_DAGGER)
	{
		ani = ENEMY_ANI_DAGGER;
	}
	else if (state == ENEMY_STATE_AXE)
	{
		ani = ENEMY_ANI_AXE;
	}
	else if (state == ENEMY_STATE_HOLYWATER)
	{
		ani = ENEMY_ANI_HOLYWATER;
	}
	else if (state == ENEMY_STATE_MONEY1)
	{
		ani = ENEMY_ANI_MONEY1;
	}
	else if (state == ENEMY_STATE_MONEY2)
	{
		ani = ENEMY_ANI_MONEY2;
	}
	else if (state == ENEMY_STATE_MONEY3)
	{
		ani = ENEMY_ANI_MONEY3;
	}
	else if (state == ENEMY_STATE_MONEY4)
	{
		ani = ENEMY_ANI_MONEY4;
	}
	if (die != 0)
	{
		ani = GHOUL_ANI_DIE;
	}
	animations[ani]->Render(camera->transform(x, y), 255);
	RenderBoundingBox(camera);
}


void Ghoul::CollisionOccurred(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];

		if (dynamic_cast<CBrick*>(e->obj))
		{
			CBrick* brick = dynamic_cast<CBrick*>(e->obj);
			if (e->nx < 0)
			{
				this->nx = -1;
			}
			if (e->nx > 0)
			{
				this->nx = 1;
			}
		}
	}
	if (!isStop)
		x += dx;
}

void Ghoul::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GHOUL_BOX_WIDTH;
	bottom = y + GHOUL_BOX_HEIGHT;
	if(state == ENEMY_STATE_MONEY1
		|| state == ENEMY_STATE_MONEY2
		|| state == ENEMY_STATE_MONEY3
		|| state == ENEMY_STATE_MONEY4)
	{
		right = x + MONEY_WIDTH;
		bottom = y + MONEY_HEIGHT;
	}
	else if (state == ENEMY_STATE_SHEART)
	{
		right = x + SHEART_WIDTH;
		bottom = y + SHEART_HEIGHT;
	}
	else if (state == ENEMY_STATE_DAGGER)
	{
		right = x + DAGGER_WIDTH;
		bottom = y + DAGGER_HEIGHT;
	} 
	else if (state != ENEMY_STATE_MOVING)
	{
		right = x + OTHER_WIDTH;
		bottom = y + OTHER_HEIGHT;
	}
}