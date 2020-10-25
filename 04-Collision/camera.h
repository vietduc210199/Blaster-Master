#pragma once
#include "Game.h"
class camera
{
private:
	static camera* __instance;

	float cam_x;
	float cam_y;
public:
	void SetCamPos(float x, float y);
	float GetCam_x() { return cam_x; };
	float GetCam_y() { return cam_y; };

	static camera* GetInstance()
	{
		if (__instance == NULL) __instance = new camera();
		return __instance;
	}
};

