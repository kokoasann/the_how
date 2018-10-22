#include "stdafx.h"
#include "END.h"
#include "Game.h"
#include "MainObject.h"
#include "GameCamera.h"
#include "point.h"
#include "Fade.h"
#include "FollingObject.h"
#include "FollingObjectGenerator.h"
#include "EnemyShip.h"
#include "EnemySpawn.h"
#include "Bullet.h"
#include "ModeSelect.h"
#include "SaveLoad.h"
#include "SoundManager.h"
#include "EnemyMator.h"

END::END()
{
}
END::~END()
{
	DeleteGO(contenew);
	DeleteGO(owali);
	DeleteGO(titleGO);
	DeleteGO(FindGO<FollingObjectGenerator>("FOG"));
	QueryGOs<EnemySpawn>("eneSpa", [&](EnemySpawn* es)->bool
	{
		DeleteGO(es);
		return true;
	});
	QueryGOs<EnemyShip>("s", [&](EnemyShip* go)->bool {
		DeleteGO(go);
		return true;
	});
	QueryGOs<FollingObject>("f", [&](FollingObject* go)->bool {
		DeleteGO(go);
		return true;
	});
	QueryGOs<prefab::CEffect>("f", [&](prefab::CEffect* go)->bool {
		go->SetScale({ 0,0,0 });
		return true;
	});
}
void END::Awake()
{
	QueryGOs<Bullet>("b", [&](Bullet* go)->bool {
		DeleteGO(go);
		return true;
	});
	FindGO<Game>("Game")->active = false;
	FindGO<MainObject>("targetOb")->END();
	FindGO<GameCamera>("camera")->END();
	DeleteGO(FindGO<EnemyMator>("emator"));
}
bool END::Start()
{
	MainCamera().SetPosition(pos);
	MainCamera().SetTarget(tar);
	MainCamera().Update();

	contenew = NewGO<prefab::CSpriteRender>(0);
	contenew->Init(L"sprite/nyellow.dds",240,150);
	contenew->SetPosition({ -300,-170,0.0f });

	owali = NewGO<prefab::CSpriteRender>(0);
	owali->Init(L"sprite/ered.dds", 240, 150);
	owali->SetPosition({ 0,-170,0.0f });

	titleGO = NewGO<prefab::CSpriteRender>(0);
	titleGO->Init(L"sprite/titR.dds", 240, 150);
	titleGO->SetPosition({ 300,-170,0.0f });

	game = FindGO<Game>("Game");
	DeleteGO(game->Aim);
	fade = FindGO<Fade>("Fade");
	p = FindGO<point>("p");
	p->breakHart();

	soundM = FindGO<SoundManager>("SM");
	//font.SetShadowParam(true, 2.0f, CVector4::Black);

	SaveLoad sl;
	for (int i = 0; i < 5; i++)
	{
		score[i] = sl.Load(i);
	}
	score[5] = p->POINT;
	for (int i = 0; i < 6; i++)
	{
		for (int ii = 0; ii < 6; ii++)
		{
			if (ii + 1 >= 6)
			{
				break;
			}
			if (score[ii] < score[ii + 1])
			{
				int iii = score[ii + 1];
				score[ii + 1] = score[ii];
				score[ii] = iii;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		sl.SAVE(i, score[i]);
	}
	return true;
}
void END::CoE()
{
	if (Pad(0).IsTrigger(enButtonLeft) && select > 0)
	{
		soundM->PlaySE(0);
		select--;
		switch (select)
		{
		case 0:
			contenew->Init(L"sprite/nyellow.dds", 250, 160);
			owali->Init(L"sprite/ered.dds", 240, 150);
			break;
		case 1:
			owali->Init(L"sprite/eyellow.dds", 250, 160);
			titleGO->Init(L"sprite/titR.dds", 240, 150);
			break;
		case 2:
			break;
		}
	}
	if (Pad(0).IsTrigger(enButtonRight) && select < 2)
	{
		soundM->PlaySE(0);
		select++;
		switch (select)
		{
		case 0:
			break;
		case 1:
			contenew->Init(L"sprite/nred.dds", 240, 150);
			owali->Init(L"sprite/eyellow.dds", 250, 160);
			break;
		case 2:
			owali->Init(L"sprite/ered.dds", 240, 150);
			titleGO->Init(L"sprite/titY.dds", 250, 160);
			break;
		}
	}
}
void END::Update()
{
	if (litleStay)
	{
		CoE();
		if (waitFade)
		{
			if (!fade->IsFade())
			{
				switch (ent)
				{
				case 0:
					DeleteGO(game);
					NewGO<Game>(0, "Game");
					DeleteGO(this);
					break;
				case 1:
					DeleteGO(game);
					DeleteGO(this);
					exit(-1);
					break;
				case 2:
					DeleteGO(game);
					NewGO<ModeSelect>(0, "modesel");
					DeleteGO(this);
					break;
				}
				/*if (enter)
				{
					
					DeleteGO(game);
					NewGO<Game>(0, "Game");
					DeleteGO(this);

				}
				else
				{
					DeleteGO(game);
					DeleteGO(this);
					exit(-1);
				}*/
			}
		}
		else if (Pad(0).IsTrigger(enButtonA))
		{
			soundM->PlaySE(1);
			waitFade = true;
			fade->StartFadeOut();
			enter = conORend;
			ent = select;
		}
	}
	else
	{
		c++;
		litleStay = c > 30 ? true : false;
	}
	angle += 1.0f;
	if (angle > 360.0f)
	{
		angle = 0.0f;
	}
	pos.x = radi * cosf(CMath::PI / 180.0f * angle) + 0.000001f;
	pos.z = radi * sinf(CMath::PI / 180.0f * angle) + 0.000001f;
	//4MainCamera().SetTarget(tar);
	MainCamera().SetPosition(pos);

	MainCamera().Update();
}

void END::PostRender(CRenderContext& rc)
{
	wchar_t text[256];
	font.Begin(rc);

	swprintf_s(text, L"END");
	font.Draw(L"END", { 500.0f, -300.0f }, CVector4::Black , 0.0f, tsc1, { 0.5f,0.5f });
	
	swprintf_s(text, L"TOTALE:%04d",p->POINT);
	font.Draw(text, { 500.0f, -360.0f }, CVector4::Yellow, 0.0f, tsc2, { 0.5f,0.5f });

	for (int i = 0;i < 5;i++)
	{
		swprintf_s(text, L"RANK%02d:%04d",i+1, score[i]);
		font.Draw(text, { 900.0f, -120.0f+(i-1)*-60 }, CVector4::Yellow, 0.0f, tsc2, { 0.5f,0.5f });
	}
	if (tsc1 > 2.0f)
	{
		tsc1 -= 1;
		tsc2 -= 1;
	}
	if (!litleStay)
	{
		if (PAK)
		{
			font.Draw(L"リトルステイメン...", { 600.0f, -650.0f }, CVector4::Yellow, 0.0f, tsc3, { 0.5f,0.5f });
			tsc3 -= 0.002f;
			if (count <= 20)
			{
				count += 1;
			}
			else
			{
				PAK = false;
			}
		}
		else if (!PAK)
		{
			font.Draw(L"リトルステイメン...", { 600.0f, -650.0f }, CVector4::Yellow, 0.0f, tsc3, { 0.5f,0.5f });
			tsc3 += 0.002f;
			if (count >= 0)
			{
				count -= 1;
			}
			else
			{
				PAK = true;
			}
		}
	}
	font.End(rc);
}