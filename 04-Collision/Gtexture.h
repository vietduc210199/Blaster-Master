#pragma once
#include "Sprites.h"
#include"Textures.h"
#include <d3dx9.h>

class Gtexture
{
private:
	LPDIRECT3DTEXTURE9 _texture;
	int totalFrame;
	int currentFrame;
	int collum;
	int row;
	float frameWidth;
	float frameHeight;
public:
	Gtexture(LPDIRECT3DTEXTURE9 _texture, int totalFrame, int collum, int row);
	~Gtexture();
};

