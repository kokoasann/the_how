#pragma once
class point;
class Rayder;
class SoundManager;
class EnemyShip:public IGameObject
{
public:
	EnemyShip();
	~EnemyShip();

	bool Start();
	void Update();
	
	std::vector<CVector3> Jud();
	void ShipBrain();

	prefab::CSkinModelRender* m_ship = nullptr;
	prefab::CSkinModelRender* m = nullptr;
	prefab::CSoundSource* SE = nullptr;

	SoundManager* soundM = nullptr;
	point* p = nullptr;
	Rayder* r = nullptr;
	CVector3 pos = CVector3::Zero;
	CVector3 add = CVector3::Zero;
	CVector3 k = CVector3::Zero;
	std::vector<CVector3> dp;
	float x, z;
	float atan;
	CQuaternion Q;
	int time = 0,wait = 50;
	int HP;
	bool Dead = false;
	bool firstShip = false;
	enum Ships
	{
		Mdl_Calico,
		MCBOM,
		GBBBShip
	};
	Ships ship;

	enum Step
	{
		first,
		drop,
		cross,
		advance
	};
	Step step;
};

