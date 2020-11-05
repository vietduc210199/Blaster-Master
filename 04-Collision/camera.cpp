#include "camera.h"

camera* camera::__instance = NULL;

void camera::SetCamPos(float x, float y)
{
	cam_x = x;
	cam_y = y;
	CGame::GetInstance()->SetCamPos(x, y);
}

void camera::SetStartPoint(int a)
{
	this->startpoint = a;
}

void camera::SetEndPoint(int a)
{
	this->endpoint = a;
}
