#include "IntroBat.h"

IntroBat::IntroBat(float X, float Y, float VX, float VY)
{
	type = eType::INTRO_BAT;
	sprite = new CSprite(eType::INTRO_BAT, 0, 0, 0, 0, TextureManager::getInstance()->getData()->Get(type), 70);

	this->x = X;
	this->y = Y;
	this->direction = -1;

	vy = VY;
	vx = VX;
}

IntroBat::~IntroBat()
{
}

void IntroBat::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
}

void IntroBat::Render(Camera* camera)
{
}

void IntroBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
