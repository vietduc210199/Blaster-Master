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

#include "Ghoul.h"
#include "Panther.h"
#include "FireBullet.h"
#include "Fishman.h"
#include "Bat.h"
#include "Boss.h"

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
	CTorch* hiddenmoney;
	Effect* effect;

	Ghoul* ghoul;
	Bat* bat;
	Fishman* fishman;
	Panther* panther;
	FireBullet* firebullet;
	Boss* phantombat;

	vector<LPGAMEOBJECT> bricks;
	vector<LPGAMEOBJECT> torches;
	vector<LPGAMEOBJECT> invisibleobjects;
	vector<LPGAMEOBJECT> effects;
	vector<LPGAMEOBJECT> weapon;
	vector<LPGAMEOBJECT> enemy;

	vector<LPGAMEOBJECT> ObjectsFromGrid;
	vector<LPGAMEOBJECT> listobj;

	
	float startpoint, endpoint, camstoppoint;

	int stagename = 0;
	
	int countChangeColor;

	int spawndelayghoul = 0;
	int spawndelaybat = 0;
	int spawndelayfishman = 0;
	int spawndelaypanther = 0;
	int stopenemy;

	bool isChangeColor;
	bool isGrey;
	bool SimonMove = false;
	bool isGameOver = true;
	Font Text;

	DWORD spawndelayghoultimer_start;
	DWORD spawndelaybattimer_start;
	DWORD spawndelayfishmantimer_start;
	DWORD spawndelaypanthertimer_start;
	DWORD stopenemytimer_start;
	DWORD timerChangeColor;
	DWORD timerSimonDie;


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
	void LoadPantherPosFromFile(string source);

	void SpawnDelayGhoulStart() { spawndelayghoul = 1;  spawndelayghoultimer_start = GetTickCount(); }
	void SpawnDelayPantherStart() { spawndelaypanther = 1;  spawndelaypanthertimer_start = GetTickCount(); }
	void SpawnDelayBatStart() { spawndelaybat = 1;  spawndelaybattimer_start = GetTickCount(); }
	void SpawnDelayFishmanStart() { spawndelayfishman = 1;  spawndelayfishmantimer_start = GetTickCount(); }
	void StopEnemyStart() { stopenemy = 1; stopenemytimer_start = GetTickCount(); }

	void InitGame(); // khởi tạo lại như chơi từ đầu

	void Update(DWORD dt);
	void Render();

	CSimon* getSimon()
	{
		return this->simon;
	}
};

