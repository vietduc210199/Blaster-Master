#include "camera.h"
#include "define.h"

camera* camera::__instance = NULL;

camera::camera()
{
}

camera::~camera()
{
}

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

D3DXVECTOR2 camera::transform(float x_world, float y_world)
{
	return D3DXVECTOR2(x_world - cam_x, y_world - cam_y);;
}

void camera::Update(DWORD dt, float start, float end)
{

	if (GetTickCount() - cammove_start > cameramovetime)
	{
		cammove_start = 0;
		cammove = 0;
	}
	if (cammove != 0)
	{
		cam_x += 1;
	}
	if (cam_x >= startpoint && endpoint == end)
	{
		CamMoving = false;
	}
	if (CamMoving == false)
	{
		if (cam_x <= startpoint)
		{
			cam_x = startpoint;
		}
		else
			if (cam_x >= endpoint - SCREEN_WIDTH)
			{
				cam_x = endpoint - SCREEN_WIDTH;
			}
	}
}
