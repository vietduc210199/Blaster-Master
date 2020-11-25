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
#include"LoadAnimations.h"

using namespace std;


#define COLOR_BLACK D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)  
#define COLOR_KEY D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) 


#define SCREEN_WIDTH 280
#define SCREEN_HEIGHT 255

#define IS_DEBUG_RENDER_BBOX isDebug_RenderBBox

#define MAX_FRAME_RATE 90

#define COLOR_BACKGROUND_DEFAULT D3DCOLOR_XRGB(0, 0, 0) // Màu đen

#define TIME_LIMIT_WAIT_RESET_GAME 300 // Thời gian chờ vẽ màn màu đen khi reset game

#define CAM_MOVE_TIME1 3000
#define CAM_MOVE_TIME2 1750

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

#define GRAVITY 0.0015f

//SIMON
#define SIMON_WALKING_SPEED		    0.07f 
#define SIMON_WALKING_STAIR_SPEED		    0.03f 
#define	SIMON_AUTO_WALKING_STAIR_SPEED   0.2f
#define SIMON_JUMP_SPEED_X			0.12f
#define SIMON_JUMP_SPEED_Y		    0.22f
#define SIMON_JUMP_DEFLECT_SPEED    0.1f
#define SIMON_GRAVITY			    0.001f
#define SIMON_DIE_DEFLECT_SPEED	    0.5f
#define PULL_UP_SIMON_AFTER_SITTING 8
#define SIMON_TEX_WIDTH 39
#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_ATTACK          500
#define SIMON_STATE_SIT             600
#define SIMON_STATE_EAT_ITEM        700
#define SIMON_STATE_SIT_ATTACK      800
#define SIMON_STATE_ON_STAIR_ATTACK 101
#define SIMON_STATE_ON_STAIR_IDLE   102
#define SIMON_STATE_WALKING_UP_STAIR 103
#define SIMON_STATE_WALKING_DOWN_STAIR 104

#define SIMON_JUMP_TIME             500
#define SIMON_ATTACK_TIME           300
#define SIMON_EAT_TIME              500
#define SIMON_AUTO_GO_TIME          1200
#define SIMON_AUTO_GO_TIME_1_STAIR  400
#define SIMON_AUTO_GO_SCENE1        1000
#define SIMON_UNTOUCHABLE_TIME  3000
#define	SIMON_IS_DAMAGED_TIME 450
#define SIMON_START_UNDERGROUND 1579

#define SIMON_ANI_IDLE_RIGHT		    0
#define SIMON_ANI_IDLE_LEFT			    1
#define SIMON_ANI_WALKING_RIGHT		    2
#define SIMON_ANI_WALKING_LEFT		    3
#define SIMON_ANI_ATTACK_RIGHT		    4
#define SIMON_ANI_ATTACK_LEFT		    5
#define SIMON_ANI_JUMP_RIGHT            6
#define SIMON_ANI_JUMP_LEFT             7
#define SIMON_ANI_SIT_RIGHT             8
#define SIMON_ANI_SIT_LEFT              9
#define SIMON_ANI_EAT_RIGHT             10
#define SIMON_ANI_EAT_LEFT              11
#define SIMON_ANI_SIT_ATTACK_RIGHT      12
#define SIMON_ANI_SIT_ATTACK_LEFT       13
#define SIMON_ANI_UP_STAIR_IDLE_RIGHT   14
#define SIMON_ANI_UP_STAIR_IDLE_LEFT    15
#define SIMON_ANI_DOWN_STAIR_IDLE_RIGHT 16
#define SIMON_ANI_DOWN_STAIR_IDLE_LEFT  17
#define SIMON_ANI_WALKING_UP_STAIR_RIGHT 18
#define SIMON_ANI_WALKING_UP_STAIR_LEFT  19
#define SIMON_ANI_WALKING_DOWN_STAIR_RIGHT 20
#define SIMON_ANI_WALKING_DOWN_STAIR_LEFT 21
#define SIMON_ANI_UP_STAIR_ATTACK_RIGHT 22
#define SIMON_ANI_UP_STAIR_ATTACK_LEFT  23
#define SIMON_ANI_DOWN_STAIR_ATTACK_RIGHT 24
#define SIMON_ANI_DOWN_STAIR_ATTACK_LEFT  25
#define SIMON_ANI_IS_DAMAGED_LEFT 26
#define SIMON_ANI_IS_DAMAGED_RIGHT 27
#define SIMON_ANI_DIE		            28


#define SIMON_LEVEL_MS_1            0
#define SIMON_LEVEL_MS_2            1
#define SIMON_LEVEL_MS_3            2

//Morning Star
#define MS_ATTACK_TIME 300

#define MS_STATE_ATTACK 0
#define MS_STATE_ATTACK_2 1
#define MS_STATE_ATTACK_3 2

#define MS_LEVEL_1 0
#define MS_LEVEL_2 1
#define MS_LEVEL_3 2

#define WHIP_NORMAL_BOX_WIDTH	15
#define WHIP_NORMAL_BOX_HEIGHT	15

#define WHIP_LONG_BOX_WIDTH		18
#define WHIP_LONG_BOX_HEIGHT	15

//Wepon
   //Axe
#define AXE_WIDTH 17
#define AXE_HEIGHT 17
#define AXE_GRAVITY  0.0001
#define AXE_DROP_SPEED 0.17
#define AXE_FLY_SPEED 0.0093
#define AXE_FLY_RANGE 70
#define AXE_STATE_ATTACK 0
	//Dagger
