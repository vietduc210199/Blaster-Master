#include "SceneGame.h"



SceneGame::SceneGame()
{
	LoadResources();

	SetScene(ID_SCENE_LEVEL_ENTRANCE);
}

SceneGame::~SceneGame()
{

}

void SceneGame::SetScene(int IDLevel)
{
	currentLevel = IDLevel;
	if (IDLevel == ID_SCENE_LEVEL_ENTRANCE)
	{
		simon = new CSimon();
		simon->SetPosition(50.0f, 0);

		MS = new CMS();
		MS->GetSimon(simon);

		/*SIMON->SetMS(MS);*/
		for (int i = 0; i < 4; i++)
		{
			CTorch* torch = new CTorch();
			torch->SetPosition(150 + i * 150.0f, 130);
			listobj.push_back(torch);
			if (simon->CheckCollision(torch))
			{
				torch->SetActive(false);
			}
		}
		for (int i = 0; i < 100; i++)
		{
			CBrick* brick = new CBrick();
			brick->SetPosition(0 + i * 10.0f, 160);
			listobj.push_back(brick);
			/*brick->SetActive(false);*/
		}
		listobj.push_back(simon);
		listobj.push_back(MS);
	}
}

void SceneGame::KeyState(BYTE* state)
{
	// disable control key when SIMON die 
	if (simon->GetState() == SIMON_STATE_DIE) return;
	if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
		simon->SetRight(1);
	}
	else if (CGame::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		simon->SetState(SIMON_STATE_WALKING_LEFT);
		simon->SetRight(0);
	}
	else if (CGame::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(SIMON_STATE_SIT);
		/*SIMON->Sit();*/
		simon->SetSit(true);
	}
	//else if(game->IsKeyDown())
	else
		simon->SetState(SIMON_STATE_IDLE);

}

void SceneGame::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		simon->SetState(SIMON_STATE_JUMP);
		simon->StartJump();
		break;
	case DIK_A:
		if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT) || CGame::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			return;
		}
		MS->StartAttack();
		MS->SetState(WHIP_STATE_ATTACK);
		MS->SetActive(true);
		simon->SetState(SIMON_STATE_ATTACK);
		simon->StartAttack();
		break;
	case DIK_Q:
		if (simon->GetActive() == true)
		{
			simon->SetActive(false);
		}
		else simon->SetActive(true);
		break;
	}
}

void SceneGame::OnKeyUp(int KeyCode)
{
	if (KeyCode == 208) {
		simon->StandUp();
	}
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void SceneGame::LoadResources()
{
	AnimationsManager* animations = AnimationsManager::getInstance();
}

void SceneGame::InitGame()
{
}

void SceneGame::Update(DWORD dt)
{
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> collide;
	for (int i = 0; i < listobj.size(); i++)
	{
		coObjects.push_back(listobj[i]);
	}
	for (int i = 0; i < listobj.size(); i++)
	{
		listobj[i]->Update(dt, &coObjects);
	}
	// Update camera to follow SIMON
	float cx, cy;
	//CGame::GetInstance()->SetCamPos(0.0f, 0.0f /*cy*/);
	simon->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;
	if (cx < 650 / 2 && cx>0)
	{
		CGame::GetInstance()->SetCamPos(cx, 0.0f);///cy
	}
}

void SceneGame::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	int x = 0, y = 0;
	int flag = 1;
	/*sprites->Get(1)->Draw(0,0 );
	sprites->Get(2)->Draw(0, 32);
	sprites->Get(3)->Draw(0, 64);*/

	//for (int i = 1; i <= 38; i++)
	//{
	int i, j;
	ifstream file_entrance("entrance.txt");
	int number;
	queue<int>entr;
	if (file_entrance.is_open())
	{
		while (!file_entrance.eof())
		{
			file_entrance >> number;
			entr.push(number);
		}
	}
	for (i = 0; i < 6 * 32; i = i + 32)
	{
		for (j = 0; j < 24 * 32; j = j + 32)
		{
			sprites->Get(entr.front())->Draw(j, i);
			entr.pop();
		}
	}
	for (int i = 0; i < listobj.size(); i++)
		listobj[i]->Render();
}
