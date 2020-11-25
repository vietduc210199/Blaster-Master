#pragma once
#include "Scene.h"
#include "camera.h"
#include "AnimationsManager.h"
#include "GameTime.h"

#include "Simon.h"
#include "Torch.h"
#include "Brick.h"
#include "Grid.h"
#include "TileMap.h"
#include "Stage.h"
#include "InviObjects.h"
#include "Effect.h"
#include "Axe.h"
#include "Dagger.h"
#include "HolyWater.h"
#include "Board.h"

#define ID_SCENE_LEVEL_ENTRANCE 1
#define ID_SCENE_LEVEL_CASTLE 2

#define GAME_TIME_MAX 300


class SceneGame : public Scene 
{
private:
	Grid* grid;
	CGame* game;
	vector<CStage*> stages;
	CStage* stage;
	TileMap* Tile;
	InviObjects* InObj;

	GameTime* gameTime;
	Camera* camera;
	Board* board;

	CSimon* simon;
	CMS* MS;
	Dagger* dagger;
	Axe* axe;
	HolyWater* Holywater;
	CBrick* brick;
	CTorch* torch;
	Effect* effect;

	int currentLevel;

	vector<LPGAMEOBJECT> bricks;
	vector<LPGAMEOBJECT> torches;
	vector<LPGAMEOBJECT> invisibleobjects;
	vector<LPGAMEOBJECT> effects;
	vector<LPGAMEOBJECT> weapon;
	vector<LPGAMEOBJECT> enemy;



	vector<LPGAMEOBJECT> ObjectsFromGrid;
	vector<LPGAMEOBJECT> listobj;

	bool SimonMove = false;

	float startpoint, endpoint, camstoppoint;

	int stagename = 0;


	//read from file
	int hiddenmoneyposx;
	int hiddenmoneyposy;
	int bossposx;
	int bossposy;
	int startmap;
	int endmap;
	int ghouly;
	int effectdoory;
public: 
	SceneGame();
	~SceneGame();

	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void LoadResources(LPCWSTR picturePath, int idTex, const char* filepath, int scene);
	void LoadSceneElement(int scene);
	void LoadStageVariableFromFile(string source);
	void LoadElementFromFile(string source);
	void LoadSceneObject(int scene);
	void LoadObjectFromFile(string source);
	void LoadStageVaribale(int scene);

	void InitGame(); // khởi tạo lại như chơi từ đầu

	void Update(DWORD dt);
	void Render();

	CSimon* getSimon()
	{
		return this->simon;
	}
};

