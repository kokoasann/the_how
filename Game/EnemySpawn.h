#pragma once
class EnemySpawn:public IGameObject
{
public:
	~EnemySpawn();
	bool Start() override;
	void Update() override;
	void SetSpawn(float x, float y, float z, int lifeSpan)
	{
		spawn.x = x;
		spawn.y = y;
		spawn.z = z;
		span = lifeSpan;
	}
	void SetProb(float p, float l = 0.0f, float u = 0.0f)
	{
		prob = p;
		probl = l;
		probu = u;
	}

	int span = 0;
	int time = 0;
	float prob = 0;
	float probl = 0;
	float probu = 0;
	CVector3 spawn = CVector3::Zero;
	CVector3 enepo = CVector3::Zero;
};

