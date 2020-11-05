#include "SceneGame.h"
#include "define.h"



SceneGame::SceneGame()
{
	camera = camera::GetInstance();
	game = CGame::GetInstance();
	
	AnimationsManager* animations = AnimationsManager::getInstance();
	grid = new Grid();
	simon = new CSimon();


	LoadResources(SOURCE_ENTRANCE_PNG, eType::ID_TEX_ENTRANCESTAGE, SOURCE_ENTRANCE_TXT, ID_SCENE_LEVEL_ENTRANCE);
	

	MS = new CMS();
	MS->GetSimon(simon);

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
		simon->SetPosition(50.0f, 0);

	

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

void SceneGame::LoadResources(LPCWSTR picturePath, int idTex, const char* filepath, int scene)
{
	camera->SetCamPos(0, 0);
	LoadSceneObject(scene);
	grid->ClearGrid();
	stages.clear();
	LoadSceneElement(scene);
	
	LoadStageVaribale(scene);

	Tile = new TileMap(picturePath, idTex, 42, 0);
	Tile->LoadMap(filepath);
	simon->SetPosition(stages.at(0)->simonposx, stages.at(0)->simonposy);
	simon->SetStartPoint(stages.at(0)->startpoint);
	simon->SetEndPoint(stages.at(0)->endpoint);
	camera->SetStartPoint(stages.at(0)->startpoint);
	camera->SetEndPoint(stages.at(0)->endpoint);
}

void SceneGame::LoadSceneElement(int scene)
{
	if (scene == ID_SCENE_LEVEL_ENTRANCE)
	{
		LoadElementFromFile(SOURCE_ENTRANCE_ELEMENT_TXT);
	}
	else if (scene == ID_SCENE_LEVEL_CASTLE)
	{
		LoadElementFromFile(SOURCE_CASTLE_ELEMENT_TXT);
	}
}

void SceneGame::LoadStageVariableFromFile(string source)
{
	int number;
	int flag = 0;
	int* arr = new int[20];
	ifstream infile;
	infile.open(source);
	while (!infile.eof())
	{
		while (infile >> number)
		{
			arr[flag] = number;
			flag++;
			if (flag == arr[0])
			{
				stage = new Stage();
				stage->AddVariable(arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7]);
				for (int i = 0; i < arr[8]; i++)
				{
					stage->AddTemp(arr[i + 9], i);
				}
				stages.push_back(stage);
				flag = 0;
			}
		}
	}
	infile.close();
}

void SceneGame::LoadElementFromFile(string source)
{
	int flag = 0;
	int number;
	int* arr = new int[20];
	int simonstartx;
	int simonstarty;
	ifstream file_objects(source);
	if (file_objects.is_open())
	{
		while (!file_objects.eof())
		{
			while (file_objects >> number)
			{
				arr[flag] = number;
				flag++;
				if (flag == arr[0])
				{
					hiddenmoneyposx = arr[1];
					hiddenmoneyposy = arr[2];
					bossposx = arr[3];
					bossposy = arr[4];
					startmap = arr[5];
					endmap = arr[6];
					ghouly = arr[7];
					effectdoory = arr[8];
					flag = 0;
				}
			}
		}
	}
}

void SceneGame::LoadSceneObject(int scene)
{
	if (scene == ID_SCENE_LEVEL_ENTRANCE)
	{
		LoadObjectFromFile(SOURCE_OBJECT_SCENE1_TXT);
		grid->maprow = 3;
		grid->mapcol = 9;
	}
	else if (scene == ID_SCENE_LEVEL_CASTLE)
	{
		LoadObjectFromFile(SOURCE_OBJECT_SCENE2_TXT);
		grid->maprow = 6;
		grid->mapcol = 35;
	}
}

void SceneGame::LoadObjectFromFile(string source)
{//vector<int> numbers;
	int flag = 0;
	int number;
	int arr[10];
	ifstream file_objects(source);
	if (file_objects.is_open())
	{
		while (!file_objects.eof())
		{
			while (file_objects >> number)
			{
				arr[flag] = number;
				flag++;
				if (flag == 10)
				{
					switch (arr[0])
					{
					case BRICK:
						brick = new CBrick();
						brick->SetMulwidth(arr[3]);
						brick->SetPosition(arr[1], arr[2]);
						grid->InsertIntoGrid(brick, arr[6], arr[7], arr[8], arr[9]);
						break;
					case TORCH:
						torch = new CTorch();
						torch->SetPosition(arr[1], arr[2]);
						torch->SetState(arr[3]);
						grid->InsertIntoGrid(torch, arr[6], arr[7], arr[8], arr[9]);
						break;
				/*	case STAGECHANGER:
						InObj = new InviObjects();
						InObj->SetPosition(arr[1], arr[2]);
						InObj->SetType(arr[3]);
						grid->InsertIntoGrid(InObj, arr[6], arr[7], arr[8], arr[9]);
						break;*/
					case BREAKABLE_BRICK:
						brick = new CBrick();
						brick->SetMulwidth(1);
						brick->SetState(arr[3]);
						brick->SetPosition(arr[1], arr[2]);
						grid->InsertIntoGrid(brick, arr[6], arr[7], arr[8], arr[9]);
					}

					flag = 0;
				}
			}
		}
	}
}

void SceneGame::LoadStageVaribale(int scene)
{
	if (scene == ID_SCENE_LEVEL_ENTRANCE)
	{
		LoadStageVariableFromFile(SOURCE_STAGE_ENTRANCE_TXT);
	}
	else if (scene == ID_SCENE_LEVEL_CASTLE)
	{
		LoadStageVariableFromFile(SOURCE_STAGE_CASTLE_TXT);
	}
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
	if (cx < 1000 / 2 && cx>0)
	{
		camera->SetCamPos(cx, 0.0f);///cy
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
	//int i, j;
	//ifstream file_entrance("entrance.txt");
	//int number;
	//queue<int>entr;
	//if (file_entrance.is_open())
	//{
	//	while (!file_entrance.eof())
	//	{
	//		file_entrance >> number;
	//		entr.push(number);
	//	}
	//}
	//for (i = 0; i < 6 * 32; i = i + 32)
	//{
	//	for (j = 0; j < 24 * 32; j = j + 32)
	//	{
	//		sprites->Get(entr.front())->Draw(j, i);
	//		entr.pop();
	//	}
	//}
	Tile->DrawMap(camera);
	for (int i = 0; i < listobj.size(); i++)
		listobj[i]->Render();
}
