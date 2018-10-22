#include "stdafx.h"
#include "point.h"
#include "END.h"
#include "Hart.h"
#include "Game.h"
#include "FollingObjectGenerator.h"
#include "SaveLoad.h"
#include "Difficulty.h"
point::point()
{
}
point::~point()
{
}
bool point::Start()
{
	diffi = FindGO<Difficulty>("diffi");
	game = FindGO<Game>("Game");
	FOG = FindGO<FollingObjectGenerator>("FOG");
	hart = FindGO<Hart>("hart");
	//superWave = true;
	//F110 = false;
	//FOG->LV = FollingObjectGenerator::level::F;
	//POINT = 1600;
	//GBBBpoi = 5;
	return true;
}
void point::addPOINT(int i)
{
	for (int c = 0; c < i; c++)
	{
		POINT += 1;
		Bonus();
	}
}
void point::Bonus()
{
	switch (POINT)
	{
	case 40:
		game->uej++;
		game->unibom3 = true;
		FOG->BT(650,500,0.1f);
		recovery(20);
		break;
	case 110:
		recovery(30);
		break;
	case 400:
		game->uej++;
		game->Kunibom = true;
		FOG->BT(400, 300, 0.1f);
		break;
	case 1000:
		FOG->BT(400, 300, 0.1f);
		break;
	default:
		if (POINT >= 110 && (firstShipBreak || firstShipEnd) && F110)
		{
			recovery(30);
			game->uej++;
			game->Sunibom = true;
			FOG->BT(500, 400, 0.15f);
			F110 = false;
		}
		if (superWave)
		{
			FOG->LV = FollingObjectGenerator::level::F;
			SaveLoad sl;
			for (int i = 6; i <= 13; i++)
			{
				sl.SAVE(i, 1);
			}
			
			superWave = false;
		}
		if (GBBBpoi == 5 && GBBB)
		{
			FOG->SpaceBT(400, 300, 0.1f);
			SaveLoad sl;
			sl.SAVE(14, 1);
			GBBB = false;
		}
		break;
	}
}
void point::damage(int i)
{
	if (!noHit)
	{
		switch (diffi->D)
		{
		case 0:
			if (lug >= 2)
			{
				if (HP > 0)
				{
					HP -= i;
					hart->setingHart(HP, HP + i);
				}
				else
				{
					End();
				}
				lug = 0;
			}
			else
			{
				lug++;
			}
			break;
		case 1:
		case 2:
			if (HP > 0)
			{
				HP -= i;
				hart->setingHart(HP, HP + i);
			}
			else
			{
				End();
			}
			break;
		}
		
	}
}
void point::recovery(int i)
{
	if (HP + i >= 50 && false)
	{
		hart->setingHart(50,HP);
		HP = 50;
	}
	else
	{
		HP += i;
		hart->setingHart(HP,HP-i);
	}
}
void point::End()
{
	NewGO<END>(0, "end");
	noHit = true;
}

void point::breakHart()
{
	hart->del();
}

void point::ReFind()
{
	hart = FindGO<Hart>("hart");
}