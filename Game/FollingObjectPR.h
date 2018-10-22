#pragma once
//#include "tkEngine/character/tkCharacterController.h"
class BulletPR;
class pointPR;
class Rayder;
class SoundManager;
class FollingObjectPR:public IGameObject
{
public:
	enum BOMB
	{
		fatman,
		littleboy,
		SeaUrchin,
		ShipFoll,
		ShipFoll2,
		wing
	};
	BOMB B;
	~FollingObjectPR();
	bool Start();
	void Update();
	void BOM();
	void Chain();
	void END();

	void Fall(float f);
	void MoveWing();

	BulletPR* bu;
	pointPR* p;
	Rayder* rd;
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
	
};

