#include "TextureManager.h"


TextureManager* TextureManager::__instance = NULL;

void TextureManager::LoadTexture()
{
	TexList->Add(ID_TEX_SIMON, L"textures\\Simon.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(ID_TEX_TORCH, L"textures\\object.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(ID_TEX_MISC, L"textures\\brick1.png", D3DCOLOR_XRGB(0, 0, 0));
	TexList->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	TexList->Add(ID_TEX_ENTRANCESTAGE, L"textures\\entrance.png", D3DCOLOR_XRGB(255, 255, 255));
	TexList->Add(ID_TEX_ENTRANCESTAGE, L"textures\\entrance.png", D3DCOLOR_XRGB(255, 255, 255));

	TexList->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));


}