#pragma once
class Fade;
class SoundManager;
class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Update();
	void OPEN();
	void PostRender(CRenderContext& rc);

	SoundManager* BGM = nullptr;


	std::vector<prefab::CDirectionLight*> lightList;
	prefab::CSkinModelRender* SMR = nullptr;
	prefab::CSkinModelRender* FLOOR = nullptr;
	prefab::CSkinModelRender* MT = nullptr;
	prefab::CSkinModelRender* BIL = nullptr;
	prefab::CSkinModelRender* BR = nullptr;
	prefab::CSkinModelRender* BL = nullptr;
	prefab::CSkinModelRender* Cannon = nullptr;
	prefab::CSkinModelRender* ASC = nullptr;
	prefab::CSkinModelRender* MOON = nullptr;
	prefab::CSkinModelRender* SUN = nullptr;

	//prefab::CSpriteRender* SMO = nullptr;
	CShaderResourceView txtu;
	CSprite SMO;
	float ALP = 0;

	CVector3 lightpos = CVector3::Zero;
	CVector3 Rpos = CVector3::Zero;
	CVector3 Lpos = CVector3::Zero;
	CVector3 Cpos = CVector3::Zero;

	CVector3 CAMpos;
	CVector3 CAMtar;
	float ang;
	CQuaternion ASrot = CQuaternion::Identity;

	Fade* f = nullptr;
	bool Open = false;
	bool Cdown = false;
	bool ACup = false;
	bool AChki = false;
	bool GO = false;
	bool action = false;

	CFont font;
	CShader shader;

	CShaderResourceView*	m_normalMapSRV;			//!<法線マップのSRV。
	CShaderResourceView* m_specularMapSRV;		//!<スペキュラマップのSRV。

};

