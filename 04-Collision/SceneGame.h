#pragma once
#include "Scene.h"
#include "camera.h"
#include "AnimationsManager.h"

#include "Simon.h"
#include "Torch.h"
#include "Brick.h"
#include "Grid.h"
#include "TileMap.h"
#include "Stage.h"
#include "InviObjects.h"

#define ID_SCENE_LEVEL_ENTRANCE 1
#define ID_SCENE_LEVEL_CASTLE 2


class SceneGame : public Scene 
{
private:
	Grid* grid;
	CGame* game;
	vector<Stage*> stages;
	Stage* stage;
	TileMap* Tile;
	InviObjects* InObj;

	Camera* camera;

	CSimon* simon;
	CMS* MS;
	CBrick* brick;
	CTorch* torch;

	int currentLevel;

	vector<LPGAMEOBJECT> bricks;
	vector<LPGAMEOBJECT> torchs;
	vector<LPGAMEOBJECT> invisibleobjects;


	vector<LPGAMEOBJECT> ObjectsFromGrid;
	vector<LPGAMEOBJECT> listobj;

	bool SimonMove = false;

	float startpoint, endpoint, camstoppoint;


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

	void SetScene(int IDLevel);

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

