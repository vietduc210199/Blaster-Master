#include "SceneGame.h"
#include "define.h"



SceneGame::SceneGame()
{
	
	game = CGame::GetInstance();
	
	AnimationsManager* animations = AnimationsManager::getInstance();
	
	InitGame();
}

void SceneGame::InitGame()
{
	camera = new Camera();

	grid = new Grid();
	simon = new CSimon();

	MS = new CMS();
	MS->GetSimon(simon);

	//Hidden money
	hiddenmoney = new CTorch();
	hiddenmoney->SetState(TORCH_STATE_MONEY4);
	hiddenmoney->SetActive(false);

	//Boss
	phantombat = new Boss(simon, MS, camera);
	phantombat->SetState(BOSS_STATE_SLEEP);
	phantombat->SetActive(false);

	LoadResources(SOURCE_ENTRANCE_PNG, eType::ID_TEX_ENTRANCESTAGE, SOURCE_ENTRANCE_TXT, ID_SCENE_LEVEL_ENTRANCE);
	//LoadResources(SOURCE_CASTLE_PNG, eType::ID_TEX_CASTLE, SOURCE_CASTLE_TXT, ID_SCENE_LEVEL_CASTLE);

	//tokens
	dagger = new Dagger(camera, simon->nx);
	axe = new Axe(simon->GetPosition().x, camera, simon->nx);
	Holywater = new HolyWater(simon->GetPosition().x, camera, simon->nx);

	//board
	gameTime = new GameTime();
	gameTime->SetTime(0);

	board = new Board(BOARD_DEFAULT_POSITION_X, BOARD_DEFAULT_POSITION_Y);

	/*stagename = 0;
	simon->SetStartPoint(stages.at(stagename)->startpoint);
	simon->SetEndPoint(stages.at(stagename)->endpoint);
	camera->SetStartPoint(stages.at(stagename)->startpoint);
	camera->SetEndPoint(stages.at(stagename)->endpoint);
	simon->SetPosition(stages.at(stagename)->simonposx, stages.at(stagename)->simonposy);*/
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
					if (simon->GetWalk1Stair() == 0)
					{
						simon->SetState(SIMON_STATE_WALKING_DOWN_STAIR);
						simon->StartWalk1Stair();
					}
					else return;
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
					if (simon->GetWalk1Stair() == 0)
					{
						simon->SetState(SIMON_STATE_WALKING_UP_STAIR);
						simon->StartWalk1Stair();
					}
					else return;
				}
			}
		}
	}
	else
	{
		if (simon->GetWalk1Stair() == 0)
			simon->SetState(SIMON_STATE_IDLE);
		else if(simon->GetState() == SIMON_STATE_WALKING_UP_STAIR)
			simon->SetState(SIMON_STATE_WALKING_UP_STAIR);
		else if(simon->GetState() == SIMON_STATE_WALKING_DOWN_STAIR)
			simon->SetState(SIMON_STATE_WALKING_DOWN_STAIR);

	}
}

void SceneGame::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (!isGameOver)
	{
		if (simon->GetState() == SIMON_STATE_DIE || simon->GetChangeColorTime() != 0 || simon->GetAutoWalkingTime() != 0 || camera->GetCamMove() == true || simon->GetIsDamaged() != 0 || simon->GetHealth() == 0) return;
		switch (KeyCode)
		{
		case DIK_R:
			CGame::GetInstance()->SetDebugging();
			break;
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
						phantombat->GetSimonDagger(dagger);
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
						phantombat->GetSimonAxe(axe);
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
	else {
		switch (KeyCode){
		case DIK_1:
			isGameOver = false;
			InitGame();
			break;
		case DIK_2:
			DestroyWindow(CGame::GetInstance()->getHWND());
		default:
			break;
		}
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
	hiddenmoney->SetPosition(hiddenmoneyposx, hiddenmoneyposy);
	phantombat->SetPosition(bossposx, bossposy);
	phantombat->SetFirstPos(bossposx, bossposy * 2);
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

void SceneGame::LoadPantherPosFromFile(string source)
{
	int flag = 0;
	int number;
	int* arr = new int[20];
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
					panther = new Panther(simon, camera, arr[1]);
					panther->nx = -1;
					panther->SetPosition(arr[1], arr[2]);
					enemy.push_back(panther);
					flag = 0;
				}
			}
		}
	}
}



