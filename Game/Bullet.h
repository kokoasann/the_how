#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Game;
class FollingObject;
class MainObject;
class Game;
class SoundManager;
class Bullet:public IGameObject
{
public:
	Bullet();
	~Bullet();
	bool Start();
	void Update();
	void BEEEEEEEEEEEEEEE();
	void BOOOOOOOOOOOONNN();
	prefab::CSkinModelRender* m_bullet = nullptr;
	prefab::CSkinModelRender* child[2];
	CSkinModel sm;
	
	CSkinModelData smd;
	MainObject* mo = nullptr;
	Game* game = nullptr;
	SoundManager* soundM = nullptr;
	prefab::CEffect* beem = nullptr;
	prefab::CEffect* beemIN = nullptr;
	CCharacterController CCC;
	//float speed = 10000;
	int time = 0;
	bool beemin = true,push = false,BOOON = false;
	float BOOoooON = 200.0f;
	CVector3 pos = CVector3::Zero;
	CVector3 move = CVector3::Zero;
	CVector3 target = CVector3::Zero;
	CVector3 t = CVector3::Zero;
	CVector3 poc[2];
	CVector3 tac[2];
	CVector3 moc[2];
	//CSkinModel smc[2];
	CQuaternion rolX = CQuaternion::Identity,rolY = CQuaternion::Identity;
	enum uepon
	{
		uniBOM,
		uniBOM3,
		uB3Chaild,
		S_uniBOM,
		K_uniBOM,

		uniBEEM
	};
	uepon ue = S_uniBOM;
	void chengeUNIBOM()
	{
		ue = uniBOM;
	}
	void chengeUNIBOM3()
	{
		ue = uniBOM3;
	}
	void chengeS_UNIBOM()
	{
		ue = S_uniBOM;
	}
	void chengeK_UNIBOM()
	{
		ue = K_uniBOM;
	}
	void chengeUNIBEEM()
	{
		ue = uniBEEM;
	}
};

