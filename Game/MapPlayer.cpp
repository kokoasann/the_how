#include "stdafx.h"
#include "MapPlayer.h"
#include "MainObject.h"

MapPlayer::MapPlayer()
{
}
MapPlayer::~MapPlayer()
{
	DeleteGO(mp);
}

bool MapPlayer::Start()
{
	mo = FindGO<MainObject>("targetOb");
	mp = NewGO<prefab::CSpriteRender>(0);
	mp->Init(L"sprite/player.dds",20,20);
	mp->SetPosition({ 500,200,0.0f });
	return true;
}
void MapPlayer::Update()
{
	rol.SetRotationDeg(CVector3::AxisZ,360.0f-mo->angle);
	mp->SetRotation(rol);
}