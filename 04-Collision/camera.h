	#pragma once
#include "Game.h"
class camera
{
private:
	static camera* __instance;

	float cam_x;
	float cam_y;
	int cammove = 0;
	bool CamMoving = false;
	float cameramovetime;
	int startpoint;
	int endpoint;
	DWORD cammove_start;

public:
	camera();
	~camera();
	void SetCamPos(float x, float y);
	float GetCam_x() { return cam_x; };
	float GetCam_y() { return cam_y; };
	int GetCamMove() { return this->cammove; }
	void SetStartPoint(int a);
	void SetEndPoint(int a);
	int GetStartPoint()
	{
		return startpoint;
	}
	int GetEndPoint()
	{
		return endpoint;
	}
	boolean GetCamMoving()
	{
		return CamMoving;
	}
	void SetCamerax(float x)
	{
		this->cam_x = x;
	}
	D3DXVECTOR2 transform(float x_world, float y_world);
	void SetCamMoving(bool a) { CamMoving = a; }
	void StartCamMove(float a) { cammove = 1; cammove_start = GetTickCount(); cameramovetime = a; }
	static camera* GetInstance()
	{
		if (__instance == NULL) __instance = new camera();
		return __instance;
	}
	void Update(DWORD dt, float start, float end);
};

