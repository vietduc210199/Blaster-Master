#pragma once
#include "define.h"
#include "camera.h"
#include "GameObject.h"
#include "FireBullet.h"

class Fishman : public CGameObject
{
private:
	bool isStop = false;
	bool isFalling;
	bool isAttack;
	DWORD timerAttack = 0;

	float movepoint;
	CGameObject* MS;
	CGameObject* Simon;
	Camera* camera;
	FireBullet* firebullet;
	vector<LPGAMEOBJECT> firebullets;
	vector<LPGAMEOBJECT> simon;
public:
	Fishman(CGameObject* Simon, CGameObject* MS, Camera* camera, float movepoint) :CGameObject()
	{
		this->LoadAnimations("ReadFile\\Ani\\Fishmanani.txt");
		SetState(ENEMY_STATE_JUMPING);
		type = FISHMAN;
		active = true;
		isStop = false;
		this->movepoint = movepoint;
		this->Simon = Simon;
		this->MS = MS;
		this->camera = camera;
		firebullet = new FireBullet(Simon, MS);
		firebullet->SetActive(false);
		simon.push_back(this->Simon);
	}
	~Fishman();
	bool GetStop()
	{
		return isStop;
	}
	void SetStop(bool a) { isStop = a; }
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render(Camera* camera);

	RECT GetBound()
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
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void CollisionOccurred(vector<LPGAMEOBJECT>* coObjects) override;
};

