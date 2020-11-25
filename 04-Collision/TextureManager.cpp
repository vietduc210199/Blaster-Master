#include "TextureManager.h"


TextureManager* TextureManager::__instance = NULL;



void TextureManager::LoadResources()
{
	
	TexList->Add(ID_TEX_ENTRANCESTAGE, L"textures\\entrance.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::ID_TEX_SIMON, L"textures\\Simon.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::ID_TEX_DAGGERR, L"textures\\item.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::ID_TEX_DAGGERL, L"textures\\item.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::ID_TEX_LHEART, L"textures\\item.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::ID_TEX_SHEART, L"textures\\item.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::ID_TEX_MSUP, L"textures\\item.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::ID_TEX_AXE, L"textures\\item.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::ID_TEX_TORCH, L"textures\\object.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::ID_TEX_MISC, L"textures\\object.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	TexList->Add(eType::ID_TEX_ENEMY, L"textures\\enemy.png", D3DCOLOR_XRGB(255, 0, 255));

	//Board
	TexList->Add(eType::BOARD, L"Resources/blackboard.png", D3DCOLOR_XRGB(1, 1, 1));
	TexList->Add(eType::FONT, L"textures\\font\\1.png", D3DCOLOR_XRGB(13, 3, 37));
	TexList->Add(eType::BOARDHEALTH, L"textures\\heal.png", D3DCOLOR_XRGB(3, 1, 3));


	//item
	TexList->Add(eType::ITEMDOUBLESHOT, L"textures\\item\\11.png", D3DCOLOR_XRGB(0, 0, 0));
}




