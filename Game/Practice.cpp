#include "stdafx.h"
#include "Practice.h"
#include "PracticeConfig.h"
#include "PracticeDrawing.h"
#include "pointPR.h"
#include "ModeSelect.h"
#include "BulletPR.h"
#include "FollingObjectPR.h"
#include "EnemyShipPR.h"
#include "GameCamera.h"
#include "MapPlayer.h"
#include "Fade.h"
#include "SoundManager.h"
#include "KeySet.h"

Practice::Practice()
{
}
Practice::~Practice()
{
	DeleteGO(PC);
	DeleteGO(PD);
	DeleteGO(m_camera);
	DeleteGO(m_mob);
	DeleteGO(Map);
	DeleteGO(mp);
	DeleteGO(Aim);
	DeleteGO(p);
	QueryGOs<BulletPR>("b", [&](BulletPR* go)->bool {
		DeleteGO(go);
		return true;
	});
	QueryGOs<FollingObjectPR>("f", [&](FollingObjectPR* go)->bool {
		DeleteGO(go);
		return true;
	});
	QueryGOs<EnemyShipPR>("s", [&](EnemyShipPR* go)->bool {
		DeleteGO(go);
		return true;
	});
	QueryGOs<prefab::CEffect>("pe", [&](prefab::CEffect *go)->bool {
		go->SetScale({ 0,0,0 });
		return true;
	});
}

bool Practice::Start()
{
	p = NewGO<pointPR>(0, "p");
	PC = NewGO<PracticeConfig>(0, "PC");
	//PD = NewGO<PracticeDrawing>(0, "PD");
	FindGO<Fade>("Fade")->StartFadeIn();

	Map = NewGO<prefab::CSpriteRender>(0);
	m_mob = NewGO<MainObject>(0, "targetOb");
	m_camera = NewGO<GameCamera>(0, "camera");

	fade = FindGO<Fade>("Fade");
	fade->StartFadeIn();

	ks = FindGO<KeySet>("KS");
	soundM = FindGO < SoundManager>("SM");

	
	Map->Init(L"sprite/rayder.dds", 250, 250);
	Map->SetPosition({ 500,200,0.0f });
	
	Aim = NewGO<prefab::CSpriteRender>(0);
	Aim->Init(L"sprite/aim.dds", 50, 50);

	mp = NewGO<MapPlayer>(0, "mapPlayer");
	return true;
}

void Practice::Update()
{
	if (Pad(0).IsTrigger(enButtonSelect) && !Seting)
	{
		PD = NewGO<PracticeDrawing>(0, "PD");
		Seting = true;
	}
	if (Pad(0).IsTrigger(enButtonStart))
	{
		QueryGOs<FollingObjectPR>("f", [&](FollingObjectPR* go)->bool {
			DeleteGO(go);
			return true;
		});
		QueryGOs<EnemyShipPR>("s", [&](EnemyShipPR* go)->bool {
			DeleteGO(go);
			return true;
		});
	}
	if (Pad(0).IsTrigger(ks->ueponChengeL) && uec > 0)
	{
		uec--;
		soundM->PlaySE(9);
		switch (uec)
		{
		case 0:
			UB3R = false;
			break;
		case 1:
			UB3R = true;
			break;
		case 2:
			UB3R = false;
			break;
		case 3:
			UB3R = false;
			break;
		}
	}
	if (Pad(0).IsTrigger(ks->ueponChengeR) && uec < uej)
	{
		uec++;
		soundM->PlaySE(9);
		switch (uec)
		{
		case 0:
			UB3R = false;
			break;
		case 1:
			UB3R = true;
			break;
		case 2:
			UB3R = false;
			break;
		case 3:
			UB3R = false;
			break;
		}
	}
	if ((Pad(0).IsTrigger(ks->Firing) /*|| Pad(0).IsMouseLeftC()*/))
	{
		switch (uec)
		{
		case 0:
			//m_camera->Reaction();
			m_bullet = NewGO<BulletPR>(0, "b");
			m_bullet->chengeUNIBOM();
			//m_blist.push_back(m_bullet);
			break;
		case 1:
			m_camera->Reaction();
			m_bullet = NewGO<BulletPR>(0, "b");
			m_bullet->chengeUNIBOM3();
			UB3R = true;
			time = 0;
			break;
		case 2:
			if (time > 30)
			{
				m_camera->Reaction();
				m_bullet = NewGO<BulletPR>(0, "b");
				m_bullet->chengeS_UNIBOM();
				//m_blist.push_back(m_bullet);
				time = 0;
			}
			break;
		case 3:
			m_camera->Reaction();
			m_bullet = NewGO<BulletPR>(0, "b");
			m_bullet->chengeS_UNIBOM();
			//m_blist.push_back(m_bullet);
			time = 0;
			break;
		/*case 4:
			if (FindGO<Bullet>("beem") == nullptr)
			{
				m_beem = NewGO<Bullet>(0, "beem");
				m_beem->chengeUNIBEEM();
				beem = true;
			}
			break;*/
		}
	}
	//else if (Pad(0).IsPress(ks->Firing) && active&&b)
	//{
	//	//m_beem->push = true;
	//	m_beem->BEEEEEEEEEEEEEEE();
	//}
	//else if (beem && !Pad(0).IsPress(ks->Firing))
	//{
	//	b = false;
	//	m_beem->push = false;
	//	beem = false;
	//	DeleteGO(FindGO<Bullet>("beem"));
	//}
	if (Pad(0).IsTrigger(enButtonSelect))
	{
		//メニュー表示予定地
	}

	//if (time <= 12 && time % 4 == 0 && UB3R)
	//{
	//	//SE->Init("sound/firing.wav");
	//	//SE->Play(false);
	//	m_camera->Reaction();
	//	m_bullet = NewGO<Bullet>(0, "b");
	//	m_bullet->chengeUNIBOM();

	//}
	time++;
}

void Practice::PostRender(CRenderContext &rc)
{
	wchar_t text[256];
	swprintf_s(text, L"CHEIN! %d", p->POINT);
	font.Begin(rc);
	font.Draw(text, { 850,-430 }, { 255,255,0,0 }, 0);
	font.End(rc);
}

void Practice::END()
{
	NewGO<ModeSelect>(0,"modesel");
	DeleteGO(this);
}