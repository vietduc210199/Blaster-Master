#pragma once
#include "define.h"
#include "Font.h"
#include "BoardHealth.h"
#include "camera.h"
#include "Simon.h"
#include "TextureManager.h"


#define BOARD_DEFAULT_POSITION_X 0.0f
#define BOARD_DEFAULT_POSITION_Y 0.0f
class Board
{
private:
	Font _font;
	BoardHealth* _boardHealth;

	LPDIRECT3DTEXTURE9 _Texture;
	CSprite* _Sprite;
	float x, y;

	string FillNumber(string s, UINT MaxNumber);


	CSprite* _spriteIconDoubleShot;
	CSprite* _spriteWeapon;
public:
	Board(float X, float Y);
	void Render(CSimon* simon, int state, int RemainingTime, CGameObject* boss);
	~Board();

	void SetTexture(LPDIRECT3DTEXTURE9* tex);
};

