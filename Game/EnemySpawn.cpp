#include "stdafx.h"
#include "EnemySpawn.h"
#include "FollingObject.h"
#include "EnemyShip.h"

EnemySpawn::~EnemySpawn()
{

}

bool EnemySpawn::Start()
{
	return true;
}

void EnemySpawn::Update()
{
	if (time == span)
	{
		DeleteGO(this);
	}
	float r = Random().GetRandDouble();
	if (r <= prob)
	{
		FollingObject* fo = NewGO<FollingObject>(0, "f");
		if (Random().GetRandDouble() < probl)
			fo->B = FollingObject::BOMB::littleboy;
		else if (Random().GetRandDouble() < probu)
			fo->B = FollingObject::BOMB::SeaUrchin;

		enepo.x = Random().GetRandDouble() * 305;
		enepo.z = Random().GetRandDouble() * 305;
		if (Random().GetRandDouble() <= 0.5)
			enepo.x *= -1;
		if (Random().GetRandDouble() > 0.5)
			enepo.z *= -1;
		enepo.x += spawn.x;
		enepo.z += spawn.z;
		enepo.y = 500;
		fo->pos = enepo;
	}
	time++;
}
