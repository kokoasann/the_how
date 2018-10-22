#pragma once
//#include "tkEngine/character/tkCharacterController.h"
class Bullet;
class point;
class Rayder;
class Game;
class SoundManager;
class EffectTextureManeger;
class FollingObject:public IGameObject
{
public:
	enum BOMB
	{
		fatman,
		littleboy,
		SeaUrchin,
		ShipFoll,
		ShipFoll2,
		wing,
		SpaceSeaUrchin
	};
	BOMB B;
	~FollingObject();
	bool Start();
	void Update();
	void BOM();
	void Chain();
	void END();

	void Fall(float f);
	void MoveWing();

	Bullet* bu;
	point* p;
	Rayder* rd;
	Game* game;
	SoundManager* soundM;

	CVector3 pos = CVector3::Zero;
	CVector3 move = CVector3::Zero;
	bool bom = false;
	int HP;
	int time = 0;
	int wait=30;
	//CVector3 addw = CVector3::Zero;
	//CVector3 din;
	prefab::CSkinModelRender* m_follingOb = nullptr;
	CQuaternion rol = CQuaternion::Identity;
	//CCharacterController CCC;
	CVector3 add;

	bool Dead = false;
	prefab::CPointLight* flash = nullptr;
	CVector3 FP = { 0,0,0 };

	CShaderResourceView*	m_normalMapSRV;			//!<法線マップのSRV。
	CShaderResourceView*	m_specularMapSRV;		//!<スペキュラマップのSRV。
	EffectTextureManeger* ETM;
};

