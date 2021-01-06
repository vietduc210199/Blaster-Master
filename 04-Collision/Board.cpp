
#include "Board.h"

string Board::FillNumber(string s, UINT MaxNumber)
{
	while (s.size() < MaxNumber)
		s = "0" + s;
	return s;
}

Board::Board(float X, float Y)
{
	_Texture = TextureManager::getInstance()->getData()->Get(eType::BOARD);
	_Sprite = new CSprite(eType::BOARD, 0, 0, 273, 42, _Texture, 100);

	_spriteIconDoubleShot = new CSprite(eType::ITEMDOUBLESHOT, 0, 0, 28, 28, TextureManager::getInstance()->getData()->Get(eType::ITEMDOUBLESHOT), 100);

	x = X;
	y = Y;

	_boardHealth = new BoardHealth(x + 55, y + 17);
}

void Board::Render(CSimon* simon, int state, int RemainingTime, Boss* boss)
{
	_Sprite->Draw(x, y);
	_font.Draw(x + 55, y + 6, FillNumber(std::to_string(simon->GetScore()), 6));

	_font.Draw(x + 154, y + 6, FillNumber(std::to_string(RemainingTime), 4));

	_font.Draw(x + 245, y + 6, FillNumber(std::to_string(state), 2));

	_font.Draw(x + 210, y + 18, FillNumber(std::to_string(simon->GetHeartCollect()), 2)); // Số lượng tim nhặt dc
	_font.Draw(x + 210, y + 28, FillNumber(std::to_string(simon->GetLives()), 2)); // số mạng sông

	int BloodBoss = 16;

	if (boss != NULL)
	{
		BloodBoss = (int)(boss->GetHealth() * 16 / 24);// HEALTH =24 -> 16 vạch
		if (BloodBoss == 0 && boss->GetHealth() > 0)
			BloodBoss = 1;
	}

	_boardHealth->Draw(simon->GetHealth(), BloodBoss);
	eType TypeWeaponCollect = simon->GetTypeWeaponCollect();
	switch (TypeWeaponCollect)
	{
	case eType::DAGGER:
		_spriteWeapon = new CSprite(eType::DAGGER, 0, 0, 20, 11, TextureManager::getInstance()->getData()->Get(eType::DAGGER), 100);
		_spriteWeapon->Draw(x + 162, y + 19);
		break;
	case eType::HOLYWATER:
		_spriteWeapon = new CSprite(eType::HOLYWATER, 0, 0, 16, 16, TextureManager::getInstance()->getData()->Get(eType::HOLYWATER), 100);
		_spriteWeapon->Draw(x + 164, y + 18);
		break;
	
	case eType::THROWINGAXE:
		_spriteWeapon = new CSprite(eType::THROWINGAXE, 0, 0, 16, 15, TextureManager::getInstance()->getData()->Get(eType::THROWINGAXE), 100);
		_spriteWeapon->Draw(x + 163, y + 18);
		break;
	default:
		break;
	}

	/*if (simon->GetIsUseDoubleShot())
	{
		_spriteIconDoubleShot->Draw(x + 465, y + 35);
	}*/
}

Board::~Board()
{
	SAFE_DELETE(_Sprite);
}

void Board::SetTexture(LPDIRECT3DTEXTURE9* tex)
{
	
}
