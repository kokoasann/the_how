#include "stdafx.h"
#include "EnemyGeneratorPR.h"
#include "FollingObjectPR.h"
#include "EnemyShipPR.h"

EnemyGeneratorPR::EnemyGeneratorPR()
{
}
EnemyGeneratorPR::~EnemyGeneratorPR()
{
}

bool EnemyGeneratorPR::Start()
{
	for (int i = 0; i < 5; i++)
	{
		Probabilitys[i] = 0.1f;
	}
	return true;
}

void EnemyGeneratorPR::Update()
{
	float r = Random().GetRandDouble();
	if (r < Probabilitys[0] && app[0])
	{
		FollingObjectPR* fo;
		fo = NewGO<FollingObjectPR>(0, "f");
		fo->B = FollingObjectPR::BOMB::fatman;
	}
	r = Random().GetRandDouble();
	if (r < Probabilitys[1] && app[1])
	{
		FollingObjectPR* fo;
		fo = NewGO<FollingObjectPR>(0, "f");
		fo->B = FollingObjectPR::BOMB::littleboy;
	}
	r = Random().GetRandDouble();
	if (r < Probabilitys[2] && app[2])
	{
		FollingObjectPR* fo;
		fo = NewGO<FollingObjectPR>(0, "f");
		fo->B = FollingObjectPR::BOMB::SeaUrchin;
	}
	r = Random().GetRandDouble();
	if (r < Probabilitys[3] && app[3])
	{
		EnemyShipPR* es;
		es = NewGO<EnemyShipPR>(0, "s");
		es->ship = EnemyShipPR::Ships::GBBBShip;
		es->step = EnemyShipPR::Step::drop;
	}
	r = Random().GetRandDouble();
	if (r < Probabilitys[4] && app[4])
	{
		EnemyShipPR* es;
		es = NewGO<EnemyShipPR>(0, "s");
		es->ship = EnemyShipPR::Ships::Mdl_Calico;
		es->step = EnemyShipPR::Step::cross;
	}
}