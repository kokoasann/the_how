#pragma once
class Fade;
class EffectTextureManeger;
class Title:public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void PostRender(CRenderContext& rc);

	bool waitFade = false,SwaitFade = false,first = true;
	int wait,waiting = 0;
	Fade* fade = nullptr;
	prefab::CSpriteRender* sprite;
	CShaderResourceView texture;
	prefab::CSkinModelRender* cannon = nullptr;
	float angle = 0.0f,radi = 50.0f;
	CVector3 pos = { 100.0f, 10.0f, 0.0f };
	CQuaternion rol = CQuaternion::Identity;

	prefab::CDirectionLight* light = nullptr;
	
	prefab::CSkinModelRender* bilding = nullptr;
	CVector3 bilpo = CVector3::Zero;
	//CShaderResourceView	m_normalMapSRV;			//!<法線マップのSRV。
	//CShaderResourceView m_specularMapSRV;		//!<スペキュラマップのSRV。
	EffectTextureManeger* ETM;

	prefab::CSkinModelRender* bils = nullptr;
	std::vector < prefab::CSkinModelRender*> bildings = { nullptr };

	prefab::CSkinModelRender* ball = nullptr;
	prefab::CSkinModelRender* floor = nullptr;

	CShader shader;

	CFont font;
	enum step
	{
		pan1,
		pan2,
		setup,
		stay
	};
	step s = pan1;
};

