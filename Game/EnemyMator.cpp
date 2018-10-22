#include "stdafx.h"
#include "EnemyMator.h"
#include "EffectTextureManeger.h"
#include "MainObject.h"
#include "EnemySpawn.h"

EnemyMator::EnemyMator()
{
}


EnemyMator::~EnemyMator()
{
}

bool EnemyMator::Start()
{
	MO = FindGO<MainObject>("targetOb");
	EffectTextureManeger* ETM = FindGO<EffectTextureManeger>("etm");
	R = ETM->Load(L"sprite/emR.dds");
	L = ETM->Load(L"sprite/emL.dds");
	matorR.Init(*R, 1280.0f, 720.0f);
	matorL.Init(*L, 1280.0f, 720.0f);
	return true;
}

void EnemyMator::Update()
{
	CVector3 mpos = MO->moveSpeed;
	mpos.y = 0;
	mpos.Normalize();
	std::vector<CVector3> spawn;
	QueryGOs<EnemySpawn>("eneSpa", [&](EnemySpawn* es)->bool
	{
		if (es != nullptr)
		{
			CVector3 p = es->spawn;
			p.y = 0;
			p.Normalize();
			spawn.push_back(p);
			return true;
		}
	});
	float alr = 0.0f;
	float all = 0.0f;
	for (auto s : spawn)
	{
		CVector3 v = mpos;
		float si = mpos.Dot(s);
		si = acos(si);
		CVector3 dif = mpos - s;
		if (mpos.x > s.x * (mpos.z / s.z))
		{
			if (all < si)
				all = si;
			alr = 360 - all;
		}
		else
		{
			if (alr < si)
				alr = si;
			all = 360 - alr;
		}
	}
	
	if (all > alr)
	{
		alphaR = alr/2;
		alphaL = 0.0f;
	}
	else
	{
		alphaR = 0.0f;
		alphaL = all/2;
	}
}

void EnemyMator::PostRender(CRenderContext & rc)
{
	if (alphaR > 0.0f)
	{
		matorR.SetMulColor({ 1.0f,1.0f,1.0f,alphaR });
		matorR.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	}
	if (alphaL > 0.0f)
	{
		matorL.SetMulColor({ 1.0f,1.0f,1.0f,alphaL });
		matorL.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	}
}
