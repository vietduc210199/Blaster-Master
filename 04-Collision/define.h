#pragma once
#include <fstream> 
#include <string>
#include <stdio.h>
#include <Windows.h>  
#include <iostream>
#include <map>
#include "debug.h" 
#include <algorithm>
#include <d3dx9.h>
#include <stdlib.h>
#include <iomanip>
#include <d3d9.h>
#include <vector>
#include <iostream>
#include"LoadAnimations.h"

using namespace std;


#define COLOR_BLACK D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)  
#define COLOR_KEY D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) 


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 255



#define IS_DEBUG_RENDER_BBOX isDebug_RenderBBox

#define MAX_FRAME_RATE 90

#define COLOR_BACKGROUND_DEFAULT D3DCOLOR_XRGB(0, 0, 0) // Màu đen

#define TIME_LIMIT_WAIT_RESET_GAME 300 // Thời gian chờ vẽ màn màu đen khi reset game

//Source file
#define SOURCE_ENTRANCE_PNG L"textures\\entrance_tilemap.png"
#define SOURCE_ENTRANCE_TXT "ReadFile\\Map\\entrance.txt"
#define SOURCE_CASTLE_PNG L"textures\\castle_tilemap.png"
#define SOURCE_CASTLE_TXT "ReadFile\\Map\\castle.txt"
#define SOURCE_ENTRANCE_ELEMENT_TXT "ReadFile\\SceneElement\\Scene1.txt"
#define SOURCE_CASTLE_ELEMENT_TXT "ReadFile\\SceneElement\\Scene2.txt"
#define SOURCE_TORCH_ELEMENT_TXT "ReadFile\\SceneElement\\Torch.txt"
#define SOURCE_STAGE_ENTRANCE_TXT "ReadFile\\SceneElement\\StageScene1.txt"
#define SOURCE_STAGE_CASTLE_TXT "ReadFile\\SceneElement\\StageScene2.txt"
#define SOURCE_OBJECT_SCENE1_TXT "ReadFile\\Objects\\ObjectsScene1.txt"
#define SOURCE_OBJECT_SCENE2_TXT "ReadFile\\Objects\\ObjectsScene2.txt"
#define SOURCE_PANTHER_POS_TXT "ReadFile\\Objects\\PantherPos.txt"


//SIMON
#define SIMON_JUMP_TIME             500
#define SIMON_ATTACK_TIME           300
#define SIMON_EAT_TIME              500
#define SIMON_AUTO_GO_TIME          1200
#define SIMON_AUTO_GO_SCENE1          1000
#define SIMON_UNTOUCHABLE_TIME  3000
#define	SIMON_IS_DAMAGED_TIME 450
#define SIMON_START_UNDERGROUND 1579





// ID của Sprite, object
enum eType
{
	//ngan define
	ID_TEX_SIMON = 1,
	ID_TEX_MISC = 2,
	ID_TEX_TORCH = 3,
	ID_TEX_DAGGERR = 4,
	ID_TEX_DAGGERL = 5,
	ID_TEX_LHEART = 6,
	ID_TEX_SHEART = 7,
	ID_TEX_MSUP = 8,
	ID_TEX_AXE = 9,
	ID_TEX_ENTRANCESTAGE = 10,
	ID_TEX_CASTLE = 11,
	ID_TEX_UNDERGROUND = 12,
	ID_TEX_BBOX = 13,
	ID_TEX_ENEMY = 14,

	//map
	BRICK = 0,
	BREAKABLE_BRICK = 2,
	TORCH = 1,
	STAGECHANGER = 3,

	//BRICK
	BRICK_STATE_NORMAL = - 1,
	BBRICK_STATE_MONEY_BRICK = 0,
	BBRICK_STATE_CHIKEN_BRICK = 1,
	BBRICK_STATE_DOUBLE_SHOOT_BRICK = 2,
	BBRICK_STATE_NORMAL = 3,
	BBRICK_STATE_MONEY = 4,
	BBRICK_STATE_CHIKEN = 5,
	BBRICK_STATE_DOUBLE_SHOOT = 6,

	BBRICK_ANI_BRICK = 0,
	BBRICK_ANI_CHIKEN_BRICK = 1,
	BBRICK_ANI_MONEY = 2,
	BBRICK_ANI_CHIKEN = 3,
	BBRICK_ANI_DOUBLE_SHOOT = 4,
	
	
	//
	SIMON = 01,
	SIMON_TRANS = 02,
	SIMON_DEADTH = 03,

	// object nền
	//BRICK = 21,
	TEX_BRICK_MODEL_1 = 22,
	TEX_BRICK_MODEL_2 = 23,
	TEX_BRICK_MODEL_3 = 24,
	TEX_BRICK_TRANSPARENT = 25,
	GATE = 26,
	TEX_BRICK_MODEL_3_3_32 = 27,
	TEX_BRICK_MODEL_3_4_32 = 28,

	// object
	//TORCH = 41,
	OBJECT_HIDDEN = 42,
	CANDLE = 43,
	STAIR = 44,
/*	STAIR_UP = 45,
	STAIR_EXIT = 46,*/
	STAIR_BOTTOM = 47,
	STAIR_TOP = 48,



	// weapon
	MORNINGSTAR = 61,
	DAGGER = 62,
	HOLYWATER = 63,
	STOPWATCH = 64,
	FIREBALL = 65,
	THROWINGAXE = 66,
	NON_WEAPON_COLLECT = 67,
	BOOMERANG = 68,
	WEAPON_DOUBLE_SHOT = 69,


	// item
	LARGEHEART = 81,
	UPGRADEMORNINGSTAR = 82,
	ITEMDAGGER = 83,
	BONUS = 84,
	SMALLHEART = 85,
	ITEMHOLYWATER =86,
	POTROAST = 87,
	CRYSTALBALL = 88,
	ITEMTHROWINGAXE = 89,
	INVISIBILITYPOTION = 90,
	CROSS = 91,
	ITEMBOOMERANG = 92,
	ITEMDOUBLESHOT = 93,
	MONEY_BAG_RED = 94, 
	MONEY_BAG_WHITE = 95,
	MONEY_BAG_PURPLE = 96,

	// other
	FONT = 101,
	BOARD = 102,
	BOARDHEALTH = 103,
	MAP1 = 104,
	RENDERBBOX =105,
	MAP2 = 106,
	BOARD_TRANS = 107,

	// Effect
	FIRE = 121,
	HIT = 122,
	BROKENBRICK = 123,
	STEAM = 124,
	EFFECT_MONEY_700 = 125,
	EFFECT_MONEY_100 = 126,
	EFFECT_MONEY_400 = 127,
	EFFECT_MONEY_1000 = 128,
	
	// Enemy
	GHOST = 141,
	PANTHER = 142,
	BAT = 143,
	FISHMEN = 144,

	//BOSS
	PHANTOMBAT = 161,

	// Intro
	MAINMENU = 181,
	INTRO_GO_SCENE1 = 182,
	INTRO_BAT_MENU = 183, // bat ở menu
	HELICOPTER = 184,
	INTRO_BAT = 185 // ở intro

};


 
 

typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO GVector2(0.0f, 0.0f)





#define GAMEOVER_SELECT_CONTINUE 0
#define GAMEOVER_SELECT_END 1




#ifndef CHECK_OBJECT_IN_CAMERA // Kiểm tra GameObject có nằm trong camera ko?
#define CHECK_OBJECT_IN_CAMERA(obj) \
checkObjectInCamera(obj->GetX(), obj->GetY(), (float)obj->GetWidth(),  (float)obj->GetHeight())
#endif


#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif

