#pragma once
#include "tkEngine/sound/tkSoundSource.h"
#include "tkEngine/graphics/effect/tkEffect.h"

class EnemyGeneratorPR;
class pointPR;
class BackGroundPR;
class PracticeConfig:public IGameObject
{
public:
	PracticeConfig();
	~PracticeConfig();
	bool Start();
	void Update();
	void SceneChenge(int s);
	void appEnemy(int i, bool b);
	bool GetAppEnemy(int i);
	void probEne(int i, float f);
	void SetBackGround(int i);
	void RemoveBackGround(int i);
	void SetProbability(int i,float f);
	float GetProbability(int i);
	
	prefab::CSoundSource* BGM;

	EnemyGeneratorPR* EGP = nullptr;
	pointPR* p = nullptr;
	BackGroundPR* BG = nullptr;

	CFont font;
	std::unique_ptr<DirectX::SpriteFont> m_font;

	int Scene = 0;

	enum enemys
	{
		fat,
		lit,
		uni,
		sh1,
		sh2
	};

	std::vector<enemys> app;
};

