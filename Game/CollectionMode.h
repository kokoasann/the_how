#pragma once
class CollectionMode:public IGameObject
{
public:
	CollectionMode();
	~CollectionMode();
	bool Start() override;
	void Update() override;
	void Move(int oy,int ox,int y,int x);

	prefab::CSpriteRender* frame[2][5] = { nullptr };
	bool sel[2][5] = { false };
	int x = 0;
	int y = 0;
	prefab::CSkinModelRender* SMR[2][5] = { nullptr };
	CQuaternion rot = CQuaternion::Identity;
	float ang = 0.0f;
	float cam = 0.0f;
	CVector3 camT = { 160,-40,50 };
	CVector3 objP = CVector3::Zero;
	CVector3 objM = CVector3::Zero;
	CVector3 oSca = CVector3::Zero;

	bool select = false;
	bool Cmove = false;
	bool Cback = false;

	std::vector<prefab::CDirectionLight*> lightList;
	CVector3 lightpos = CVector3::Zero;

	std::vector<prefab::CPointLight*> PliteList;

	prefab::CSkinModelRender* BOX;

	CShaderResourceView*	m_normalMapSRV;			//!<法線マップのSRV。
	CShaderResourceView* m_specularMapSRV;		//!<スペキュラマップのSRV。
};

