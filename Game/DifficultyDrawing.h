#pragma once
class Difficulty;
class Fade;
class SoundManager;
class DifficultyDrawing:public IGameObject
{
public:
	DifficultyDrawing();
	~DifficultyDrawing();
	bool Start();
	void Update();
	void movesprite(prefab::CSpriteRender* d,bool LR);
	Fade* fade = nullptr;
	Difficulty* dif = nullptr;
	SoundManager* soundM = nullptr;
	float Ex = 0.0f,Nx = 0.0f,Dx = 0.0f;
	int time = 0, control = 1;
	prefab::CSpriteRender* Left = nullptr;
	prefab::CSpriteRender* Right = nullptr;
	prefab::CSpriteRender* E = nullptr;
	prefab::CSpriteRender* N = nullptr;
	prefab::CSpriteRender* D = nullptr;

	prefab::CSkinModelRender* ball = nullptr;
	prefab::CDirectionLight* light = nullptr;
};

