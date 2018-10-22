#pragma once
class PracticeConfig;
class NumberDisplay;
class SoundManager;
class PracticeDrawing:public IGameObject
{
public:
	PracticeDrawing();
	~PracticeDrawing();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext &rc) override;

	void SSKR();
	void SGHT();
	void BEBS();

	void UP();
	void DOWN();
	bool UpMove = true;
	bool DownMove = false;

	CFont font;

	SoundManager* soundM = nullptr;
	NumberDisplay* ND[5] = { nullptr };
	
	PracticeConfig* PC = nullptr;
	prefab::CSpriteRender* Manu = nullptr;
	prefab::CSpriteRender* Choice[4] = { nullptr };
	CVector3 ChoP[4] = { CVector3::Zero };
	CVector3 MP = CVector3::Zero;
	int cho = 0;

	prefab::CSpriteRender* ChildM = nullptr;
	prefab::CSpriteRender* Select = nullptr;
	CVector3 SelP = CVector3::Zero;
	
	prefab::CSpriteRender* enemys[5] = { nullptr };
	prefab::CSpriteRender* mark[5] = { nullptr };
	int ECho = 0;

	prefab::CSpriteRender* map[3] = { nullptr };
	
	bool chenge = false;
};

