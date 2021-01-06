#pragma once
#include"Scene.h"
#include"SceneGame.h"
#include "camera.h"
#include "Simon.h"
#include "TextureManager.h"
#include"Board.h"
#include"IntroBat.h"
#include"HeliCopter.h"

#define INTRO_STATUS_PROCESS_MENU 0 
#define INTRO_STATUS_PROCESS_GO_SCENE1 1 

#define INTRO_SIMON_WALKING_SPEED 0.08f

class IntroScene : public Scene
{
private:
	Font textPressToStart;
	TextureManager *_textureManager;
	CSprite* sprite_MainMenu;
	CSprite* sprite_IntroBatMenu;

	/*Xử lí nhấn phím thì tiếp tục*/
	bool isPressStart;
	DWORD TimeWaited;

	/* Xử lí nhấp nháy TextPressStart */
	bool isDrawTextPressStart;
	DWORD TimeWaitedToChangeDisplayTextPressStart;

	int StatusProcess;

	CSimon* simon;
	Board* board;
	CSprite* Sprite_IntroGoScene1;
	Camera* camera;

	CBrick* brick;
	vector<LPGAMEOBJECT> listBrick;


	HeliCopter* heliCopter;
	IntroBat* introBat1;
	IntroBat* introBat2;
public:
	IntroScene();
	virtual ~IntroScene();

	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources(LPCWSTR picturePath, int idTex, const char* filepath, int scene);
	void Update(DWORD dt);
	void Render();
};

