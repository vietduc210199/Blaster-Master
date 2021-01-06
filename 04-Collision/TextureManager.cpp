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
	TexList->Add(eType::BOARD, L"textures\\blackboard.png", D3DCOLOR_XRGB(0, 0, 0));
	TexList->Add(eType::FONT, L"textures\\font\\1.png", D3DCOLOR_XRGB(0, 0, 0));
	TexList->Add(eType::BOARDHEALTH, L"textures\\heal.png", D3DCOLOR_XRGB(0, 0, 0));


	//item
	TexList->Add(eType::ITEMDOUBLESHOT, L"textures\\item\\11.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::DAGGER, L"textures\\item\\4.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::THROWINGAXE, L"textures\\item\\7.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::HOLYWATER, L"textures\\item\\9.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::BOOMERANG, L"textures\\item\\8.png", D3DCOLOR_XRGB(255, 0, 255));

	//Intro Scene
	TexList->Add(eType::MAINMENU, L"textures\\Intro\\mainmenu.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::INTRO_BAT, L"textures\\Intro\\intro_bat.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::INTRO_BAT_MENU, L"textures\\Intro\\IntroBatMenu.png", D3DCOLOR_XRGB(0, 0, 0));
	TexList->Add(eType::INTRO_GO_SCENE1, L"textures\\Intro\\intro_go_scene_1.png", D3DCOLOR_XRGB(255, 0, 255));
	TexList->Add(eType::HELICOPTER, L"textures\\Intro\\helicopter.png", D3DCOLOR_XRGB(255, 0, 255));

}




