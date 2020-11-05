#include "TileMap.h"
#pragma warning(disable : 4996)

TileMap::TileMap(LPCWSTR picturePath, int id, int translate_y, int translate_x)
{
	this->id = id;
	this->translate_y = translate_y;
	this->translate_x = translate_x;

	textures->Add(id, picturePath, D3DCOLOR_XRGB(alpha, alpha, alpha));

	LPDIRECT3DTEXTURE9 tex = textures->Get(this->id);

	if (id == eType::ID_TEX_ENTRANCESTAGE)
	{
		rowtile = 4;
	}
	else if (id == eType::ID_TEX_CASTLE)
	{
		rowtile = 43;
	}

	int t = 0;
	int k = 0;
	for (int j = 0; j < rowtile; j++)
	{
		int l = 0, r = 16;
		for (int i = t; i <= t + 15; i++)
		{
			sprites->Add(i, l, k, r, k + 16, tex);
			l += 16;
			r += 16;
		}
		t += 16;
		k += 16;
	}
}

void TileMap::LoadMap(const char* filepath)
{
	FILE* pFile;
	pFile = fopen(filepath, "r");

	fscanf(pFile, "%d %d %d %d", &rowTileset, &colTileset, &width, &height);

	for (int i = 0; i < rowTileset; i++)
	{
		for (int j = 0; j < colTileset; j++)
		{
			fscanf(pFile, "%d", &listTile[i][j]);

		}
	}
	fclose(pFile);
}

void TileMap::DrawMap(camera* camera)
{
	remain_y = fmod(camera->GetCam_y(), height);
	remain_x = fmod(camera->GetCam_x(), width);

	int colCamLeft = camera->GetCam_x() / width;
	int colCamRight = colCamLeft + SCREEN_WIDTH / width;
	int rowCamTop = camera->GetCam_y() / height;
	int rowCamBottom = rowCamTop + SCREEN_HEIGHT / height;

	for(int j = colCamLeft; j <= colCamRight; j++)
		for (int i = rowCamTop; i <= rowCamBottom; i++)
		{
			float pos_x = (j - colCamLeft) * width - remain_x + translate_x;
			float pos_y = (i - rowCamTop) * height - remain_y + translate_y;
			int index = listTile[i][j];
			sprites->Get(index)->Draw(pos_x, pos_y, 255);
		}
}

void TileMap::Update()
{
}

TileMap::~TileMap()
{
}
