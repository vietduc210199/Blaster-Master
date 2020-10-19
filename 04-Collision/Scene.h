#pragma once
#include "Game.h"
#include "Simon.h"

class Scene
{
public:
	Scene();

	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;

	virtual void LoadResources() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

	virtual CSimon* getSimon() = 0;

	virtual ~Scene();

};

