#include "HeliCopter.h"

HeliCopter::HeliCopter(float X, float Y)
{
	type = eType::HELICOPTER;
	sprite = new CSprite(eType::HELICOPTER, 0, 0, 32, 14, TextureManager::getInstance()->getData()->Get(type), 70);

	this->x = X;
	this->y = Y;
	this->direction = -1;

	vy = -HELICOPTER_SPEED_Y;
	vx = HELICOPTER_SPEED_X * direction;
}

HeliCopter::~HeliCopter()
{
}

void HeliCopter::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	CGameObject::Update(dt); // Update dt, dx, dy

	y += dy;
	x += dx;
}

void HeliCopter::Render(Camera* camera)
{
	D3DXVECTOR2 pos = camera->transform(x, y);
	if (direction == -1)
		sprite->Draw(pos.x, pos.y);

}

void HeliCopter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
