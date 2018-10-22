#pragma once
class FollingObject;
class Difficulty;
class FollingObjectGenerator:public IGameObject
{
public:
	FollingObjectGenerator();
	~FollingObjectGenerator();
	bool Start();
	void Update();
	void BT(int WT,int AT,float PB);
	void SpaceBT(int WT, int AT, float PB);
	bool appe(double r,float en,float d);

	FollingObject* FO = nullptr;
	int time = 0, WaitTime = 0, AppTime;
	float Probabi;
	bool first = true;
	prefab::CEffect* ef = nullptr;
	Difficulty* diffi = nullptr;
	int superWave = 0;

	enum level
	{
		BreakTime,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T
	};
	level LV = A;
	level LVold;
};

