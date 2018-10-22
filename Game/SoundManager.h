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
	�T�E���h�ԍ�
	0:button			���
	1:pickup			���
	2:sairen			������
	3:firing			�޵����
	4:bom				�޵�������
	5:groundbom			���ީ���
	6:missile_path		�ޭ�޺޺޺�
	7:fallingBOMB		˭������
	8:airship			�޺ޫ�޺޵��
	9:chenge			������
	*/
	void PlaySE(int sound,bool roop = false);
	void StopSE();

	/*!
	BGM�ԍ�
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

