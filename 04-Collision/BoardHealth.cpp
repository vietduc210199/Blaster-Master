#include "BoardHealth.h"

BoardHealth::BoardHealth(float X, float Y)
{
	_Texture = TextureManager::getInstance()->getData()->Get(eType::BOARDHEALTH);
	_Sprite = new CSprite(eType::BOARDHEALTH, 0, 0, 33, 18, _Texture);
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
		_Sprite->DrawFrame(_Sprite->GetCurrentFrame(),x + i * 11, y, 1, 11, 18);

	_Sprite->SelectFrame(BOARDHEALTH_FRAME_NONE);
	for (j = i; j < BOARDHEALTH_MAX_CELL; j++)
	{
		_Sprite->DrawFrame(_Sprite->GetCurrentFrame(), x + j * 11, y, 1, 11, 18);
	}

	_Sprite->SelectFrame(BOARDHEALTH_FRAME_ENEMY);
	for (i = 0; i < HealthEnemy; i++)
		_Sprite->DrawFrame(_Sprite->GetCurrentFrame(),x + i * 11, y + 18, 1, 11, 18);

	_Sprite->SelectFrame(BOARDHEALTH_FRAME_NONE);
	for (j = i; j < BOARDHEALTH_MAX_CELL; j++)
	{
		_Sprite->DrawFrame(_Sprite->GetCurrentFrame(), x + j * 11, y + 18, 1, 11, 18);
	}

}
