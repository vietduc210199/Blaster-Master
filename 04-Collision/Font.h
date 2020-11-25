#pragma once
#include "define.h"
#include "TextureManager.h"
class Font
{
private:
	LPDIRECT3DTEXTURE9 _Texture;
	CSprite* _Sprite;
public:
	Font();
	~Font();
	void Draw(float x, float y, const string& s);
};

