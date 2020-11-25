#include "SpritesManager.h"

SpritesManager* SpritesManager::__instance = NULL;

void SpritesManager::LoadResources()
{
	TextureManager* TexManager = TexManager->getInstance();

	LPDIRECT3DTEXTURE9 texEntrance = TexManager->getData()->Get(ID_TEX_ENTRANCESTAGE);

	int l = 0, r = 32;
	for (int i = 1; i <= 20; i++)
	{
		sprites->Add(i, l, 0, r, 32, texEntrance);
		l += 32;
		r += 32;
	}
	l = 0;
	r = 32;
	for (int i = 21; i <= 38; i++)
	{
		sprites->Add(i, l, 32, r, 64, texEntrance);
		l += 32;
		r += 32;
	}


	
	CSprites* sprites = CSprites::GetInstance();
	CTextures* textures = CTextures::GetInstance();
	vector<int> numbers;
	int flag = 0;
	int number;
	int arr[6];
	ifstream file_Simon("ReadFile\\sprite.txt");
	if (file_Simon.is_open())
	{
		while (!file_Simon.eof())
		{
			while (file_Simon >> number)
			{
				arr[flag] = number;
				flag++;
				if (flag == 6)
				{
					LPDIRECT3DTEXTURE9 tex = TexManager->getData()->Get(arr[0]);
					sprites->Add(arr[1], arr[2], arr[3], arr[4], arr[5], tex);
					flag = 0;
				}
			}
		}
	}
}
