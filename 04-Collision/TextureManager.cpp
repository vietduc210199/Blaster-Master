#include "TextureManager.h"


TextureManager* TextureManager::__instance = NULL;



void TextureManager::LoadResources()
{
	//TexList->Add(ID_TEX_SIMON, L"textures\\Simon.png", D3DCOLOR_XRGB(255, 0, 255));
	//TexList->Add(ID_TEX_TORCH, L"textures\\object.png", D3DCOLOR_XRGB(255, 0, 255));
	//TexList->Add(ID_TEX_MISC, L"textures\\brick1.png", D3DCOLOR_XRGB(0, 0, 0));
	//TexList->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	TexList->Add(ID_TEX_ENTRANCESTAGE, L"textures\\entrance.png", D3DCOLOR_XRGB(255, 0, 255));

	//TexList->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	//// Intro
	//TexList->Add(eType::MAINMENU, L"textures\\mainmenu.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::INTRO_BAT, L"textures\\intro_bat.png", D3DCOLOR_XRGB(2, 1, 2));
	//TexList->Add(eType::INTRO_BAT_MENU, L"textures\\IntroBatMenu.png", D3DCOLOR_XRGB(5, 3, 15));
	//TexList->Add(eType::INTRO_GO_SCENE1, L"textures\\intro_go_scene_1.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::HELICOPTER, L"textures\\helicopter.png", COLOR_BACKGROUND_DEFAULT);

	////board
	//TexList->Add(eType::FONT, L"textures\\font\\1.png", D3DCOLOR_XRGB(13, 3, 37));

	//TexList->Add(eType::BOARD, L"textures\\blackboard.png", D3DCOLOR_XRGB(1, 1, 1));
	////TexList->Add(eType::BOARD_TRANS, L"textures\\blackboard.png", 1, 1, 1, 0, 0, 0));
	//TexList->Add(eType::BOARD_TRANS, L"textures\\blackboard.png", COLOR_BACKGROUND_DEFAULT);

	//TexList->Add(eType::BOARDHEALTH, L"textures\\heal.png", D3DCOLOR_XRGB(3, 1, 3));
	//TexList->Add(eType::RENDERBBOX, L"textures\\bbox.png", COLOR_BACKGROUND_DEFAULT); // dùng để vẽ BBOX

	////MAP
	//TexList->Add(eType::MAP1, L"textures\\map\\tileset_map1.png", D3DCOLOR_XRGB(8, 4, 32));
	//TexList->Add(eType::MAP2, L"textures\\map\\tileset_map2.png", D3DCOLOR_XRGB(22, 4, 88));


	////gameobject ground
	//TexList->Add(eType::TEX_BRICK_MODEL_1, L"textures\\ground\\2.png", COLOR_BACKGROUND_DEFAULT); // loại dành cho state 1
	//TexList->Add(eType::TEX_BRICK_MODEL_2, L"textures\\ground\\2-2.png", COLOR_BACKGROUND_DEFAULT); // dành cho state 2
	//TexList->Add(eType::TEX_BRICK_MODEL_3, L"textures\\ground\\8.png", COLOR_BACKGROUND_DEFAULT); // loại nhỏ
	//TexList->Add(eType::TEX_BRICK_TRANSPARENT, L"textures\\ground\\brick_transparent.png", COLOR_BACKGROUND_DEFAULT); // loại trong suốt

	//TexList->Add(eType::TEX_BRICK_MODEL_3_3_32, L"textures\\ground\\8-2.png", COLOR_BACKGROUND_DEFAULT); // loại nhỏ 4 ô
	//TexList->Add(eType::TEX_BRICK_MODEL_3_4_32, L"textures\\ground\\8-1.png", COLOR_BACKGROUND_DEFAULT); // loại nhỏ 4 ô



	//TexList->Add(eType::GATE, L"textures\\ground\\Gate1.png", D3DCOLOR_XRGB(4, 1, 4));

	//TexList->Add(eType::TORCH, L"textures\\object.png", D3DCOLOR_XRGB(255, 0 ,255));
	//TexList->Add(eType::CANDLE, L"textures\\ground\\1.png", D3DCOLOR_XRGB(2, 1, 2));

	////item
	//TexList->Add(eType::ITEMDAGGER, L"textures\\item\\4.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::LARGEHEART, L"textures\\item\\1.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::UPGRADEMORNINGSTAR, L"textures\\item\\3.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::BONUS, L"textures\\item\\2.png", D3DCOLOR_XRGB(3, 1, 3));
	//TexList->Add(eType::SMALLHEART, L"textures\\item\\0.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::ITEMHOLYWATER, L"textures\\item\\9.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::POTROAST, L"textures\\item\\10.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::CRYSTALBALL, L"textures\\item\\13.png", D3DCOLOR_XRGB(2, 1, 2));
	//TexList->Add(eType::ITEMTHROWINGAXE, L"textures\\item\\7.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::INVISIBILITYPOTION, L"textures\\item\\14.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::CROSS, L"textures\\item\\6.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::ITEMBOOMERANG, L"textures\\item\\8.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::ITEMDOUBLESHOT, L"textures\\item\\11.png", COLOR_BACKGROUND_DEFAULT);




	//// Weapon
	//TexList->Add(eType::DAGGER, L"textures\\weapon\\1.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::MORNINGSTAR, L"textures\\weapon\\morningstar.png", D3DCOLOR_XRGB(4, 3, 12));
	//TexList->Add(eType::HOLYWATER, L"textures\\weapon\\2.png", D3DCOLOR_XRGB(4, 1, 4));
	//TexList->Add(eType::STOPWATCH, L"textures\\item\\5.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::FIREBALL, L"textures\\weapon\\fireball.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::THROWINGAXE, L"textures\\weapon\\3.png", D3DCOLOR_XRGB(4, 1, 4));
	//TexList->Add(eType::BOOMERANG, L"textures\\weapon\\4.png", D3DCOLOR_XRGB(3, 1, 3));


	////player
	//TexList->Add(eType::SIMON, L"textures\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	//TexList->Add(eType::SIMON_TRANS, L"textures\\simon_trans.png", D3DCOLOR_XRGB(255, 0, 255));
	//TexList->Add(eType::SIMON_DEADTH, L"textures\\simondeath.png", COLOR_BACKGROUND_DEFAULT);

	////effect
	//TexList->Add(eType::FIRE, L"textures\\other\\1.png", D3DCOLOR_XRGB(4, 1, 4));
	//TexList->Add(eType::HIT, L"textures\\other\\0.png", D3DCOLOR_XRGB(2, 1, 2));
	//TexList->Add(eType::BROKENBRICK, L"textures\\other\\BrokenBrick.png", D3DCOLOR_XRGB(2, 1, 2));//, 4,4,16));
	//TexList->Add(eType::STEAM, L"textures\\other\\2.png", COLOR_BACKGROUND_DEFAULT);
	//TexList->Add(eType::EFFECT_MONEY_700, L"textures\\other\\effect700.png", D3DCOLOR_XRGB(2, 1, 2));
	//TexList->Add(eType::EFFECT_MONEY_100, L"textures\\other\\effect100.png", D3DCOLOR_XRGB(2, 1, 2));
	//TexList->Add(eType::EFFECT_MONEY_1000, L"textures\\other\\effect1000.png", D3DCOLOR_XRGB(2, 1, 2));
	//TexList->Add(eType::EFFECT_MONEY_400, L"textures\\other\\effect400.png", D3DCOLOR_XRGB(2, 1, 2));



	////enemy
	//TexList->Add(eType::GHOST, L"textures\\enemy\\1.png", D3DCOLOR_XRGB(2, 1, 2));
	//TexList->Add(eType::PANTHER, L"textures\\enemy\\2.png", D3DCOLOR_XRGB(4, 1, 4));


	//TexList->Add(eType::BAT, L"textures\\enemy\\0.png", D3DCOLOR_XRGB(4, 1, 4));
	//TexList->Add(eType::FISHMEN, L"textures\\enemy\\3.png", D3DCOLOR_XRGB(3, 1, 3));


	////boss
	//TexList->Add(eType::PHANTOMBAT, L"textures\\boss\\0.png", D3DCOLOR_XRGB(3, 1, 3));



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

}




