#include "IntroScene.h"
#include "SceneManager.h"

IntroScene::IntroScene()
{
	LoadResources(NULL, 0, NULL, 0);
}

IntroScene::~IntroScene()
{
	SAFE_DELETE(simon);
	SAFE_DELETE(board);
}

void IntroScene::KeyState(BYTE* state)
{
}

void IntroScene::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_2) // lấy tọa độ world của chuột 
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(CGame::GetInstance()->getHWND(), &p);
		DebugOut(L"[MOUSE POSITION] %d %d \n", p.x, p.y);
	}
	else
	{
		isPressStart = true; // nhấn phím bất kì thì xác nhận đã nhấn
	}
}

void IntroScene::OnKeyUp(int KeyCode)
{

}

void IntroScene::LoadResources(LPCWSTR picturePath, int idTex, const char* filepath, int scene)
{
	_textureManager = TextureManager::getInstance();
	sprite_MainMenu = new CSprite(eType::MAINMENU, 0, 0, 305, 216, _textureManager->getData()->Get(eType::MAINMENU), 0);
	sprite_IntroBatMenu = new CSprite(eType::INTRO_BAT_MENU, 0, 0, 365, 171, _textureManager->getData()->Get(eType::INTRO_BAT_MENU), 100, 15, 5, 3);

	StatusProcess = INTRO_STATUS_PROCESS_MENU;
	TimeWaited = 0;
	isPressStart = 0;

	isDrawTextPressStart = true;

	camera = new Camera();
	camera->SetCamera(0, 0);
	brick = new CBrick();

	simon = new CSimon();
	simon->SetStartPoint(0);
	simon->SetEndPoint(280);
	camera->SetStartPoint(0);
	camera->SetEndPoint(280);
	board = new Board(BOARD_DEFAULT_POSITION_X, BOARD_DEFAULT_POSITION_Y);

	Sprite_IntroGoScene1 = new CSprite(eType::INTRO_GO_SCENE1, 0, 0, 305, 224, _textureManager->getData()->Get(eType::INTRO_GO_SCENE1), 0);

	heliCopter = new HeliCopter(250, 70);
	introBat1 = new IntroBat(200, 55, -0.02, 0);
	introBat2 = new IntroBat(50, 100, 0.02, -0.01); 
}

void IntroScene::Update(DWORD dt)
{
	switch (StatusProcess)
	{
	case INTRO_STATUS_PROCESS_MENU:
	{
		if (!isPressStart) // chưa nhấn phím thì update sprite
			sprite_IntroBatMenu->Update(dt);
		if (isPressStart)
		{
			TimeWaited += dt;
			if (TimeWaited >= 1000)
			{ // qua trạng thái 2
				StatusProcess = INTRO_STATUS_PROCESS_GO_SCENE1;

				this->brick->SetMulwidth(20);
				this->brick->SetPosition(0, 200);
				this->brick->SetActive(true);
				listBrick.push_back(brick);

				simon->SetActive(true);
				simon->SetPosition(217, 169);
				simon->SetDirection(-1);
				simon->StartAutoWalking(3000);
			}
			else
			{
				TimeWaitedToChangeDisplayTextPressStart += dt;
				if (TimeWaitedToChangeDisplayTextPressStart >= 150)
				{
					TimeWaitedToChangeDisplayTextPressStart = 0;
					isDrawTextPressStart = !isDrawTextPressStart; // lật trạng thái
				}
			}
		}
		break;
	}
	case INTRO_STATUS_PROCESS_GO_SCENE1:
	{
		for (int i = 0; i < listBrick.size(); i++)
		{
			listBrick[i]->Update(dt, &listBrick);
		}
		if (TimeWaited >= 3000)
		{
			simon->SetState(SIMON_STATE_BACK);
		}
		heliCopter->Update(dt);


		introBat1->Update(dt);
		introBat2->Update(dt);
		simon->Update(dt, &listBrick);
		TimeWaited += dt;
		if (TimeWaited >= 5000)
			SceneManager::GetInstance()->SetScene(new SceneGame());
		break;
	}
	}
}

void IntroScene::Render()
{
	switch (StatusProcess)
	{
	case INTRO_STATUS_PROCESS_MENU:
	{
		sprite_MainMenu->Draw(0, 0);
		sprite_IntroBatMenu->DrawFrame(sprite_IntroBatMenu->GetCurrentFrame(), 203, 97, 3, sprite_IntroBatMenu->GetFrameWidth(), sprite_IntroBatMenu->GetFrameHeight(), 3);
		if (isDrawTextPressStart)
			textPressToStart.Draw(90, 130, "PUSH START KEY");
		break;
	}
	case INTRO_STATUS_PROCESS_GO_SCENE1:
	{
		Sprite_IntroGoScene1->Draw(0, 0);
		brick->Render(camera);
		heliCopter->Render(camera);
		introBat1->Render(camera);
		introBat2->Render(camera);
		simon->Render(camera);
		break;
	}
	}
}
