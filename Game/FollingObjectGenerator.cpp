#include "stdafx.h"
#include "FollingObjectGenerator.h"
#include "FollingObject.h"
#include "EnemyShip.h"
#include "point.h"
#include "BackGround.h"
#include "Difficulty.h"
#include "EnemySpawn.h"

FollingObjectGenerator::FollingObjectGenerator()
{
}


FollingObjectGenerator::~FollingObjectGenerator()
{
}

bool FollingObjectGenerator::Start()
{
	diffi = FindGO<Difficulty>("diffi");
	return true;
}

void FollingObjectGenerator::Update()
{
	float r = Random().GetRandDouble();

	bool ArD = false;
	if (diffi->D != 2)
	{
		ArD = r <= 0.1f;
	}
	else
	{
		ArD = r <= 0.3f;
	}
	int i;
	int count = 0;
	switch (LV)
	{
	case A:
	{
		if (first)
		{
			if (WaitTime <= time)
			{
				EnemySpawn* enesp = NewGO<EnemySpawn>(0, "eneSpa");
				float x = Random().GetRandDouble();
				float z = Random().GetRandDouble();
				float t = abs(x) + abs(z);
				x /= t;
				z /= t;
				if (Random().GetRandDouble() <= 0.5)
					x *= -1;
				if (Random().GetRandDouble() <= 0.5)
					z *= -1;

				//enesp->SetSpawn(x * 450, 500, z * 450, 300);

				if (diffi->D != 2)
				{
					enesp->SetSpawn(x * 450, 500, z * 450, 600);
					enesp->SetProb(0.05f, 0.5f);
				}
				else
				{
					enesp->SetSpawn(x * 450, 500, z * 450, 50);
					enesp->SetProb(0.1f, 0.5f);
				}
				first = false;
			}
		}
		QueryGOs<EnemySpawn>("eneSpa", [&](EnemySpawn* es)->bool
		{
			if (es != nullptr)
				count++;
			return true;
		});
		if (!first && count == 0)
		{
			WaitTime = 150;
			time = 0;
			first = true;
		}
		time++;
		break;
	}
	case B:
	{
		if (first)
		{
			if (WaitTime == 0)
			{
				ef = NewGO < prefab::CEffect >(0);
				ef->Play(L"effect/warning.efk");
				ef->SetPosition({ 0.000001f, -10.0f, 0.0f });
				ef->SetScale({ 50,50,50 });
				EnemyShip* e = NewGO<EnemyShip>(0, "s");
				e->ship = EnemyShip::Ships::Mdl_Calico;
				e->step = EnemyShip::Step::cross;
				e->firstShip = true;
			}

			if (WaitTime <= time)
			{
				EnemySpawn* enesp = NewGO<EnemySpawn>(0, "eneSpa");
				float x = Random().GetRandDouble();
				float z = Random().GetRandDouble();
				float t = abs(x) + abs(z);
				x /= t;
				z /= t;
				if (Random().GetRandDouble() <= 0.5)
					x *= -1;
				if (Random().GetRandDouble() <= 0.5)
					z *= -1;

				//enesp->SetSpawn(x * 450, 500, z * 450, 300);

				if (diffi->D != 2)
				{
					enesp->SetSpawn(x * 450, 500, z * 450, 550);
					enesp->SetProb(0.05f, 0.5f);
				}
				else
				{
					enesp->SetSpawn(x * 450, 500, z * 450, 50);
					enesp->SetProb(0.1f, 0.5f);
				}
				first = false;
			}
		}
		QueryGOs<EnemySpawn>("eneSpa", [&](EnemySpawn* es)->bool
		{
			if (es != nullptr)
				count++;
			return true;
		});
		if (!first && count == 0)
		{
			WaitTime = 120;
			time = 0;
			first = true;
		}
		time++;
		/*else if (ArD && !ef->IsPlay())
		{
			FO = NewGO<FollingObject>(0, "f");
			if (Random().GetRandDouble() <= 0.7f)
			{
				FO->B = FollingObject::BOMB::littleboy;
			}
			else if (Random().GetRandDouble() <= 0.3f)
			{
				FO->B = FollingObject::BOMB::SeaUrchin;
			}

		}*/
		break;
	}
	case C:
	{
		if (first)
		{
			if (WaitTime <= time)
			{
				EnemySpawn* enesp = NewGO<EnemySpawn>(0, "eneSpa");
				float x = Random().GetRandDouble();
				float z = Random().GetRandDouble();
				float t = abs(x) + abs(z);
				x /= t;
				z /= t;
				if (Random().GetRandDouble() <= 0.5)
					x *= -1;
				if (Random().GetRandDouble() <= 0.5)
					z *= -1;

				//enesp->SetSpawn(x * 450, 500, z * 450, 300);

				if (diffi->D != 2)
				{
					enesp->SetSpawn(x * 450, 500, z * 450, 500);
					enesp->SetProb(0.05f, 0.7f,0.3f);
				}
				else
				{
					enesp->SetSpawn(x * 450, 500, z * 450, 50);
					enesp->SetProb(0.1f, 0.7f,0.3f);
				}
				first = false;
			}
		}
		QueryGOs<EnemySpawn>("eneSpa", [&](EnemySpawn* es)->bool
		{
			if (es != nullptr)
				count++;
			return true;
		});
		if (!first && count == 0)
		{
			WaitTime = 100;
			time = 0;
			first = true;
		}
		time++;

		/*if (ArD)
		{
			FO = NewGO<FollingObject>(0, "f");
			if (Random().GetRandDouble() <= 0.7f)
			{
				FO->B = FollingObject::BOMB::littleboy;
			}
			else if (Random().GetRandDouble() <= 0.3f)
			{
				FO->B = FollingObject::BOMB::SeaUrchin;
			}
			else if (Random().GetRandDouble() <= 0.05f)
			{
				EnemyShip* e = NewGO<EnemyShip>(0, "s");
				e->ship = EnemyShip::Ships::Mdl_Calico;
				e->step = EnemyShip::Step::cross;
			}
		}*/
		break;
	}
	case D:
	{
		if (first)
		{
			if (WaitTime <= time)
			{
				EnemySpawn* enesp = NewGO<EnemySpawn>(0, "eneSpa");
				float x = Random().GetRandDouble();
				float z = Random().GetRandDouble();
				float t = abs(x) + abs(z);
				x /= t;
				z /= t;
				if (Random().GetRandDouble() <= 0.5)
					x *= -1;
				if (Random().GetRandDouble() <= 0.5)
					z *= -1;

				//enesp->SetSpawn(x * 450, 500, z * 450, 300);

				if (diffi->D != 2)
				{
					enesp->SetSpawn(x * 450, 500, z * 450, 300);
					enesp->SetProb(0.05f, 0.7f, 0.3f);
				}
				else
				{
					enesp->SetSpawn(x * 450, 500, z * 450, 50);
					enesp->SetProb(0.1f, 0.7f, 0.3f);
				}
				first = false;
			}
		}
		QueryGOs<EnemySpawn>("eneSpa", [&](EnemySpawn* es)->bool
		{
			if (es != nullptr)
				count++;
			return true;
		});
		if (!first && count == 0)
		{
			WaitTime = 50;
			time = 0;
			first = true;
		}
		time++;
		/*if (ArD)
		{
			FO = NewGO<FollingObject>(0, "f");
			if (Random().GetRandDouble() <= 0.7f)
			{
				FO->B = FollingObject::BOMB::littleboy;
			}
			else if (appe(Random().GetRandDouble(), 0.3f, 0.1f))
			{
				FO->B = FollingObject::BOMB::SeaUrchin;
			}
			else if (appe(Random().GetRandDouble(), 0.05f, 0.2f))
			{
				EnemyShip* e = NewGO<EnemyShip>(0, "s");
				e->ship = EnemyShip::Ships::Mdl_Calico;
				e->step = EnemyShip::Step::cross;
			}
		}*/
		break;
	}
	case E:
		if (first)
		{
			if (WaitTime <= time)
			{
				EnemySpawn* enesp = NewGO<EnemySpawn>(0, "eneSpa");
				float x = Random().GetRandDouble();
				float z = Random().GetRandDouble();
				float t = abs(x) + abs(z);
				x /= t;
				z /= t;
				if (Random().GetRandDouble() <= 0.5)
					x *= -1;
				if (Random().GetRandDouble() <= 0.5)
					z *= -1;

				//enesp->SetSpawn(x * 450, 500, z * 450, 300);

				if (diffi->D != 2)
				{
					enesp->SetSpawn(x * 450, 500, z * 450, 150);
					enesp->SetProb(0.7f, 0.7f, 0.3f);
				}
				else
				{
					enesp->SetSpawn(x * 450, 500, z * 450, 50);
					enesp->SetProb(0.8f, 0.7f, 0.1f);
				}
				first = false;
			}
		}
		QueryGOs<EnemySpawn>("eneSpa", [&](EnemySpawn* es)->bool
		{
			if (es != nullptr)
				count++;
			return true;
		});
		if (!first && count == 0)
		{
			WaitTime = 10;
			time = 0;
			first = true;
			superWave++;
			if (superWave == 5)
			{
				FindGO<point>("p")->superWave = true;
				break;
			}
		}
		
		time++;

/*
		if (first)
		{
			AppTime = 500;
			first = false;
		}
		if (appe(r,0.7f,0.8f) && time < AppTime)
		{
			FO = NewGO<FollingObject>(0, "f");
			if (Random().GetRandDouble() <= 0.7f)
			{
				FO->B = FollingObject::BOMB::littleboy;
			}
			else if (appe(Random().GetRandDouble(),0.3f,0.1f))
			{
				FO->B = FollingObject::BOMB::SeaUrchin;
			}
			else if (appe(Random().GetRandDouble(),0.05f,0.2f))
			{
				EnemyShip* e = NewGO<EnemyShip>(0, "s");
				e->ship = EnemyShip::Ships::Mdl_Calico;
				e->step = EnemyShip::Step::cross;
			}
		}
		else if (time >= AppTime)
		{
			FindGO<point>("p")->superWave = true;
			first = true;
		}
		time++;*/
		break;
	case F:
		if (first)
		{
			FindGO<BackGround>("BG")->OPEN();
			QueryGOs<EnemySpawn>("eneSpa", [&](EnemySpawn* es)->bool
			{
				DeleteGO(es);
				return true;
			});
			QueryGOs<FollingObject>("f", [&](FollingObject* fo)->bool 
			{
				DeleteGO(fo);
				return true;
			});
			QueryGOs<EnemyShip>("s", [&](EnemyShip* es)->bool 
			{
				DeleteGO(es);
				return true;
			});
			
			first = false;
		}
		break;
	case G:
		if (first)
		{
			time = 5;
			first = false;
		}
		if (r <= 0.3f && time > 0)
		{
			EnemyShip* e = NewGO<EnemyShip>(0, "s");
			e->ship = EnemyShip::Ships::GBBBShip;
			e->firstShip = true;
			e->step = EnemyShip::Step::drop;
			time--;
		}
		break;
	case H:
		i = 0;
		QueryGOs<EnemyShip>("s", [&](EnemyShip* es)->bool
		{
			if (es != nullptr)
			{
				if (int(es->ship) == 2)
				{
					i++;
				}
			}
			return true;
		});
		if (i <= 5 && r < 0.05f)
		{
			EnemyShip* e = NewGO<EnemyShip>(0, "s");
			e->ship = EnemyShip::Ships::GBBBShip;
			e->step = EnemyShip::Step::drop;
		}
		break;
	case BreakTime:
		if (r <= Probabi && time < AppTime)
		{
			FO = NewGO<FollingObject>(0, "f");
			FO->B = FollingObject::BOMB::SeaUrchin;
			float r1 = Random().GetRandDouble() * 600;
			float r2 = Random().GetRandDouble() * 600;
			FO->pos = { r1,500,r2 };
			time++;
		}
		else if(time >= AppTime+150)
		{
			LV = level(int(LVold) + 1);
			time = 0;
			AppTime = 0;
			WaitTime = 0;
			first = true;
		}
		else
		{
			time++;
		}
		break;
	case S:
		if (r <= Probabi && time < AppTime)
		{
			FO = NewGO<FollingObject>(0, "f");
			FO->B = FollingObject::BOMB::SpaceSeaUrchin;
			time++;
		}
		else if (time >= AppTime + 150)
		{
			LV = level(int(LVold) + 1);
			time = 0;
			AppTime = 0;
			first = true;
		}
		else
		{
			time++;
		}
		break;
	}
}
void FollingObjectGenerator::BT(int WT,int AT,float PB)
{
	QueryGOs<EnemySpawn>("eneSpa", [&](EnemySpawn* es)->bool 
	{
		DeleteGO(es);
		return true;
	});
	LVold = LV;
	LV = BreakTime;
	time = 0;
	WaitTime = WT;
	AppTime = AT;
	Probabi = PB;
}

void FollingObjectGenerator::SpaceBT(int WT, int AT, float PB)
{
	LVold = LV;
	LV = S;
	time = 0;
	WaitTime = WT;
	AppTime = AT;
	Probabi = PB;
}

bool FollingObjectGenerator::appe(double r, float en, float d)
{
	switch (diffi->D)
	{
	case 0:
	case 1:
		if (r <= en)
			return true;
		else
			return false;
		break;
	case 2:
		if (r <= d)
			return true;
		else
			return false;
		break;
	}
	return false;
}