#include "SceneGame.h"
#include "define.h"



SceneGame::SceneGame()
{
	
	game = CGame::GetInstance();
	camera = new Camera();

	AnimationsManager* animations = AnimationsManager::getInstance();
	grid = new Grid();
	simon = new CSimon();


	LoadResources(SOURCE_ENTRANCE_PNG, eType::ID_TEX_ENTRANCESTAGE, SOURCE_ENTRANCE_TXT, ID_SCENE_LEVEL_ENTRANCE);
	//LoadResources(SOURCE_CASTLE_PNG, eType::ID_TEX_CASTLE, SOURCE_CASTLE_TXT, ID_SCENE_LEVEL_CASTLE);
	

	MS = new CMS();
	MS->GetSimon(simon);

	//tokens
	dagger = new Dagger(camera, simon->nx);
	axe = new Axe(simon->GetPosition().x, camera, simon->nx);
	Holywater = new HolyWater(simon->GetPosition().x, camera, simon->nx);

	gameTime = new GameTime();
	gameTime->SetTime(0);

	board = new Board(BOARD_DEFAULT_POSITION_X, BOARD_DEFAULT_POSITION_Y);

	/*stagename = 3;
	simon->SetStartPoint(stages.at(3)->startpoint);
	simon->SetEndPoint(stages.at(3)->endpoint);
	camera->SetStartPoint(stages.at(3)->startpoint);
	camera->SetEndPoint(stages.at(3)->endpoint);
	simon->SetPosition(stages.at(3)->simonposx, stages.at(3)->simonposy);*/
}

SceneGame::~SceneGame()
{
	SAFE_DELETE(grid);
	SAFE_DELETE(Tile);
	SAFE_DELETE(board);
}

void SceneGame::KeyState(BYTE* state)
{
	// disable control key when SIMON die 
	if (simon->GetState() == SIMON_STATE_DIE || simon->GetChangeColorTime() != 0) return;
	if (game->IsKeyDown(DIK_RIGHT) && !game->IsKeyDown(DIK_DOWN) && simon->GetJumpTime() == 0 && simon->GetOnStair() == false && camera->GetCamMove() == false && simon->GetIsDamaged() == 0)
	{
		
		if (simon->GetHealth() != 0)
		{
			if (simon->GetAutoWalkingTime() == 0 && simon->GetAttackTime() == 0)
				simon->SetState(SIMON_STATE_WALKING_RIGHT);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT) && !game->IsKeyDown(DIK_DOWN) && simon->GetJumpTime() == 0 && simon->GetOnStair() == false && camera->GetCamMove() == false && simon->GetIsDamaged() == 0)
	{
		if (simon->GetHealth() != 0)
		{
			if (simon->GetAutoWalkingTime() == 0 && simon->GetAttackTime() == 0)
				simon->SetState(SIMON_STATE_WALKING_LEFT);
		}
	}
	else if (game->IsKeyDown(DIK_DOWN) && camera->GetCamMove() == false && simon->GetIsDamaged() == 0 )
	{
		if(simon->GetJumpMoveTime() == 0)
		if (simon->GetHealth() != 0)
		{
			if (simon->GetAutoWalkingTime() == 0)
			{
				if (simon->GetOnStair() == false)
				{
					simon->SetState(SIMON_STATE_SIT);
					simon->SetSit(true);
				}
				else if (simon->GetOnStair() == true)
				{
					simon->SetState(SIMON_STATE_WALKING_DOWN_STAIR);
				}
			}
		}
	}
	else if (game->IsKeyDown(DIK_UP) && camera->GetCamMove() == false && simon->GetIsDamaged() == 0)
	{
		if (simon->GetHealth() != 0)
		{
			if (simon->GetAutoWalkingTime() == 0)
			{
				if (simon->GetOnStair() == true)
				{
					simon->SetState(SIMON_STATE_WALKING_UP_STAIR);
				}
			}
		}
	}
	else
		simon->SetState(SIMON_STATE_IDLE);
}

