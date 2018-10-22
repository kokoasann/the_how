#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
}
SoundManager::~SoundManager()
{
	DeleteGO(roopS);
}
bool SoundManager::Start()
{
	roopS = NewGO<prefab::CSoundSource>(0);
	return true;
}
void SoundManager::Awake()
{
	roopS = NewGO<prefab::CSoundSource>(0);
}
void SoundManager::AllStop()
{
}
void SoundManager::PlaySE(int sound,bool roop)
{
	prefab::CSoundSource* SE = NewGO<prefab::CSoundSource>(0);
	if (!roop)
	{
		switch (sound)
		{
		case button:
			SE->Init("sound/button.wav");
			SE->Play(roop);
			SE->SetVolume(vol);
			break;
		case pickup:
			SE->Init("sound/pickup.wav");
			SE->Play(roop);
			SE->SetVolume(vol);
			break;
		case sairen:
			SE->Init("sound/sairen.wav");
			SE->Play(roop);
			SE->SetVolume(vol);
			break;
		case firing:
			SE->Init("sound/firing.wav");
			SE->Play(roop);
			SE->SetVolume(vol);
			break;
		case bom:
			SE->Init("sound/bom.wav");
			SE->Play(roop);
			SE->SetVolume(vol);
			break;
		case groundbom:
			SE->Init("sound/groundbom.wav");
			SE->Play(roop);
			SE->SetVolume(vol);
			break;
		case missile:
			SE->Init("sound/missile_path.wav");
			SE->Play(roop);
			SE->SetVolume(vol/2);
			break;
		case fallingBOMB:
			SE->Init("sound/fallingBOMB.wav");
			SE->Play(roop);
			SE->SetVolume(vol);
			break;
		case airship:
			SE->Init("sound/airship1.wav");
			SE->Play(roop);
			SE->SetVolume(vol/2);
			break;
		case chenge:
			SE->Init("sound/chenge.wav");
			SE->Play(roop);
			SE->SetVolume(vol);
			break;
		}
	}
	else
	{
		switch (sound)
		{
		case button:
			roopS->Init("sound/button.wav");
			roopS->Play(roop);
			roopS->SetVolume(vol);
			break;
		case pickup:
			roopS->Init("sound/pickup.wav");
			roopS->Play(roop);
			roopS->SetVolume(vol);
			break;
		case sairen:
			roopS->Init("sound/sairen.wav");
			roopS->Play(roop);
			roopS->SetVolume(vol);
			break;
		case firing:
			roopS->Init("sound/firing.wav");
			roopS->Play(roop);
			roopS->SetVolume(vol);
			break;
		case bom:
			roopS->Init("sound/bom.wav");
			roopS->Play(roop);
			roopS->SetVolume(vol);
			break;
		case groundbom:
			roopS->Init("sound/groundbom.wav");
			roopS->Play(roop);
			roopS->SetVolume(vol);
			break;
		case missile:
			roopS->Init("sound/missile_path.wav");
			roopS->Play(roop);
			roopS->SetVolume(vol);
			break;
		case fallingBOMB:
			roopS->Init("sound/fallingBOMB.wav");
			roopS->Play(roop);
			roopS->SetVolume(vol);
			break;
		case airship:
			roopS->Init("sound/airship1.wav");
			roopS->Play(roop);
			roopS->SetVolume(vol/2);
			break;
		}
	}
}

void SoundManager::StopSE()
{
	roopS->Stop();
}

void SoundManager::PlayBGM(int bgm)
{
	switch (bgm)
	{
	case siren:
		roopS->Init("sound/sairen.wav");
		roopS->Play(true);
		roopS->SetVolume(vol);
		break;
	}
}
void SoundManager::StopBGM()
{
	roopS->Stop();
}