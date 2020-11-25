#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Textures.h"
#include "Sprites.h"
#include "define.h"
#include "camera.h"


using namespace std;

//#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:

	float x; 
	float y;

	int id;
	
	int type; // Loại Object
	int direction;	// hướng -1 : trái, 1: phải

	int health = 1;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;	 
	float FirstX;

	int state;
	int level = 1;
	boolean active = true;
	
	bool isTouchable;
	bool isOnGround;
	bool isStop;

	int die = 0;

	DWORD dt; 
	DWORD dietime_start;

    CTextures* texture;
	CSprite* sprite;
	CAnimation* animation;

	vector<LPANIMATION> animations;
	void LoadAnimations(string source);

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	D3DXVECTOR2 GetPosition() { return D3DXVECTOR2(x, y); }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	virtual void SetActive(boolean a) { active = a; };
	virtual boolean GetActive() { return active; };
	void StartDieTime() { die = 1; dietime_start = GetTickCount(); }

	int GetState() { return this->state; }

	void SetDirection(int d);
	int GetDirection();
	void SetId(int ID);
	int GetId();


	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);

	void AddAnimation(int aniId);

	CGameObject();
	bool CheckCollision(CGameObject* object);
	virtual void Collision(vector<LPGAMEOBJECT>* coObjects);
	virtual void CollisionOccurred(vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	void RenderBoundingBox(Camera* camera);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera* camera) = 0;
	virtual void SetState(int state) { this->state = state; }
	virtual void SetLevel(int level) { this->level = level; }
	RECT CGameObject::GetBound()
	{
		RECT rect;
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		return rect;
	}


	~CGameObject();
};

