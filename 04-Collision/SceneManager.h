#pragma once
#include "Scene.h"
class SceneManager
{
	static SceneManager* __instance;
	Scene* __scene;
public:
	SceneManager();
	~SceneManager();


	static SceneManager* GetInstance()
	{
		if (__instance == NULL) __instance = new SceneManager;
		return __instance;
	}

	void SetScene(Scene* x);

	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();

	CSimon* getSimon()
	{
		return __scene->getSimon();
	}

	Scene* GetScene();
	
};

