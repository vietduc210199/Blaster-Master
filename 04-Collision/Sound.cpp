#include "Sound.h"

Sound* Sound::__Instance = NULL;

Sound::Sound()
{
	Init();
	LoadResourceSound();
}

void Sound::LoadResourceSound()
{
	AddSound(eSound::soundWhip, L"sound/usingwhip.wav");
	AddSound(eSound::soundHolyWater, L"sound/holywater.wav");
	AddSound(eSound::soundHit, L"sound/hit.wav");
	AddSound(eSound::soundCollectItem, L"sound/collectitem.wav");
	AddSound(eSound::soundCollectWeapon, L"sound/collectweapon.wav");
	AddSound(eSound::soundHolyCross, L"sound/holycross.wav");
	AddSound(eSound::soundBoomerang, L"sound/08-boomerang.wav");



	AddSound(eSound::soundStopTimer, L"sound/stoptimer.wav");
	AddSound(eSound::soundDagger, L"sound/usingdagger.wav");
	AddSound(eSound::soundDisplayMonney, L"sound/display_monney.wav");
	AddSound(eSound::soundAxe, L"sound/Axe.wav");
	AddSound(eSound::soundStopWatch, L"sound/StopWatch.wav");
	AddSound(eSound::soundInvisibilityPotion_Begin, L"sound/InvisibilityPotion_Begin.wav");
	AddSound(eSound::soundInvisibilityPotion_End, L"sound/InvisibilityPotion_End.wav");


	AddSound(eSound::soundHurting, L"sound/hurting.wav");
	AddSound(eSound::soundOpenDoor, L"sound/opendoor.wav");
	AddSound(eSound::soundBrokenBrick, L"sound/broken_brick.wav");
	AddSound(eSound::soundSplashwater, L"sound/splashwater.wav");
	AddSound(eSound::soundFallingDownWaterSurface, L"sound/fallingdownwatersurface.wav");
	AddSound(eSound::soundGetScoreTimer, L"sound/getscoretime.wav");
	AddSound(eSound::soundGetScoreHeart, L"sound/getscoreheart-[AudioTrimmer.com].wav");



	AddSound(eSound::musicState1, L"music/Stage_01_Vampire_Killer.wav");
	AddSound(eSound::musicLifeLost, L"music/Life_Lost.wav");

	AddSound(eSound::music_PhantomBat, L"music/Boss_Battle_Poison_Mind.wav");
	AddSound(eSound::musicStateClear, L"music/Stage_Clear.wav");
	AddSound(eSound::musicGame_Start_Prologue, L"music/Game_Start_Prologue.wav");

}

bool Sound::isPlaying(eSound type)
{
	return _ArrSound[type]->IsSoundPlaying();
}

void Sound::StopAll()
{
	for (auto& x : _ArrSound)
	{
		if (x.second->IsSoundPlaying())
			x.second->Stop();
	}
}

void Sound::AddSound(eSound type, LPTSTR filename)
{
	CSound* wave;
	HRESULT result = dsound->Create(&wave, filename);
	if (result != DS_OK)
	{
		DebugOut(L"[SOUND] Load Sound that bai. eSound = %d \n", (int)type);
		return;
	}
	_ArrSound[type] = wave;
}

void Sound::Play(eSound type, bool isLoop, LONG lVolume)
{
	_ArrSound[type]->Play(0, isLoop, lVolume);
	//DSBPLAY_LOOPING             0x00000001 -> int = 1

}

void Sound::Stop(eSound type)
{
	_ArrSound[type]->Stop();
}


void Sound::Init()
{
	dsound = new CSoundManager();
	dsound->Initialize(Game::GetInstance()->GetWindowHandle(), DSSCL_PRIORITY);
	dsound->SetPrimaryBufferFormat(2, 22050, 16);
}

Sound* Sound::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Sound();
	return __Instance;
}