#pragma once
class SoundManager:public IGameObject
{
public:
	SoundManager();
	~SoundManager();
	bool Start() override;
	void Awake() override;
	void AllStop();
	/*!
	ƒTƒEƒ“ƒh”Ô†
	0:button			Îßİ
	1:pickup			Ëßİ
	2:sairen			³³©©³³
	3:firing			ÄŞµµ«µİ
	4:bom				ÎŞµµµ««««İ
	5:groundbom			½ŞÄŞ©µ«İ
	6:missile_path		ËŞ­ºŞºŞºŞºŞ
	7:fallingBOMB		Ë­³³©©©İ
	8:airship			ºŞºŞ«ºŞºŞµµµ
	9:chenge			¶ŞÁ¬ºİ
	*/
	void PlaySE(int sound,bool roop = false);
	void StopSE();

	/*!
	BGM”Ô†
	0:siren
	*/
	void PlayBGM(int bgm);
	void StopBGM();
	float vol = 0.5f;
	prefab::CSoundSource* roopS = nullptr;
	enum Sounds
	{
		button,
		pickup,
		sairen,
		firing,
		bom,
		groundbom,
		missile,
		fallingBOMB,
		airship,
		chenge
	};
	enum BGMs
	{
		siren,

	};
};

