#include "stdafx.h"
#include "Rayder.h"

Rayder::Rayder()
{
}
Rayder::~Rayder()
{
	DeleteGO(enemy);
}
void Rayder::Update()
{
	if (ship || advance)
	{
		enemy->SetPosition({ po.x / 5.0f + 500,po.z / 5.0f + 200,0.0f });
	}
}
void Rayder::CreatEnemy(CVector3 pos)
{
	enemy = NewGO<prefab::CSpriteRender>(0);
	enemy->Init(L"sprite/ene.dds", 10, 10);
	enemy->SetPosition({ pos.x/5.0f+500,pos.z/5.0f+200,0.0f });
}
void Rayder::CreatShip(CVector3 pos)
{
	enemy = NewGO<prefab::CSpriteRender>(0);
	enemy->Init(L"sprite/Eship.dds", 10, 10);
	enemy->SetPosition({ pos.x / 5.0f + 500,pos.z / 5.0f + 200,0.0f });
	ship = true;
}