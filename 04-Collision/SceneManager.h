#pragma once
#include "Scene.h"
class SceneManager
{
	static SceneManager* __instance;
	SceneManager* __currentScene;
	Scene* __scene;
public:
	SceneManager();
	~SceneManager();


	static SceneManager* GetInstance()
	{
		if (__instance == NULL) __instance = new SceneManager;
		return __instance;
	}

	SceneManager* GetCurrentScene();

	void SetScene(Scene* x);

	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void Update(DWORD dt);
	void Render();

	CSimon* getSimon()
	{
		return __scene->getSimon();
	}

	Scene* GetScene();
	
};

