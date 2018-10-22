#pragma once
class MainObject;
class EnemyMator:public IGameObject
{
public:
	EnemyMator();
	~EnemyMator();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& rc) override;

	MainObject* MO;

	CShaderResourceView* R;
	CShaderResourceView* L;
	CSprite matorR;
	CSprite matorL;

	float alphaR = 0.0f;
	float alphaL = 0.0f;
};

