#pragma once
#include "Game.h"
class camera
{
private:
	static camera* __instance;

	float cam_x;
	float cam_y;
	int cammove = 0;

	int startpoint;
	int endpoint;
public:
	void SetCamPos(float x, float y);
	float GetCam_x() { return cam_x; };
	float GetCam_y() { return cam_y; };
	int GetCamMove() { return this->cammove; }
	void SetStartPoint(int a);
	void SetEndPoint(int a);


	static camera* GetInstance()
	{
		if (__instance == NULL) __instance = new camera();
		return __instance;
	}
};

