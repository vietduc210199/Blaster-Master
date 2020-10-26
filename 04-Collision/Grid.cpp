#include "Grid.h"

Grid::~Grid()
{
	for (int i = 0; i < GRID_CELL_MAX_ROW; i++)
		for (int j = 0; j < GRID_CELL_MAX_COLUMN; j++)
		{
			cells[i][j].clear();
		}
}

void Grid::SetFile(char* str)
{
	filepath = str;
}

CGameObject* Grid::GetNewObject(int type, float x, float y, int w, int h, int Model)
{
	return nullptr;
}

void Grid::Insert(int id, int type, int direction, float x, float y, int w, int h, int Model)
{

	int top = (int)(y / GRID_CELL_HEIGHT);
	int bottom = (int)((y + h) / GRID_CELL_HEIGHT);
	int left = (int)(x / GRID_CELL_WIDTH);
	int right = (int)((x + w) / GRID_CELL_WIDTH);

	CGameObject* obj = GetNewObject(type, x, y, w, h, Model);
	if (obj == NULL)
		return;

	obj->SetId(id);
	obj->SetDirection(direction);

	for (int i = top; i <= bottom; i++)
		for (int j = left; j <= right; j++)
			cells[i][j].push_back(obj);
}
