#include "SceneManager.h"
SceneManager* SceneManager::__instance = NULL;


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::SetScene(Scene* x)
{
	Scene* scene_temp = __scene;
	__scene = x;
	if (scene_temp)
	{
		delete(scene_temp);
		scene_temp = nullptr;
	}
}

void SceneManager::KeyState(BYTE* state)
{
	__scene->KeyState(state);
}

void SceneManager::OnKeyDown(int KeyCode)
{
	__scene->OnKeyDown(KeyCode);
}

void SceneManager::OnKeyUp(int KeyCode)
{
	__scene->OnKeyUp(KeyCode);
}

void SceneManager::LoadResources()
{
	__scene->LoadResources();
}

void SceneManager::Update(DWORD dt)
{
	__scene->Update(dt);
}

void SceneManager::Render()
{
	__scene->Render();
}

Scene* SceneManager::GetScene()
{
	return __scene;
}
