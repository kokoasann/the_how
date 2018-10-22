#pragma once
class PracticeConfig;
class EnemyGeneratorPR:public IGameObject
{
public:
	EnemyGeneratorPR();
	~EnemyGeneratorPR();
	bool Start() override;
	void Update() override;

	PracticeConfig* PC = nullptr;
	float Probabilitys[5] = { 0.1f };
	bool app[5] = { false };
};