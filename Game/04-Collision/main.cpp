/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions:
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox

================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "SIMON.h"
#include "MS.h"
#include "Torch.h"
#include "Brick.h"

#include "TextureManager.h"
#include "SpritesManager.h"
#include "AnimationsManager.h"

#include<iostream>
#include<fstream>
#include<string>
#include<queue>

#define WINDOW_CLASS_NAME L"Castlevania"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 450
#define SCREEN_HEIGHT 230

#define MAX_FRAME_RATE 120

CGame * game;

CSimon* SIMON;
CMS* MS;

vector<LPGAMEOBJECT> objects;

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander* keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		SIMON->SetState(SIMON_STATE_JUMP);
		SIMON->StartJump();
		break;
	case DIK_A:
		if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))
		{
			return;
		}
		MS->StartAttack();
		MS->SetState(WHIP_STATE_ATTACK);
		MS->SetActive(true);
		SIMON->SetState(SIMON_STATE_ATTACK);
		SIMON->StartAttack();
		break;
	case DIK_Q:
		if (SIMON->GetActive() == true)
		{
			SIMON->SetActive(false);
		}
		else SIMON->SetActive(true);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	if (KeyCode == 208) {
		SIMON->StandUp();
	}
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE* states)
{
	// disable control key when SIMON die 
	if (SIMON->GetState() == SIMON_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
	{
		SIMON->SetState(SIMON_STATE_WALKING_RIGHT);
		SIMON->SetRight(1);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		SIMON->SetState(SIMON_STATE_WALKING_LEFT);
		SIMON->SetRight(0);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		SIMON->SetState(SIMON_STATE_SIT);
		/*SIMON->Sit();*/
		SIMON->SetSit(true);
	}
	//else if(game->IsKeyDown())
	else
		SIMON->SetState(SIMON_STATE_IDLE);
	

}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and SIMON object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	AnimationsManager* animations = animations->getInstance();
	
	SIMON = new CSimon();

	SIMON->AddAnimation(400);	// idle right 
	SIMON->AddAnimation(401);	// idle left 
    SIMON->AddAnimation(500);	// walk right 
	SIMON->AddAnimation(501);	// walk left 
	SIMON->AddAnimation(402);	//attack right
	SIMON->AddAnimation(502);	//attack left
	SIMON->AddAnimation(403);	//jump right
	SIMON->AddAnimation(503);	//jump left
	SIMON->AddAnimation(404);	//sit right
	SIMON->AddAnimation(504);	//sit left

    SIMON->SetPosition(50.0f, 0);
	

	MS = new CMS();
	MS->GetSimon(SIMON);
	MS->AddAnimation(600);
	MS->AddAnimation(601);
	

	/*SIMON->SetMS(MS);*/
	for (int i = 0; i < 4; i++)
	{
		CTorch* torch = new CTorch();
		torch->AddAnimation(1001);
		torch->SetPosition(150 + i * 150.0f, 130);
		objects.push_back(torch);
		if (SIMON->CheckCollision(torch))
		{
			torch->SetActive(false);
		}
	}
	for (int i = 0; i < 100; i++)
	{
		CBrick* brick = new CBrick();
		brick->AddAnimation(1000);
		brick->SetPosition(0 + i * 10.0f, 160);
		objects.push_back(brick);
		/*brick->SetActive(false);*/

	}
	objects.push_back(SIMON);
	objects.push_back(MS);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> collide;
	for (int i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	// Update camera to follow SIMON
	float cx, cy;
	//CGame::GetInstance()->SetCamPos(0.0f, 0.0f /*cy*/);
	SIMON->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;
	if (cx < 650/ 2 && cx>0)
	{
		CGame::GetInstance()->SetCamPos(cx, 0.0f);///cy
	}
}
/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		CSprites* sprites = CSprites::GetInstance();
		int x=0, y=0;
		int flag = 1;
		/*sprites->Get(1)->Draw(0,0 );
		sprites->Get(2)->Draw(0, 32);
		sprites->Get(3)->Draw(0, 64);*/
		
		//for (int i = 1; i <= 38; i++)
		//{
		int i, j;
		ifstream file_entrance("entrance.txt");
		int number;
		queue<int>entr;
		if (file_entrance.is_open())
		{
			while (!file_entrance.eof())
			{
				file_entrance >> number;
				entr.push(number);
			}
		}
		for (i = 0; i < 6*32; i=i+32)
		{
			for (j = 0; j < 24*32; j=j+32)
				{
					sprites->Get(entr.front())->Draw(j, i);
					entr.pop();
				}
		}
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

		

		spriteHandler->End();
		

		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}