void SceneGame::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (simon->GetState() == SIMON_STATE_DIE || simon->GetChangeColorTime() != 0 || simon->GetAutoWalkingTime() != 0 || camera->GetCamMove() == true || simon->GetIsDamaged() != 0 || simon->GetHealth() == 0) return;
	switch (KeyCode)
	{
	case DIK_S:
		if (simon->GetOnStair() == false)
		{
			if (simon->GetOnGround())
			{
				simon->SetState(SIMON_STATE_JUMP);
				if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))
				{
					simon->StartJumpMove();
				}
				else simon->StartJump();
			}
		}
		break;
	case DIK_A:
		if (simon->GetAttackTime() == 0)
		{	
			if (game->IsKeyDown(DIK_UP) && simon->GetHeartCollect() > 0)
			{
				if (simon->GetThrowDagger() && weapon.size() < simon->GetNumWeapon())
				{
					dagger = new Dagger(camera, simon->nx);
					simon->SetHeart(-1);

					if (simon->nx > 0)
					{
						dagger->SetPosition(simon->x + 20, simon->y + 5);
					}
					else
						dagger->SetPosition(simon->x, simon->y + 5);
					//phantombat->GetSimonDagger(dagger);
					weapon.push_back(dagger);
					MS->SetActive(false);
					simon->SetState(SIMON_STATE_ATTACK);
					simon->StartAttack();
				}
				else if (simon->GetThrowAxe() && weapon.size() < simon->GetNumWeapon())
				{
					axe = new Axe(simon->GetPosition().x + 8, camera, simon->nx);
					simon->SetHeart(-1);

					if (simon->nx > 0)
					{
						axe->SetPosition(simon->x + 8, simon->y);
					}
					else
						axe->SetPosition(simon->x + 24, simon->y);
					//phantombat->GetSimonAxe(Axe);
					weapon.push_back(axe);
					MS->SetActive(false);
					simon->SetState(SIMON_STATE_ATTACK);
					simon->StartAttack();
				}
				else if (simon->GetThrowHolyWater() && weapon.size() < simon->GetNumWeapon())
				{
					if (simon->nx > 0)
					{
						Holywater = new HolyWater(simon->GetPosition().x + 20, camera, simon->nx);
						simon->SetHeart(-1);

						Holywater->SetPosition(simon->x + 20, simon->y);
					}
					else
					{
						Holywater = new HolyWater(simon->GetPosition().x, camera, simon->nx);
						simon->SetHeart(-1);

						Holywater->SetPosition(simon->x + 8, simon->y);
					}
					weapon.push_back(Holywater);
					MS->SetActive(false);
					simon->SetState(SIMON_STATE_ATTACK);
					simon->StartAttack();
				}
			}

			if (!game->IsKeyDown(DIK_UP))
			{
				MS->SetActive(true);
				if (game->IsKeyDown(DIK_DOWN))
				{
					simon->SetState(SIMON_STATE_SIT);
					simon->StartSitAttack();
					MS->StartAttack();
					simon->SetJump(0);
				}
				else {
					simon->SetState(SIMON_STATE_ATTACK);
					simon->StartAttack();
					MS->StartAttack();
					simon->SetJump(0);
				}
				if (simon->GetLevel() == SIMON_LEVEL_MS_2)
				{
					MS->SetState(MS_STATE_ATTACK_2);
				}
				if (simon->GetLevel() == SIMON_LEVEL_MS_3)
				{
					MS->SetState(MS_STATE_ATTACK_3);
				}
			}
		}
		break;
	}
}

