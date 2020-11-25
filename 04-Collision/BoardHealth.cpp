#include "BoardHealth.h"

BoardHealth::BoardHealth(float X, float Y)
{
	_Texture = TextureManager::getInstance()->getData()->Get(eType::BOARDHEALTH);
	_Sprite = new CSprite(eType::BOARDHEALTH, 0, 0, 18, 10, _Texture);
	this->x = X;
	this->y = Y;
}

BoardHealth::~BoardHealth()
{
	SAFE_DELETE(_Sprite);
}

void BoardHealth::Draw(int HealthPlayer, int HealthEnemy)
{
	HealthPlayer = min(HealthPlayer, 16);
	HealthEnemy = min(HealthEnemy, 16);

	int i, j;
	_Sprite->SelectFrame(BOARDHEALTH_FRAME_PLAYER);
	for (i = 0; i < HealthPlayer; i++)
		_Sprite->DrawFrame(_Sprite->GetCurrentFrame(),x + i * (18/3), y, 3, 18 /3, 10);

	_Sprite->SelectFrame(BOARDHEALTH_FRAME_NONE);
	for (j = i; j < BOARDHEALTH_MAX_CELL; j++)
	{
		_Sprite->DrawFrame(_Sprite->GetCurrentFrame(), x + j * (18 /3), y, 3, (18 / 3), 10);
	}

	_Sprite->SelectFrame(BOARDHEALTH_FRAME_ENEMY);
	for (i = 0; i < HealthEnemy; i++)
		_Sprite->DrawFrame(_Sprite->GetCurrentFrame(),x + i * (18 /3), y + 10, 3, (18 / 3), 10);

	_Sprite->SelectFrame(BOARDHEALTH_FRAME_NONE);
	for (j = i; j < BOARDHEALTH_MAX_CELL; j++)
	{
		_Sprite->DrawFrame(_Sprite->GetCurrentFrame(), x + j * (18 /3), y + 10, 3, (18 / 3), 10);
	}

}