void SceneGame::Update(DWORD dt)
{ 
	if (isGameOver) return;
	if (simon->GetLives() < 0 || GAME_TIME_MAX - gameTime->GetTime() < 0) isGameOver = true;

	if (simon->y > camera->cam_y + 260)
	{
		simon->SetLives(-1);
		simon->SetPosition(stages.at(stagename)->simonposx, stages.at(stagename)->simonposy);
		simon->SetStartPoint(stages.at(stagename)->startpoint);
		simon->SetEndPoint(stages.at(stagename)->endpoint);
		camera->SetCamerax(camera->GetStartPoint());
		simon->StartIsUnTouchable(SIMON_UNTOUCHABLE_TIME);
	}
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
				simon->SetHeart(2);
				break;
			case TORCH_STATE_SHEART:
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
				enemy.clear();
				break;
			case TORCH_STATE_CLOCK:
				torch->SetActive(false);
				StopEnemyStart();
				break;
			case TORCH_STATE_INVI_POT:
				torch->SetActive(false);
				simon->StartIsUnTouchable(SIMON_UNTOUCHABLE_TIME * 2);
				break;
			case TORCH_STATE_MONEY1:
				simon->SetScores(100);
				torch->SetActive(false);
				break;
			case TORCH_STATE_MONEY2:
				simon->SetScores(200);
				torch->SetActive(false);
				break;
			case TORCH_STATE_MONEY3:
				simon->SetScores(500);
				torch->SetActive(false);
				break;
			case TORCH_STATE_MONEY4:
				simon->SetScores(1000);
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
	if (simon->CheckCollision(hiddenmoney) && hiddenmoney->GetActive() == true)
	{
		simon->SetScores(1000);
		hiddenmoney->SetActive(false);
	}

	//Simon collision with Invisible Objects
	for (int i = 0; i < invisibleobjects.size(); i++)
	{
		InviObjects* InOb = dynamic_cast<InviObjects*>(invisibleobjects[i]);
		if (simon->CheckCollision(InOb))
		{
			/*DebugOut(L"Type ID: %d", InOb->type);
			DebugOut(L"  Postion: %d\n", InOb->x);*/

			if (InOb->type == SC_TYPE_CHANGE_SCENE && simon->nx >= 0)
			{
				if (simon->GetAutoWalkingTime() == 0)
				{
					LoadResources(SOURCE_CASTLE_PNG, ID_TEX_CASTLE, SOURCE_CASTLE_TXT, 2);
				}
			}
			else if (InOb->type == SC_TYPE_AUTO_HELPER && simon->nx >= 0)
			{
				InOb->SetActive(false);
				simon->SetDirection(1);
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
			else if (InOb->type == SC_TYPE_UNDER_GROUND && simon->GetOnStair())
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
				DebugOut(L"Postion Y: %d\n", stages.at(stagename)->simonposy);
				DebugOut(L"Postion X: %d\n", stages.at(stagename)->simonposx);
			}
			else if (InOb->type == SC_TYPE_UNDER_TO_LAND && simon->GetOnStair())
			{
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
					DebugOut(L"statename: %d\n", stagename);
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
			else if (InOb->type == MONEY_SPAWNER)
			{
				InOb->SetActive(false);
				hiddenmoney->SetActive(true);
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
					simon->StopWalkStair();
				}
			}
			else if (InOb->type == STAIR_TYPE_DOWN_LEFT )
			{
				if (game->IsKeyDown(DIK_DOWN) && !simon->GetOnStair() && simon->GetWalk1Stair() == 0)
				{
					DebugOut(L"IN %d\n");
					if (simon->x >= InOb->x - 15 || simon->x < InOb->x - 15 && simon->GetOnStair() == false )
					{
						simon->x = InOb->x - 15;
					}
					if (simon->x >= InOb->x - 15 || simon->x <= InOb->x - 16)
					{
						simon->SetOnStair(true);
						simon->SetStairUp(true);
						simon->nx = -1;
						simon->SetState(SIMON_STATE_WALKING_DOWN_STAIR);
						simon->StartWalk1Stair();
					}
				}
				else if (game->IsKeyDown(DIK_UP))
				{
					if (simon->GetOnStair())
					{
						if (simon->y + SIMON_IDLE_BBOX_HEIGHT > InOb->y + INVI_HEIGHT)
						{
							simon->y = InOb->y + INVI_HEIGHT * 2 - SIMON_IDLE_BBOX_HEIGHT + 1;
							simon->x += 3;
						}
						simon->SetState(SIMON_STATE_IDLE);
						simon->SetOnStair(false);
						simon->SetStairUp(false);
						simon->StopWalkStair();
					}
				}
			}
			else if (InOb->type == STAIR_TYPE_UP_LEFT)
			{
				if (game->IsKeyDown(DIK_UP))
				{
					if (simon->x <= InOb->x - 23.5)
					{
						DebugOut(L"UPPPPPPPP: %d\n");
						simon->SetOnStair(true);

						simon->SetState(SIMON_STATE_WALKING_UP_STAIR);
						simon->StartAutoWalking(SIMON_AUTO_GO_TIME);
						simon->SetStairUp(false);
						simon->nx = -1;

					}
					else if (InOb->x - simon->x >=20)
					{
						DebugOut(L"Check &d\n");
						simon->x = InOb->x - 23.5;
					}
				
				}
				else if (game->IsKeyDown(DIK_DOWN))
				{
					simon->SetOnStair(false);
					simon->SetStairUp(true);
					simon->StopWalkStair();
				}
			}
			else if (InOb->type == STAIR_TYPE_DOWN_RIGHT)
			{

				if (game->IsKeyDown(DIK_DOWN) && !simon->GetOnStair() && simon->GetWalk1Stair() == 0)
				{
					if (simon->x >= InOb->x - 5 || simon->x < InOb->x - 6 && simon->GetOnStair() == false)
					{ 
						simon->x = InOb->x - 5;
					}
					if (simon->x == InOb->x - 5)
					{
						simon->SetOnStair(true);
						simon->SetStairUp(false);
						simon->nx = 1;
						simon->SetState(SIMON_STATE_WALKING_DOWN_STAIR);
						simon->StartWalk1Stair();
					}
				}
				else if (game->IsKeyDown(DIK_UP) && simon->GetOnStair() == true)
				{
					if (simon->GetOnStair())
					{
						if (simon->y + SIMON_IDLE_BBOX_HEIGHT > InOb->y + INVI_HEIGHT)
						{
							simon->y = InOb->y + 0.5 + INVI_HEIGHT * 2 - SIMON_IDLE_BBOX_HEIGHT - 3;
							simon->x -= 2;
						}
						simon->SetState(SIMON_STATE_IDLE);
						simon->SetOnStair(false);
						simon->SetStairUp(true);
						simon->StopWalkStair();
					}
				
				}
			}
			else if (InOb->type == GHOUL_SPAWNER)
			{
				if (spawndelayghoul == 0)
				{
					int a;
					srand(time(NULL));
					a = rand() % 4 + 1;
					for (int i = 0; i < a; i++)
					{
						ghoul = new Ghoul();
						ghoul->nx = 1;
						ghoul->SetPosition(camera->GetPosition().x - 20 - i * 20, ghouly);
						enemy.push_back(ghoul);
					}
					for (int i = 0; i < (4 - a); i++)
					{
						ghoul = new Ghoul();
						ghoul->nx = -1;
						ghoul->SetPosition(camera->GetPosition().x + SCREEN_WIDTH + i * 20, ghouly);
						enemy.push_back(ghoul);
					}
					SpawnDelayGhoulStart();
				}
			}
			else if (InOb->type == PANTHER_SPAWNER)
			{
				if (spawndelaypanther == 0)
				{
					LoadPantherPosFromFile(SOURCE_PANTHER_POS_TXT);
					SpawnDelayPantherStart();
				}
			}
			else if (InOb->type == BAT_SPAWNER)
			{
				if (spawndelaybat == 0)
				{
					bat = new Bat(D3DXVECTOR2(simon->GetPosition().x, simon->GetPosition().y));
					bat->nx = -1;
					bat->SetPosition(camera->GetPosition().x + SCREEN_WIDTH, simon->GetPosition().y);
					enemy.push_back(bat);
					SpawnDelayBatStart();
				}
			}
			else if (InOb->type == FISHMAN_SPAWNER)
			{
				if (spawndelayfishman == 0)
				{
					fishman = new Fishman(simon, MS, camera, InOb->x - 50);
					fishman->nx = -1;
					fishman->SetPosition(InOb->x - 50, InOb->y + 120);
					enemy.push_back(fishman);
					effect = new Effect(camera);
					effect->SetType(EFFECT_TYPE_WATER);
					effect->SetPosition(InOb->x - 60, InOb->y + 50);
					effects.push_back(effect);

					fishman = new Fishman(simon, MS, camera, InOb->x + 40);
					fishman->nx = 1;
					fishman->SetPosition(InOb->x + 40, InOb->y + 120);
					enemy.push_back(fishman);
					effect = new Effect(camera);
					effect->SetType(EFFECT_TYPE_WATER);
					effect->SetPosition(InOb->x + 50, InOb->y + 50);
					effects.push_back(effect);
					SpawnDelayFishmanStart();
				}
			}
			else if (InOb->type == BOSS_SPAWNER && phantombat->GetState() == BOSS_STATE_SLEEP)
			{
			//InOb->SetActive(false);
			
			phantombat->SetActive(true);
			}
		}
	}

	//Weapon collision with torch
	for (int i = 0; i < torches.size(); i++)
	{
		CTorch* torch = dynamic_cast<CTorch*>(torches[i]);
		if (MS->CheckCollision(torch) || dagger->CheckCollision(torch) || axe->CheckCollision(torch))
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
				int b;
				
				srand(time(NULL));
				a = rand() % 15 + 1;
				if (MS->MSUpDropTime < 3)
				{
					torch->SetState(TORCH_STATE_MSUP);
				}
				else
					switch (a)
					{
					case 1:
					case 2:
					case 3:
						torch->just_die = 1;
						torch->StartDieTime();
						
						break;
					case 4:
					case 5:
						b = rand() % 4 + 1;
						switch (b)
						{
						case 1:
							torch->SetState(TORCH_STATE_DAGGER); break;
						case 2:
							torch->SetState(TORCH_STATE_HOLYWATER); break;
						case 3:
							torch->SetState(TORCH_STATE_CROSS); break;
						case 4: 
							torch->SetState(TORCH_STATE_AXE); break;
						}
						break;
					case 6:
						b = rand() % 10 + 1;
						switch (b)
						{
						case 1:
						case 2:
						case 3:
						case 4:
							torch->SetState(TORCH_STATE_MONEY1);
							break;
						case 5:
						case 6:
						case 7:
							torch->SetState(TORCH_STATE_MONEY2);
							break;
						case 8:
						case 9:
							torch->SetState(TORCH_STATE_MONEY3);
							break;
						case 10:
							torch->SetState(TORCH_STATE_MONEY4);
							break;
						default:
							break;
						}
						break;
					default:
						b = rand() % 8 + 1;
						switch (b)
						{
						case 1:
							torch->SetState(TORCH_STATE_LHEART); break;
						default:
							torch->SetState(TORCH_STATE_SHEART); break;
						}
						break;
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
	
	//Simon Collision with enemy
	for (int i = 0; i < enemy.size(); i++)
	{
		if (simon->CheckCollision(enemy.at(i)))
		{
			if (enemy.at(i)->GetState() == ENEMY_STATE_MOVING)
			{
				if (simon->GetUntouchable() == 0)
				{
					if (enemy.at(i)->nx > 0)
					{
						simon->nx = -1;
					}
					else simon->nx = 1;
					if (simon->GetOnStair() == false)
					{
						simon->StartIsDamaged();
					}
					if (simon->GetHealth() <= 2)
						simon->SetLives(-1);
					simon->SetHealth(2);
					
					simon->StartIsUnTouchable(SIMON_UNTOUCHABLE_TIME);
				}
				if (enemy.at(i)->type == BAT)
				{
					enemy.at(i)->StartDieTime();
					enemy.at(i)->SetState(ENEMY_STATE_DIE);
					simon->SetHealth(2);
				}
			}
			else switch (enemy.at(i)->GetState())
			{
			case ENEMY_STATE_SHEART:
				simon->SetHeart(1);
				enemy.erase(enemy.begin() + i);
				break;
			case ENEMY_STATE_MONEY1:
				simon->SetScores(100);
				enemy.erase(enemy.begin() + i);
				break;
			case ENEMY_STATE_MONEY2:
				simon->SetScores(200);
				enemy.erase(enemy.begin() + i);
				break;
			case ENEMY_STATE_MONEY3:
				simon->SetScores(500);
				enemy.erase(enemy.begin() + i);
				break;
			case ENEMY_STATE_MONEY4:
				simon->SetScores(1000);
				enemy.erase(enemy.begin() + i);
				break;
			case ENEMY_STATE_DAGGER:
				simon->SetThrowDagger(true);
				simon->SetThrowAxe(false);
				simon->SetThrowHolyWater(false);
				enemy.erase(enemy.begin() + i);
				break;
			case ENEMY_STATE_AXE:
				simon->SetThrowDagger(false);
				simon->SetThrowAxe(true);
				simon->SetThrowHolyWater(false);
				enemy.erase(enemy.begin() + i);
				break;
			case ENEMY_STATE_HOLYWATER:
				simon->SetThrowDagger(false);
				simon->SetThrowAxe(false);
				simon->SetThrowHolyWater(true);
				enemy.erase(enemy.begin() + i);
				break;
			default:
				break;
			}
		}
	}

	//simon collision with boss
	if(phantombat->GetActive())
		if (simon->CheckCollision(phantombat))
		{
			if (phantombat->GetState() == BOSS_STATE_BLOOD)
			{
				phantombat->SetActive(false);
				this->isGameOver = true;
			}
			else
			{
				if (simon->GetUntouchable() == 0)
				{
					if (simon->GetOnStair() == false)
					{
						if (simon->GetHealth() <= 4)
						{
							phantombat->SetState(BOSS_STATE_SLEEP);
							//phantombat->SetActive(false);
							phantombat->SetPosition(bossposx, bossposy);
							phantombat->SetFirstPos(bossposx, bossposy * 2);
							simon->SetLives(-1);
							
						}
						simon->StartIsDamaged();
						simon->SetHealth(4);
					}
					simon->StartIsUnTouchable(SIMON_UNTOUCHABLE_TIME);
				}
			}
		}

	//Weapon collision with enemy
	for (int i = 0; i < enemy.size(); i++)
	{
		if (MS->CheckCollision(enemy.at(i))
			|| dagger->CheckCollision(enemy.at(i)) && dagger->active == true
			|| axe->CheckCollision(enemy.at(i)) && axe->active == true
			|| Holywater->CheckCollision(enemy.at(i)) && Holywater->active == true)
		{
			dagger->SetActive(false);
			axe->SetActive(false);
			enemy.at(i)->FirstX = enemy.at(i)->x;
			if (enemy.at(i)->GetState() == ENEMY_STATE_MOVING
				|| enemy.at(i)->GetState() == ENEMY_STATE_IDLE
				|| enemy.at(i)->GetState() == ENEMY_STATE_ATTACK)
			{
				enemy.at(i)->StartDieTime();
				enemy.at(i)->SetState(ENEMY_STATE_DIE);
				enemy.at(i)->EnemySetStateDie();
				simon->SetScores(100);
			}
		}
	}

	//Deleate enemy when out of camera
	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy.at(i)->x < camera->GetPosition().x - (enemy.at(i)->GetBound().right - enemy.at(i)->GetBound().left) && enemy.at(i)->nx < 0)
		{
			if (enemy.at(i)->type == PANTHER)
				return;
			else enemy.erase(enemy.begin() + i);
		}
		else if (enemy.at(i)->x > camera->GetPosition().x + SCREEN_WIDTH && enemy.at(i)->nx > 0)
		{
			enemy.erase(enemy.begin() + i);
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
	if (camera->GetPosition().x + SCREEN_WIDTH >= endmap)
	{
		camera->SetCamerax(endmap);
		camera->SetCamLock(true);
	}
	else
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
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Update(dt, &bricks);
	}

	phantombat->Update(dt, &bricks);
	camera->Update(dt, startpoint, endpoint);
	simon->Update(dt, &bricks);
	MS->Update(dt, &bricks);
	gameTime->Update(dt);
	hiddenmoney->Update(dt, &bricks);


	//functiions that affect the scene
	if (GetTickCount() - spawndelayghoultimer_start > SPAWN_DELAY_TIMER)
	{
		spawndelayghoultimer_start = 0;
		spawndelayghoul = 0;
	}
	if (GetTickCount() - spawndelaybattimer_start > SPAWN_DELAY_TIMER)
	{
		spawndelaybattimer_start = 0;
		spawndelaybat = 0;
	}
	if (GetTickCount() - spawndelayfishmantimer_start > SPAWN_DELAY_TIMER)
	{
		spawndelayfishmantimer_start = 0;
		spawndelayfishman = 0;
	}
	if (GetTickCount() - spawndelaypanthertimer_start > SPAWN_DELAY_TIMER)
	{
		spawndelaypanthertimer_start = 0;
		spawndelaypanther = 0;
	}
	if (GetTickCount() - stopenemytimer_start > STOP_ENEMY_TIMER)
	{
		stopenemytimer_start = 0;
		stopenemy = 0;
	}
	if (stopenemy != 0)
	{
		for (int i = 0; i < enemy.size(); i++)
		{
			enemy.at(i)->isStop = true;
		}
	}
	if (stopenemy == 0)
	{
		for (int i = 0; i < enemy.size(); i++)
		{
			enemy.at(i)->isStop = false;
		}
	}
	if (simon->GetEatCross() == true)
	{
		isChangeColor = true;
		simon->SetEatCross(false);
	}
	if (isChangeColor)
	{
		if (timerChangeColor < 90)
		{
			isGrey = true;
			timerChangeColor += dt;
		}
		else
		{
			isGrey = false;
			timerChangeColor = 0;
			countChangeColor++;
		}
		if (countChangeColor >= 7)
		{
			isChangeColor = false;
			countChangeColor = 0;
		}
	}
	if (simon->GetHealth() == 0)
	{
		if (!camera->GetCamLock()) camera->SetCamLock(false);
		if (timerSimonDie < 1000)
		{
			timerSimonDie += dt;
		}
		else
		{
			timerSimonDie = 0;
			simon->SetPosition(stages.at(stagename)->simonrespawnx, stages.at(stagename)->simonrespawny);
			simon->SetHealth(-16);
			simon->nx = 1;
			camera->SetCamerax(stages.at(stagename)->startpoint);
		}
	}
}

void SceneGame::Render()
{
	if (!isGameOver)
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
		for (int i = 0; i < enemy.size(); i++)
		{
			enemy[i]->Render(camera);
		}
		phantombat->Render(camera);
		hiddenmoney->Render(camera);
		simon->Render(camera);
		MS->Render(camera);
		for (int i = 0; i < weapon.size(); i++)
		{
			weapon[i]->Render(camera);
		}
		board->Render(simon, stagename + 1, GAME_TIME_MAX - gameTime->GetTime(), phantombat);

	}
	else {
		Text.Draw(110, 70, "GAME OVER");
		Text.Draw(110, 100, "1 CONTINUE");
		Text.Draw(110, 120, "2 END");
	}
}
