#pragma once
class pointPR;
class Rayder;
class SoundManager;
class EnemyShipPR :public IGameObject
{
public:
	EnemyShipPR();
	~EnemyShipPR();

	bool Start();
	void Update();

	std::vector<CVector3> Jud();
	void ShipBrain();

	prefab::CSkinModelRender* m_ship = nullptr;
	prefab::CSkinModelRender* m = nullptr;
	prefab::CSoundSource* SE = nullptr;

	SoundManager* soundM = nullptr;
	pointPR* p = nullptr;
	Rayder* r = nullptr;
	CVector3 pos = CVector3::Zero;
	CVector3 add = CVector3::Zero;
	CVector3 k = CVector3::Zero;
	std::vector<CVector3> dp;
	float x, z;
	float atan;
	CQuaternion Q;
	int time = 0, wait = 50;
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

