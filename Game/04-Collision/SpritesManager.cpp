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


	LPDIRECT3DTEXTURE9 texSIMON = TexManager->getData()->Get(ID_TEX_SIMON);
	vector<int> numbers;

	int flag = 0;
	int number;
	int arr[5];
	ifstream file_mario("Simon.txt");
	if (file_mario.is_open())
	{
		while (!file_mario.eof())
		{
			while (file_mario >> number)
			{
				arr[flag] = number;
				flag++;
				if (flag == 5)
				{
					sprites->Add(arr[0], arr[1], arr[2], arr[3], arr[4], texSIMON);
					flag = 0;
				}
			}
		}
	}

	sprites->Add(10099, 215, 120, 231, 135, texSIMON);		// die 

	LPDIRECT3DTEXTURE9 texMisc = TexManager->getData()->Get(ID_TEX_MISC);
	sprites->Add(90001, 0, 0, 32, 32, texMisc);
	LPDIRECT3DTEXTURE9 texTorch = TexManager->getData()->Get(ID_TEX_TORCH);
	sprites->Add(90002, 47, 25, 64, 56, texTorch);

	LPDIRECT3DTEXTURE9 texEnemy = TexManager->getData()->Get(ID_TEX_ENEMY);
}
