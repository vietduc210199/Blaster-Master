#include "IntroBat.h"

IntroBat::IntroBat(float X, float Y, float VX, float VY)
{
	type = eType::INTRO_BAT;
	sprite = new CSprite(eType::INTRO_BAT, 0, 0, 16, 8, TextureManager::getInstance()->getData()->Get(type), 70, 2, 2);

	this->x = X;
	this->y = Y;
	this->direction = -1;

	this->vy = VY;
	this->vx = VX;
}

IntroBat::~IntroBat()
{
}

void IntroBat::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	CGameObject::Update(dt); // Update dt, dx, dy
	y += dy;
	x += dx;

	sprite->Update(dt);
}

void IntroBat::Render(Camera* camera)
{
	D3DXVECTOR2 pos = camera->transform(x, y);
	if (direction == -1)
		sprite->DrawFrame(sprite->GetCurrentFrame(), pos.x, pos.y, 2, sprite->GetFrameWidth(), sprite->GetFrameHeight());
}

void IntroBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
