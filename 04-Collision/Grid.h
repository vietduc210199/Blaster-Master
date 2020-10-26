#pragma once
#include "Unit.h"
#include "define.h"
#include "Game.h"
#include "GameObject.h"
#include "camera.h"

using namespace std;

#define GRID_CELL_WIDTH (SCREEN_WIDTH/4.0f)
#define GRID_CELL_HEIGHT (SCREEN_HEIGHT/4.0f)

#define GRID_CELL_MAX_ROW 20 // số dòng tối đa;
#define GRID_CELL_MAX_COLUMN 100 // số cột tối đa

class Grid
{
private:
	vector<CGameObject*> cells[GRID_CELL_MAX_ROW][GRID_CELL_MAX_COLUMN];
	char* filepath;
public:
	Grid();
	~Grid();

	void SetFile(char* str); //đọc các Objects từ file
	void ReloadGrid();

	CGameObject* GetNewObject(int type, float x, float y, int w, int h, int Model); 
	void Insert(int id, int type, int direction, float x, float y, int w, int h, int Model); //Thêm object vào grid
	void GetListObject(vector<CGameObject*>& ListObj, camera* camera);

};

