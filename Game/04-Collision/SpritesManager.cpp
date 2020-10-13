#include "SpritesManager.h"
#include "TextureManager.h"

void SpritesManager::LoadSprites()
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


}
