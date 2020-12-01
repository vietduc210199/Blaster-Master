#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "AnimationsManager.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

void CGameObject::EnemySetStateDie()
{
	if (state == ENEMY_STATE_ATTACK) return;
	int a;
	int b;
	srand(time(NULL));
	a = rand() % 15 + 1;
	switch (a)
	{
	case 1:
	case 2:
	case 3:
		this->just_die = 1;
		this->StartDieTime();

		break;
	case 4:
	case 5:
		b = rand() % 3 + 1;
		switch (b)
		{
		case 1:
			this->SetState(ENEMY_STATE_DAGGER); break;
		case 2:
			this->SetState(ENEMY_STATE_HOLYWATER); break;
		case 3:
			this->SetState(ENEMY_STATE_AXE); break;
		}
		break;
	case 6:
		b = rand() % 10 + 1;
		switch (b)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			this->SetState(ENEMY_STATE_MONEY1);
			break;
		case 5:
		case 6:
		case 7:
			this->SetState(ENEMY_STATE_MONEY2);
			break;
		case 8:
		case 9:
			this->SetState(ENEMY_STATE_MONEY3);
			break;
		case 10:
			this->SetState(ENEMY_STATE_MONEY4);
			break;
		default:
			break;
		}
		break;
	default:
			this->SetState(ENEMY_STATE_SHEART); break;
	}
	DebugOut(L"Enemy rand a: %\d\n", a);
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx*dt;
	float sdy = svy*dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty, 
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix>=0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy>=0) coEventsResult.push_back(coEvents[min_iy]);
}


void CGameObject::LoadAnimations(string source)
{
	int idani, time, idsprite;
	string all;
	ifstream infile;
	LPANIMATION ani;
	
	idani = 0;
	infile.open(source);

	while (!infile.eof())
	{
		int num_sprite;
		infile >> idani;
		ani = new CAnimation(100);
		infile >> num_sprite;
		for (int i = 0; i < num_sprite; i++)
		{
			infile >> idsprite >> time;
			ani->Add(idsprite, time);
		}
		AnimationsManager::getInstance()->getData()->Add(idani, ani);
		this->AddAnimation(idani);
	}
}

void CGameObject::SetDirection(int d)
{
	direction = d;
}

int CGameObject::GetDirection()
{
	return direction;
}

void CGameObject::SetId(int ID)
{
	this->id = ID;
}

int CGameObject::GetId()
{
	return this->id;
}

void CGameObject::RenderBoundingBox(Camera* camera)
{
	if (active == true && CGame::GetInstance()->GetDebugging())
	{
		D3DXVECTOR3 p((int)x, (int)y, 0);
		RECT rect;

		LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

		float l, t, r, b;

		GetBoundingBox(l, t, r, b);
		rect.left = 0;
		rect.top = 0;
		rect.right = (int)r - (int)l;
		rect.bottom = (int)b - (int)t;

		D3DXVECTOR2 pos = camera->transform(l, t);

		CGame::GetInstance()->Draw(pos.x, pos.y, bbox, rect.left, rect.top, rect.right, rect.bottom, 80);
	}
}
bool CGameObject::CheckCollision(CGameObject* object)
{
	if (CGame::GetInstance()->AABB(this->GetBound(), object->GetBound()))
	{
	
		return true;
	}

	LPCOLLISIONEVENT e = SweptAABBEx(object);
	if (e->t > 0 && e->t <= 1.0f)
	{


		return true;
	}
	delete e;
}
void CGameObject::Collision(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		if (!isStop)
		{
			x += dx;
			y += dy;
		}
		isOnGround = false;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// block 
		if (!isStop)
		{
			if (ny == 1)
				y += dy;
		}
		if (ny == -1)
		{
			y += min_ty * dy + ny * 0.2f;
			isOnGround = true;
		}
		if (state == ENEMY_STATE_SHEART)
		{
			if (ny == -1) { isOnGround = true; vy = 0; vx = 0; }
		}
		CollisionOccurred(coObjects);
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CGameObject::CollisionOccurred(vector<LPGAMEOBJECT>* coObjects)
{

}
void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}


CGameObject::~CGameObject()
{

}