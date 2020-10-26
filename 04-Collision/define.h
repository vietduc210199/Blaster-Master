﻿#pragma once
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

using namespace std;


#define COLOR_BLACK D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)  
#define COLOR_KEY D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) 


#define SCREEN_WIDTH 326
#define SCREEN_HEIGHT 230 


#define IS_DEBUG_RENDER_BBOX isDebug_RenderBBox

#define MAX_FRAME_RATE 90

#define COLOR_BACKGROUND_DEFAULT D3DCOLOR_XRGB(0, 0, 0) // Màu đen

#define TIME_LIMIT_WAIT_RESET_GAME 300 // Thời gian chờ vẽ màn màu đen khi reset game

// ID của Sprite, object
enum eType
{
	SIMON = 01,
	SIMON_TRANS = 02,
	SIMON_DEADTH = 03,

	// object nền
	BRICK = 21,
	TEX_BRICK_MODEL_1 = 22,
	TEX_BRICK_MODEL_2 = 23,
	TEX_BRICK_MODEL_3 = 24,
	TEX_BRICK_TRANSPARENT = 25,
	GATE = 26,
	TEX_BRICK_MODEL_3_3_32 = 27,
	TEX_BRICK_MODEL_3_4_32 = 28,

	// object
	TORCH = 41,
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
		ITEMHOLYWATER = 86,
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
		RENDERBBOX = 105,
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