void SceneGame::OnKeyUp(int KeyCode)
{
	if (KeyCode == 208) {
		if (simon->GetSit() == true)
			simon->StandUp();
	}
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void SceneGame::LoadResources(LPCWSTR picturePath, int idTex, const char* filepath, int scene)
{
	camera->SetCamera(0, 0);
	grid->ClearGrid();
	stages.clear();
	LoadSceneElement(scene);
	LoadSceneObject(scene);
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
				stage = new CStage();
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
					case STAGECHANGER:
						InObj = new InviObjects();
						InObj->SetPosition(arr[1], arr[2]);
						InObj->SetType(arr[3]);
						grid->InsertIntoGrid(InObj, arr[6], arr[7], arr[8], arr[9]);
						break;
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

void SceneGame::Update(DWORD dt)
{
	//Push Objects
	vector<LPGAMEOBJECT> coObjects;
	grid->GetListCollisionFromGrid(camera, ObjectsFromGrid);
	torches.clear();
	invisibleobjects.clear();
	bricks.clear();
	for (int i = 0; i < ObjectsFromGrid.size(); i++)
	{
		coObjects.push_back(ObjectsFromGrid[i]);
	}

	for (int i = 0; i < coObjects.size(); i++)
	{
		if (coObjects.at(i)->type == BRICK)
			bricks.push_back(coObjects[i]);
		else if (coObjects.at(i)->type == TORCH)
			torches.push_back(coObjects[i]);
		else
			invisibleobjects.push_back(coObjects[i]);
	}

	//Simon collision with torch
	for (int i = 0; i < torches.size(); i++)
	{
		CTorch* torch = dynamic_cast<CTorch*>(torches[i]);
		if (simon->CheckCollision(torch))
		{
			switch (torch->GetState())
			{
			case TORCH_STATE_CANDLE:
			case TORCH_STATE_NORMAL:
			case TORCH_STATE_INVI_POT_TORCH:
			case TORCH_STATE_AXE_TORCH:
				break;
			case TORCH_STATE_LHEART:
				torch->SetActive(false);
				simon->SetHealth(-3);
				simon->SetHeart(2);
				break;
			case TORCH_STATE_SHEART:
				simon->SetHealth(-1);
				simon->SetHeart(1);
				torch->SetActive(false);
				break;
			case TORCH_STATE_CHIKEN:
				torch->SetActive(false);
				simon->SetHealth(-5);
				break;
			case TORCH_STATE_CROSS:
				torch->SetActive(false);
				simon->SetEatCross(true);
				//enemy.clear();
				break;
			case TORCH_STATE_CLOCK:
				torch->SetActive(false);
				//StopEnemyStart();
				break;
			case TORCH_STATE_INVI_POT:
				torch->SetActive(false);
				simon->StartIsUnTouchable(SIMON_UNTOUCHABLE_TIME * 2);
				break;
			case TORCH_STATE_MONEY1:
				torch->SetActive(false);
				break;
			case TORCH_STATE_MONEY2:
				torch->SetActive(false);
				break;
			case TORCH_STATE_MONEY3:
				torch->SetActive(false);
				break;
			case TORCH_STATE_MONEY4:
				torch->SetActive(false);
				break;
			case TORCH_STATE_MSUP:
				torch->SetActive(false);
				simon->StartChangeColor();
				if (simon->GetLevel() == SIMON_LEVEL_MS_1)
				{
					simon->SetLevel(SIMON_LEVEL_MS_2);
				}
				else if (simon->GetLevel() == SIMON_LEVEL_MS_2)
				{
					simon->SetLevel(SIMON_LEVEL_MS_3);
				}
				break;
			case TORCH_STATE_DAGGER:
				torch->SetActive(false);
				simon->SetThrowDagger(true);
				simon->SetThrowAxe(false);
				simon->SetThrowHolyWater(false);
				break;
			case TORCH_STATE_AXE:
				torch->SetActive(false);
				simon->SetThrowDagger(false);
				simon->SetThrowAxe(true);
				simon->SetThrowHolyWater(false);
				break;
			case TORCH_STATE_HOLYWATER:
				torch->SetActive(false);
				simon->SetThrowDagger(false);
				simon->SetThrowAxe(false);
				simon->SetThrowHolyWater(true);
				break;
			case TORCH_STATE_DOUBLE_SHOOT:
				torch->SetActive(false);
				simon->SetNumWeapon(2);
			}
		}
	}

	//Simon collison with breakabkle brick
	for (int i = 0; i < bricks.size(); i++)
	{
		if (bricks.at(i)->GetState() != BRICK_STATE_NORMAL)
		{
			if (simon->CheckCollision(bricks.at(i)))
			{
				if (bricks.at(i)->GetState() == BBRICK_STATE_CHIKEN)
				{
					bricks.at(i)->SetActive(false);
					simon->SetHealth(-5);
				}
				if (bricks.at(i)->GetState() == BBRICK_STATE_DOUBLE_SHOOT)
				{
					simon->SetNumWeapon(2);
					bricks.at(i)->SetActive(false);
				}
				if (bricks.at(i)->GetState() == BBRICK_STATE_MONEY)
				{
					bricks.at(i)->SetActive(false);
				}
			}
		}
	}
	

	//Simon collision with Invisible Objects
	for (int i = 0; i < invisibleobjects.size(); i++)
	{
		InviObjects* InOb = dynamic_cast<InviObjects*>(invisibleobjects[i]);
		if (simon->CheckCollision(InOb))
		{
			if (InOb->type == SC_TYPE_CHANGE_SCENE)
			{
				if (simon->GetAutoWalkingTime() == 0)
				{
					LoadResources(SOURCE_CASTLE_PNG, ID_TEX_CASTLE, SOURCE_CASTLE_TXT, 2);
				}
			}
			else if (InOb->type == SC_TYPE_AUTO_HELPER)
			{
				InOb->SetActive(false);
				simon->StartAutoWalking(SIMON_AUTO_GO_SCENE1);
			}
			else if (InOb->type == SC_TYPE_DOOR)
			{
				InOb->SetActive(false);
				if (simon->x >= InOb->x - 24)
					simon->x = InOb->x - 24;
				effect = new Effect(camera);
				effect->SetType(EFFECT_TYPE_DOOR);
				effect->SetPosition(InOb->x, effectdoory);
				effects.push_back(effect);
				camera->StartCamMove(CAM_MOVE_TIME1);
				camera->SetCamMoving(true);
				stagename = stagename + 1;
				simon->SetEndPoint(stages.at(stagename)->endpoint);
				camera->SetEndPoint(stages.at(stagename)->endpoint);
				SimonMove = true;
			}
			else if (InOb->type == SC_TYPE_CHANGE_STAGE)
			{
				InOb->SetActive(false);
				camera->StartCamMove(CAM_MOVE_TIME2);
				camera->SetCamMoving(true);
				SimonMove = false;
				simon->SetStartPoint(stages.at(stagename)->startpoint);
				camera->SetStartPoint(stages.at(stagename)->startpoint);
				endpoint = stages.at(stagename)->endpoint;
			}
			else if (InOb->type == SC_TYPE_UNDER_GROUND)
			{
				if (simon->GetStartPoint() == stages.at(1)->startpoint)
				{
					stagename += 2;
					if (stages.at(3)->temp[0] < stages.at(3)->simonposx)
					{
						stages.at(3)->SetSimonPos(0, 1);
					}
				}
				else if (simon->GetStartPoint() == stages.at(3)->startpoint)
				{
					stagename -= 2;

					if (stages.at(1)->temp[0] < stages.at(1)->simonposx)
					{
						stages.at(1)->SetSimonPos(0, 1);
					}
				}
				simon->SetStartPoint(stages.at(stagename)->startpoint);
				simon->SetEndPoint(stages.at(stagename)->endpoint);
				camera->SetStartPoint(stages.at(stagename)->startpoint);
				camera->SetEndPoint(stages.at(stagename)->endpoint);
				simon->SetPosition(stages.at(stagename)->simonposx - 1, stages.at(stagename)->simonposy - 1);
			}
			else if (InOb->type == SC_TYPE_UNDER_TO_LAND)
			{
				DebugOut(L"Under to land");
				if (simon->GetStartPoint() == stages.at(1)->startpoint)
				{
					stagename += 2;
					if (stages.at(stagename)->temp[0] > stages.at(stagename)->simonposx)
					{
						stages.at(stagename)->SetSimonPos(0, 1);
					}
				}
				else if (simon->GetStartPoint() == stages.at(3)->startpoint)
				{
					stagename -= 2;
					if (stages.at(stagename)->temp[0] > stages.at(stagename)->simonposx)
					{
						stages.at(stagename)->SetSimonPos(0, 1);
					}
				}
				simon->SetStartPoint(stages.at(stagename)->startpoint);
				simon->SetEndPoint(stages.at(stagename)->endpoint);
				camera->SetStartPoint(stages.at(stagename)->startpoint);
				camera->SetEndPoint(stages.at(stagename)->endpoint);
				simon->SetPosition(stages.at(stagename)->simonposx - 1, stages.at(stagename)->simonposy - 1);
			}
			else if (InOb->type == STAIR_TYPE_RIGHT_UP_HELPER)
			{
				if (game->IsKeyDown(DIK_UP) && simon->GetOnStair() == false)
				{
					simon->SetState(SIMON_STATE_WALKING_LEFT);
				}
			}
			else if (InOb->type == STAIR_TYPE_LEFT_UP_HELPER)
			{

				if (game->IsKeyDown(DIK_UP) && simon->GetOnStair() == false)
				{
					simon->SetState(SIMON_STATE_WALKING_RIGHT);
				}
			}
			else if (InOb->type == STAIR_TYPE_UP_RIGHT)
			{

				if (game->IsKeyDown(DIK_UP))
				{
					if (InOb->x - simon->x <= 5)
					{
						simon->x = InOb->x + 2;
					}
					if (simon->x >= InOb->x + 2)
					{
						simon->SetState(SIMON_STATE_WALKING_UP_STAIR);
						simon->StartAutoWalking(SIMON_AUTO_GO_TIME);
						simon->SetOnStair(true);
						simon->SetStairUp(true);
						simon->nx = 1;
					}
				}
				else if (game->IsKeyDown(DIK_DOWN))
				{
					simon->SetOnStair(false);
					simon->SetStairUp(false);
				}
			}
			else if (InOb->type == STAIR_TYPE_DOWN_LEFT)
			{
				if (game->IsKeyDown(DIK_DOWN))
				{
					if (simon->x >= InOb->x - 14 || simon->x < InOb->x - 14 && simon->GetOnStair() == false)
					{
						simon->x = InOb->x - 14;
					}
					if (simon->x >= InOb->x - 14 || simon->x <= InOb->x - 16)
					{
						simon->SetState(SIMON_STATE_WALKING_DOWN_STAIR);
						simon->SetOnStair(true);
						simon->SetStairUp(true);
						simon->nx = -1;
					}
				}
				else if (game->IsKeyDown(DIK_UP))
				{
					if (simon->y + SIMON_IDLE_BBOX_HEIGHT > InOb->y + INVI_HEIGHT)
					{
						simon->y = InOb->y  + INVI_HEIGHT * 2 - SIMON_IDLE_BBOX_HEIGHT + 1;
						simon->x += 1;
					}
					simon->SetOnStair(false);
					simon->SetStairUp(false);
				}
			}
			else if (InOb->type == STAIR_TYPE_UP_LEFT)
			{
				if (game->IsKeyDown(DIK_UP))
				{
					if (InOb->x - simon->x >= 20)
					{
						simon->x = InOb->x - 23.5;
					}
					if (simon->x <= InOb->x - 23.5)
					{
						simon->SetState(SIMON_STATE_WALKING_UP_STAIR);
						simon->StartAutoWalking(SIMON_AUTO_GO_TIME);
						simon->SetOnStair(true);
						simon->SetStairUp(false);
						simon->nx = -1;
					}
				}
				else if (game->IsKeyDown(DIK_DOWN))
				{
					simon->SetOnStair(false);
					simon->SetStairUp(true);
				}
			}
			else if (InOb->type == STAIR_TYPE_DOWN_RIGHT)
			{

				if (game->IsKeyDown(DIK_DOWN) && simon->GetOnStair() == false)
				{
					if (simon->x >= InOb->x - 5 || simon->x < InOb->x - 6 && simon->GetOnStair() == false)
					{
						simon->x = InOb->x - 5;
					}
					if (simon->x == InOb->x - 5)
					{
						simon->SetState(SIMON_STATE_WALKING_DOWN_STAIR);
					}
				
					simon->SetOnStair(true);
					simon->SetStairUp(false);
					simon->nx = 1;
				}
				else if (game->IsKeyDown(DIK_UP) && simon->GetOnStair() == true)
				{
					if (simon->y + SIMON_IDLE_BBOX_HEIGHT > InOb->y + INVI_HEIGHT)
					{
						simon->y = InOb->y + 0.5 + INVI_HEIGHT * 2 - SIMON_IDLE_BBOX_HEIGHT - 1;
						simon->x -= 0.5;
					}
					simon->SetOnStair(false);
					simon->SetStairUp(true);
				}
			}
		}
	}

	

	//Weapon collision with torch
	for (int i = 0; i < torches.size(); i++)
	{
		CTorch* torch = dynamic_cast<CTorch*>(torches[i]);
		if (MS->CheckCollision(torch) /*|| dagger->CheckCollision(torch) || Axe->CheckCollision(torch)*/)
		{
			if (torch->GetState() == TORCH_STATE_INVI_POT_TORCH)
			{
				torch->StartDieTime();
				torch->FirstX = torch->x;
				dagger->SetActive(false);
				torch->SetState(TORCH_STATE_INVI_POT);
			}
			if (torch->GetState() == TORCH_STATE_AXE_TORCH)
			{
				torch->StartDieTime();
				torch->FirstX = torch->x;
				dagger->SetActive(false);
				torch->SetState(TORCH_STATE_AXE);
			}
			if (torch->GetState() == TORCH_STATE_NORMAL || torch->GetState() == TORCH_STATE_CANDLE)
			{
				torch->StartDieTime();
				torch->FirstX = torch->x;
				dagger->SetActive(false);
				MS->MSUpDropTime++;
				int a;
				srand(time(NULL));
				a = rand() % 30 + 1;
				if (MS->MSUpDropTime < 3)
				{
					torch->SetState(TORCH_STATE_MSUP);
				}
				else
					switch (a)
					{
					case 25:
						torch->SetState(TORCH_STATE_SHEART); break;
					case 26:
						torch->SetState(TORCH_STATE_LHEART); break;
					case 27:
						torch->SetState(TORCH_STATE_DAGGER); break;
					case 28:
						torch->SetState(TORCH_STATE_HOLYWATER); break;
					case 29:
						torch->SetState(TORCH_STATE_CROSS); break;
					case 30:
						torch->SetState(TORCH_STATE_AXE); break;
					default: 
						torch->SetState(TORCH_STATE_SHEART); break;
					}
			}
		}
	}

	//Morning Star collsion with breackable brick
	for (int i = 0; i < bricks.size(); i++)
	{
		if (MS->CheckCollision(bricks.at(i)))
		{
			if (bricks.at(i)->state != BRICK_STATE_NORMAL)
			{
				effect = new Effect(camera);
				effect->SetPosition(bricks.at(i)->x - 30, bricks.at(i)->y - 20);
				effect->SetType(EFFECT_TYPE_BRICK);
				effects.push_back(effect);
				if (bricks.at(i)->GetState() == BBRICK_STATE_NORMAL)
				{
					bricks.at(i)->SetActive(false);
				}
				else if (bricks.at(i)->GetState() == BBRICK_STATE_CHIKEN_BRICK)
				{
					bricks.at(i)->SetState(BBRICK_STATE_CHIKEN);
				}
				else if (bricks.at(i)->GetState() == BBRICK_STATE_MONEY_BRICK)
				{
					bricks.at(i)->SetState(BBRICK_STATE_MONEY);
				}
				else if (bricks.at(i)->GetState() == BBRICK_STATE_DOUBLE_SHOOT_BRICK)
				{
					bricks.at(i)->SetState(BBRICK_STATE_DOUBLE_SHOOT);
				}
			}
		}
	}
	for (int i = 0; i < effects.size(); i++)
	{
		if (effects.at(i)->GetActive() == false)
		{
			effects.erase(effects.begin() + i);
		}
	}
	for (int i = 0; i < bricks.size(); i++)
	{
		if (bricks.at(i)->GetActive() == false)
		{
			bricks.erase(bricks.begin() + i);
		}
	}
	for (int i = 0; i < torches.size(); i++)
	{
		if (torches.at(i)->GetActive() == false)
		{
			torches.erase(torches.begin() + i);
		}
	}
	for (int i = 0; i < invisibleobjects.size(); i++)
	{
		if (invisibleobjects.at(i)->GetActive() == false)
		{
			invisibleobjects.erase(invisibleobjects.begin() + i);
		}
	}

	//Delete object when unactive
	for (int i = 0; i < weapon.size(); i++)
	{
		if (weapon.at(i)->GetActive() == false)
		{
			weapon.erase(weapon.begin() + i);
		}
	}
	for (int i = 0; i < effects.size(); i++)
	{
		if (effects.at(i)->GetActive() == false)
		{
			effects.erase(effects.begin() + i);
		}
	}
	for (int i = 0; i < bricks.size(); i++)
	{
		if (bricks.at(i)->GetActive() == false)
		{
			bricks.erase(bricks.begin() + i);
		}
	}
	for (int i = 0; i < torches.size(); i++)
	{
		if (torches.at(i)->GetActive() == false)
		{
			torches.erase(torches.begin() + i);
		}
	}
	for (int i = 0; i < invisibleobjects.size(); i++)
	{
		if (invisibleobjects.at(i)->GetActive() == false)
		{
			invisibleobjects.erase(invisibleobjects.begin() + i);
		}
	}

	//Adjust Camera to Simon
	if (camera->GetPosition().x + SCREEN_WIDTH != endmap)
	{
		if (simon->x - camera->GetPosition().x <= 100 && SimonMove == true)
		{
			simon->StartAutoWalking(SIMON_AUTO_GO_TIME * 2);
		}
		if (camera->GetCamMove() == 0 && simon->nx > 0)
		{
			if ((simon->x + SIMON_IDLE_BBOX_WIDTH) - camera->GetPosition().x >= SCREEN_WIDTH / 2)
				camera->SetCamera((simon->x + SIMON_IDLE_BBOX_WIDTH) - SCREEN_WIDTH / 2, 0);
		}
		if (simon->nx < 0)
		{
			camera->SetCamera((simon->x + SIMON_IDLE_BBOX_WIDTH) - SCREEN_WIDTH / 2, 0);
		}
		if (simon->GetStartPoint() == SIMON_START_UNDERGROUND)
		{
			camera->SetCamera((simon->x + SIMON_IDLE_BBOX_WIDTH) - SCREEN_WIDTH / 2, 200);
		}

	}


	//Update Objects
	for (int i = 0; i < torches.size(); i++)
	{
		torches[i]->Update(dt, &bricks);
	}

	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Update(dt, &bricks);
	}
	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i]->Update(dt, &bricks);
	}
	for (int i = 0; i < weapon.size(); i++)
	{
		weapon[i]->Update(dt, &bricks);
	}
	camera->Update(dt, startpoint, endpoint);
	simon->Update(dt, &bricks);
	MS->Update(dt, &bricks);
	gameTime->Update(dt);
}

void SceneGame::Render()
{
	Tile->DrawMap(camera);
	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i]->Render(camera);
	}
	for (int i = 0; i < torches.size(); i++)
	{
		torches[i]->Render(camera);
	}
	for (int i = 0; i < invisibleobjects.size(); i++)
	{
		invisibleobjects[i]->Render(camera);
	}
	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Render(camera);
	}
	simon->Render(camera);
	MS->Render(camera);
	for (int i = 0; i < weapon.size(); i++)
	{
		weapon[i]->Render(camera);
	}
	board->Render(simon, 1, GAME_TIME_MAX - gameTime->GetTime(), NULL);
	
}
