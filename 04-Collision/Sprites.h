#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left; 
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;

	LPD3DXSPRITE spriteHandler;
	int currentFrame;
	int totalFrames;

	float frameWidth;
	float frameHeight;

	int column;
	int row;

	DWORD timeAccumulated;	 // thời gian chờ đã tích lũy
	DWORD timeAnimation; // thời gian phải chờ giữa các frame
public: 
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, DWORD TimeAnimation, int totalFrames = 1, int collum = 1, int row = 1);

	void Draw(float x, float y, int alpha = 255);
	void DrawFrame(int idFrame, float X, float Y,int Column, float FrameWidth, float Frameheight, int row = 1, int alpha = 255, int R = 255, int G = 255, int B = 255);


	void SelectFrame(int idFrame)
	{
		currentFrame = idFrame;
	}
	int GetCurrentFrame()
	{
		return currentFrame;
	}

	float GetFrameWidth()
	{
		return frameWidth;
	}

	float GetFrameHeight()
	{
		return frameHeight;
	}
	void Update(DWORD dt);
	void Next();
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
	LPSPRITE &operator[](int id) {return sprites[id];}

	static CSprites * GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	int GetCurrentFrame()
	{
		return currentFrame;
	};
	void SetCurrentcFrame(int cf)
	{
		this->currentFrame = cf;
	}
	void Render(float x, float y, int alpha=255);
	void Render(D3DXVECTOR2 pos, int alpha);
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations * GetInstance();
};

