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
	サウンド番号
	0:button			ﾎﾟﾝ
	1:pickup			ﾋﾟﾝ
	2:sairen			ｳｳｩｩｳｳ
	3:firing			ﾄﾞｵｵｫｵﾝ
	4:bom				ﾎﾞｵｵｵｫｫｫｫﾝ
	5:groundbom			ｽﾞﾄﾞｩｵｫﾝ
	6:missile_path		ﾋﾞｭｺﾞｺﾞｺﾞｺﾞ
	7:fallingBOMB		ﾋｭｳｳｩｩｩﾝ
	8:airship			ｺﾞｺﾞｫｺﾞｺﾞｵｵｵ
	9:chenge			ｶﾞﾁｬｺﾝ
	*/
	void PlaySE(int sound,bool roop = false);
	void StopSE();

	/*!
	BGM番号
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

