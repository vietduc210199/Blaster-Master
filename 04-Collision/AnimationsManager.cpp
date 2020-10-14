#include "AnimationsManager.h"


AnimationsManager* AnimationsManager::__instance = NULL;

void AnimationsManager::LoadResources()
{
	SpritesManager* spritesManager = spritesManager->getInstance();

	LPANIMATION ani;

	ani = new CAnimation(100);	// idle right
	ani->Add(10001);
	animations->Add(400, ani);
	ani = new CAnimation(100);	// idle left
	ani->Add(10011);
	animations->Add(401, ani);

	ani = new CAnimation(100);	// walk right
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);
	ani = new CAnimation(100);	//  walk left
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	ani = new CAnimation(100);	// attack right
	ani->Add(10004);
	ani->Add(10005);
	ani->Add(10006);
	animations->Add(402, ani);
	ani = new CAnimation(100);	// attack left
	ani->Add(10014);
	ani->Add(10015);
	ani->Add(10016);
	animations->Add(502, ani);

	ani = new CAnimation(100);	// jump right
	ani->Add(10007);
	animations->Add(403, ani);
	ani = new CAnimation(100);	// jump right
	ani->Add(10017);
	animations->Add(503, ani);

	ani = new CAnimation(100);	// sit right
	ani->Add(10008);
	animations->Add(404, ani);
	ani = new CAnimation(100);	// sit right
	ani->Add(10018);
	animations->Add(504, ani);

	ani = new CAnimation(100);		// brick
	ani->Add(90001);
	animations->Add(1000, ani);

	ani = new CAnimation(100);		// torch
	ani->Add(90002);
	animations->Add(1001, ani);

	ani = new CAnimation(100);		//mornig star
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	animations->Add(600, ani);
	ani = new CAnimation(100);//left morning starr
	ani->Add(20011);
	ani->Add(20012);
	ani->Add(20013);
	animations->Add(601, ani);
}
