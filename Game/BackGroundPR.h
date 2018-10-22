#pragma once
class EffectTextureManeger;
class BackGroundPR:public IGameObject
{
public:
	BackGroundPR();
	~BackGroundPR();
	bool Start() override;
	void SetBackGround(int i);
	void RemBackGround(int i);
	int GetBackGround()
	{
		return BG;
	}

	int BG = 0;
	CVector3 lightpos = CVector3::Zero;
	std::vector<prefab::CDirectionLight*> lightList;
	prefab::CSkinModelRender* SMR = nullptr;
	prefab::CSkinModelRender* FLOOR = nullptr;
	prefab::CSkinModelRender* MT = nullptr;
	prefab::CSkinModelRender* BIL = nullptr;
	prefab::CSkinModelRender* BR = nullptr;
	prefab::CSkinModelRender* BL = nullptr;

	prefab::CSkinModelRender* MOON = nullptr;
	prefab::CSkinModelRender* SUN = nullptr;

	CShader shader;

	CShaderResourceView*	m_normalMapSRV;			//!<法線マップのSRV。
	CShaderResourceView* m_specularMapSRV;		//!<スペキュラマップのSRV。
	EffectTextureManeger* ETM;
};

