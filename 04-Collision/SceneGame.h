#pragma once
#include "Scene.h"
#include "camera.h"
#include "AnimationsManager.h"

#include "Simon.h"
#include "Torch.h"
#include "Brick.h"
#include "Grid.h"

#define ID_SCENE_LEVEL_ENTRANCE 1


class SceneGame : public Scene 
{
private:
	Grid* grid;

	camera* camera;

	CSimon* simon;
	CMS* MS;

	int currentLevel;

	vector<LPGAMEOBJECT> listobj;
public: 
	SceneGame();
	~SceneGame();

	void SetScene(int IDLevel);

	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources();

	void InitGame(); // khởi tạo lại như chơi từ đầu

	void Update(DWORD dt);
	void Render();

	CSimon* getSimon()
	{
		return this->simon;
	}

	
};

