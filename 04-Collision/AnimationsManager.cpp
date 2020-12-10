#include "AnimationsManager.h"


AnimationsManager* AnimationsManager::__instance = NULL;

void AnimationsManager::LoadResources()
{
	SpritesManager* spritesManager = spritesManager->getInstance();
	
	LoadAnimations(aniType::ANI_SIMON, "ReadFile\\Ani\\simonani.txt");
	LoadAnimations(aniType::ANI_GHOUL, "ReadFile\\Ani\\Ghoulani.txt");
	LoadAnimations(aniType::ANI_PANTHER, "ReadFile\\Ani\\Pantherani.txt");
	LoadAnimations(aniType::ANI_FISHMAN, "ReadFile\\Ani\\Fishmanani.txt");
	LoadAnimations(aniType::ANI_BAT, "ReadFile\\Ani\\Batani.txt");
	LoadAnimations(aniType::ANI_BRICK, "ReadFile\\Ani\\Brickani.txt");
	LoadAnimations(aniType::ANI_TORCH, "ReadFile\\Ani\\Torchani.txt");
	LoadAnimations(aniType::ANI_MS, "ReadFile\\Ani\\MSani.txt");
	LoadAnimations(aniType::ANI_AXE, "ReadFile\\Ani\\Axeani.txt");
	LoadAnimations(aniType::ANI_DAGGER, "ReadFile\\Ani\\Daggerani.txt");
	LoadAnimations(aniType::ANI_HOLYWATER, "ReadFile\\Ani\\Holywaterani.txt");
	LoadAnimations(aniType::ANI_PHANTOMBAT, "ReadFile\\Ani\\Bossani.txt");
	LoadAnimations(aniType::ANI_FIREBULLET, "ReadFile\\Ani\\Firebulletani.txt");
}

void AnimationsManager::LoadAnimations(int idAni, string source)
{
	vector<LPANIMATION> animation;
	int idani, time, idsprite;
	string all;
	ifstream infile;
	LPANIMATION ani;

	idani = 0;
	infile.open(source);

	while (!infile.eof())
	{
		int num_sprite;
		infile >> idani;
		ani = new CAnimation(100);
		infile >> num_sprite;
		for (int i = 0; i < num_sprite; i++)
		{
			infile >> idsprite >> time;
			ani->Add(idsprite, time);
		}
		
		animation.push_back(ani);
		
	}
	this->animations[idAni] = animation;
}
