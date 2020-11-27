#include "FireBullet.h"

FireBullet::~FireBullet()
{
}

void FireBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (active == false)
		return;
	CGameObject::Update(dt, coObjects);
	x += dx;
	if (nx > 0)
		vx = BULLET_SPEED;
	else vx = -BULLET_SPEED;
	for (int i = 0; i < coObjects->size(); i++)
	{
		CSimon* simon = dynamic_cast<CSimon*>(coObjects->at(i));
		if (this->CheckCollision(simon))
		{
			if (simon->GetUntouchable() == 0)
			{
				if (nx > 0)
				{
					simon->nx = -1;
				}
				else simon->nx = 1;
				if (simon->GetOnStair() == false)
				{
					simon->StartIsDamaged();
					simon->SetHealth(2);
				}
				simon->StartIsUnTouchable(SIMON_UNTOUCHABLE_TIME);
			}

		}
	}

	if (this->CheckCollision(this->MS))
	{
		this->SetActive(false);
	}
}

void FireBullet::SetState(int state)
{
	CGameObject::SetState(state);

}

void FireBullet::Render(Camera* camera)
{
	if (active != true)
		return;
	int ani;
	if (nx > 0)
		ani = 0;
	else ani = 1;
	animations[ani]->Render(camera->transform(x, y), 255);
	RenderBoundingBox(camera);
}

void FireBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SHEART_WIDTH;
	bottom = y + SHEART_HEIGHT;
}