#define DG_WIDTH 17
#define DG_HEIGHT 10
#define DG_FLY_SPEED 0.2
#define DG_STATE_ATTACK_RIGHT 0
#define DG_STATE_ATTACK_LEFT 1
//Holy Water
#define HW_FIRE_WIDTH 18
#define HW_FIRE_HEIGHT 14
#define HW_FLY_RANGE 25
#define HW_GRAVITY 0.02
#define HW_SPEED 0.1
#define HW_DROP_GRAVITY 0.14
#define HW_DROP_SPEED 0.08
#define HW_FIRE_TIME 1000
#define HW_STATE_BOTTLE 0
#define HW_STATE_FIRE 1
#define HW_ANI_BOTTLE 0
#define HW_ANI_FIRE 1

//--------------MAP------------
//brick
	//Brick
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16
#define BRICK_TYPE_NORMAL 0
#define BRICK_TYPE_GROUND 1

#define BRICK_STATE_NORMAL -1
#define BBRICK_STATE_MONEY_BRICK 0
#define BBRICK_STATE_CHIKEN_BRICK 1
#define BBRICK_STATE_DOUBLE_SHOOT_BRICK 2
#define BBRICK_STATE_NORMAL 3
#define BBRICK_STATE_MONEY 4
#define BBRICK_STATE_CHIKEN 5
#define BBRICK_STATE_DOUBLE_SHOOT 6

#define BBRICK_ANI_BRICK 0
#define BBRICK_ANI_CHIKEN_BRICK 1
#define BBRICK_ANI_MONEY 2
#define BBRICK_ANI_CHIKEN 3
#define BBRICK_ANI_DOUBLE_SHOOT 4
//Invisible Objects
#define INVI_WIDTH 10
#define INVI_HEIGHT 10
	//Stage Changer
#define SC_TYPE_CHANGE_SCENE 1006
#define SC_TYPE_DOOR 1001
#define SC_TYPE_UNDER_GROUND 1002
#define SC_TYPE_DOOR_BOSS 1003
#define SC_TYPE_AUTO_HELPER 1004
#define SC_TYPE_CHANGE_STAGE 1005
#define SC_TYPE_UNDER_TO_LAND 1007

//Stair
#define STAIR_TYPE_RIGHT_UP_HELPER 99
#define STAIR_TYPE_LEFT_UP_HELPER -99
#define STAIR_TYPE_UP_RIGHT 100
#define STAIR_TYPE_DOWN_LEFT -100
#define STAIR_TYPE_UP_LEFT 101
#define STAIR_TYPE_DOWN_RIGHT -101
//Torch
#define TORCH_STATE_NORMAL 0
#define TORCH_STATE_LHEART 1
#define TORCH_STATE_SHEART 2
#define TORCH_STATE_MSUP 3
#define TORCH_STATE_DAGGER 4
#define TORCH_STATE_AXE 5
#define TORCH_STATE_CANDLE 6
#define TORCH_STATE_HOLYWATER 7
#define TORCH_STATE_CROSS 8
#define TORCH_STATE_CLOCK 9
#define TORCH_STATE_MONEY1 10
#define TORCH_STATE_MONEY2 11
#define TORCH_STATE_MONEY3 12
#define TORCH_STATE_CHIKEN 13
#define TORCH_STATE_DOUBLE_SHOOT 14
#define TORCH_STATE_MONEY4 15
#define TORCH_STATE_INVI_POT 16
#define TORCH_STATE_INVI_POT_TORCH 17
#define TORCH_STATE_AXE_TORCH 18

#define TORCH_ANI_NORMAL 0
#define TORCH_ANI_LHEART 1
#define TORCH_ANI_SHEART 2
#define TORCH_ANI_MSUP 3
#define TORCH_ANI_DAGGER 4
#define TORCH_ANI_AXE 5
#define TORCH_ANI_CANDLE 6
#define TORCH_ANI_HOLYWATER 7
#define TORCH_ANI_CROSS 8
#define TORCH_ANI_CLOCK 9
#define TORCH_ANI_MONEY1 10
#define TORCH_ANI_MONEY2 11
#define TORCH_ANI_MONEY3 12
#define TORCH_ANI_DESTROYED 13
#define TORCH_ANI_CHIKEN 14
#define TORCH_ANI_DOUBLE_SHOOT 15
#define TORCH_ANI_MONEY4 16
#define TORCH_ANI_INVI_POT 17

//Enemy
#define BOSS 2005
#define GHOUL 2000
#define PANTHER 2001
#define BAT 2002
#define FISHMAN 2003
#define FIREBULLET 2004

#define ENEMY_DIE_TIME 200
#define ENEMY_SHEART_RANGE 15
#define ENEMY_SHEART_SPEED -0.05f

#define ENEMY_STATE_MOVING 0
#define ENEMY_STATE_DIE 1
#define ENEMY_STATE_IDLE 2
#define ENEMY_STATE_SHEART 3
#define ENEMY_STATE_JUMPING 4
#define ENEMY_STATE_FALLING 5
#define ENEMY_STATE_ATTACK 6


   //Effect
#define EFFECT_TYPE_DOOR 1
#define EFFECT_TYPE_WATER 2
#define EFFECT_TYPE_BRICK 3
#define EFFECT_ANI_DOOR 0
#define EFFECT_ANI_WATER 2
#define EFFECT_ANI_BRICK 1

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

	
	
	
	//
	simon = 01,
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
	/*GHOST = 141,
	PANTHER = 142,
	BAT = 143,
	FISHMEN = 144,*/

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

