
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
	_Sprite = new CSprite(eType::BOARD, 0, 0, 520, 80, _Texture);

	_spriteIconDoubleShot = new CSprite(eType::ITEMDOUBLESHOT, 0, 0, 28, 28, TextureManager::getInstance()->getData()->Get(eType::ITEMDOUBLESHOT));

	x = X;
	y = Y;

	_boardHealth = new BoardHealth(x + 110, y + 30);
}

void Board::Render(CSimon* simon, int state, int RemainingTime, CGameObject* boss)
{
	_Sprite->Draw(x, y);
	//_font.Draw(x + 100, y + 15, FillNumber(std::to_string(simon->GetScore()), 6));

	_font.Draw(x + 295, y + 15, FillNumber(std::to_string(RemainingTime), 4));

	_font.Draw(x + 465, y + 15, FillNumber(std::to_string(state), 2));

	//_font.Draw(x + 393, y + 33, FillNumber(std::to_string(simon->GetHeartCollect()), 2)); // Số lượng tim nhặt dc
	//_font.Draw(x + 393, y + 51, FillNumber(std::to_string(simon->GetLives()), 2)); // số mạng sông

	int BloodBoss = 16;

	//if (boss != NULL)
	//{
	//	BloodBoss = (int)(boss->GetHealth() * 16 / 24);// HEALTH =24 -> 16 vạch
	//	if (BloodBoss == 0 && boss->GetHealth() > 0)
	//		BloodBoss = 1;
	//}

	_boardHealth->Draw(simon->GetHealth(), BloodBoss);
}

Board::~Board()
{
}

void Board::SetTexture(LPDIRECT3DTEXTURE9* tex)
{
}
