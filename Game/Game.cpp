#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "MainObject.h"
#include "FollingObject.h"
#include "Bullet.h"
#include "point.h"
#include "BackGround.h"
#include "MapPlayer.h"
#include "Fade.h"
#include "KeySet.h"
#include "FollingObjectGenerator.h"
#include "Hart.h"
#include "SoundManager.h"
#include "EnemyMator.h"
#include "tkEngine/light/tkDirectionLight.h"
Game::Game()
{
}
Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_camera);
	DeleteGO(m_mob);
	DeleteGO(Map);
	//DeleteGO(Aim);
	DeleteGO(mp);
	DeleteGO(p);
	DeleteGO(BG);
	QueryGOs<Bullet>("b", [&](Bullet* go)->bool {
		DeleteGO(go);
		return true;
	});
	/*for (auto lig : lightList) {
		DeleteGO(lig);
	}*/
	/*for (auto bull : m_blist)
	{
		DeleteGO(bull);
	}*/
}

bool Game::Start()
{
	Map = NewGO<prefab::CSpriteRender>(0);
	mp = NewGO<MapPlayer>(0, "mapPlayer");
	Map->Init(L"sprite/rayder.dds", 250, 250);
	Map->SetPosition({ 500,200,0.0f });
	Aim = NewGO<prefab::CSpriteRender>(0);
	Aim->Init(L"sprite/aim.dds", 50, 50);
	m_mob = NewGO<MainObject>(0, "targetOb");
	//m_player = NewGO<Player>(0, "unitychan");
	m_camera = NewGO<GameCamera>(0,"camera");
	hart = NewGO<Hart>(0,"hart");
	p = NewGO<point>(0,"p");
	BG = NewGO<BackGround>(0,"BG");
	fade = FindGO<Fade>("Fade");
	ks = FindGO<KeySet>("KS");
	NewGO<FollingObjectGenerator>(0, "FOG");
	soundM = FindGO < SoundManager>("SM");
	em = NewGO<EnemyMator>(0, "emator");

	

	m_font = std::make_unique < DirectX::SpriteFont>(GraphicsEngine().GetD3DDevice(),L"font/hato_pop.spritefont");
	font.SetFont(m_font.get());
	font.SetShadowParam(true, 2.0f, { 26.0f / 255.0f, 49 / 255.0f, 103 / 255.0f, 1.0f });

	fade->StartFadeIn();

	/*auto light = NewGO<prefab::CDirectionLight>(0);
	lightpos.Set(-0.707, -0.707f, 0.0f);
	GraphicsEngine().GetShadowMap().SetLightDirection(lightpos);
	light->SetDirection(lightpos);
	light->SetColor({ 30.3f, 30.3f, 30.3f, 1.0f });
	lightList.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	lightpos.Set(0.707, -0.707f, 0.0f);
	light->SetDirection(lightpos);
	light->SetColor({ 10.3f, 10.3f, 10.3f, 1.0f });
	lightList.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	lightpos.Set(0.0, 0.0f, 1.0f);
	light->SetDirection(lightpos);
	light->SetColor({ 10.3f, 10.3f, 10.3f, 1.0f });
	lightList.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	lightpos.Set(0.0, 0.0f, -1.0f);
	light->SetDirection(lightpos);
	light->SetColor({ 10.3f, 10.3f, 10.3f, 1.0f });

	lightList.push_back(light);
	LightManager().SetAmbientLight({ 1.4f, 1.4f, 1.4f });*/
	return true;
}
void Game::Update()
{
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
	if ((Pad(0).IsTrigger(ks->Firing) /*|| Pad(0).IsMouseLeftC()*/) && active)
	{
		switch (uec)
		{
		case 0:
			//m_camera->Reaction();
			m_bullet = NewGO<Bullet>(0, "b");
			m_bullet->chengeUNIBOM();
			//m_blist.push_back(m_bullet);
			break;
		case 1:
			m_camera->Reaction();
			m_bullet = NewGO<Bullet>(0, "b");
			m_bullet->chengeUNIBOM3();
			UB3R = true;
			time = 0;
			break;
		case 2:
			if (time > 30)
			{
				m_camera->Reaction();
				m_bullet = NewGO<Bullet>(0, "b");
				m_bullet->chengeS_UNIBOM();
				//m_blist.push_back(m_bullet);
				time = 0;
			}
			break;
		case 3:
			m_camera->Reaction();
			m_bullet = NewGO<Bullet>(0, "b");
			m_bullet->chengeS_UNIBOM();
			//m_blist.push_back(m_bullet);
			time = 0;
			break;
		case 4:
			if (FindGO<Bullet>("beem") == nullptr)
			{
				m_beem = NewGO<Bullet>(0, "beem");
				m_beem->chengeUNIBEEM();
				beem = true;
			}
			break;
		}
	}
	else if (Pad(0).IsPress(ks->Firing)&&active&&b)
	{
		//m_beem->push = true;
		m_beem->BEEEEEEEEEEEEEEE();
	}
	else if (beem&&!Pad(0).IsPress(ks->Firing))
	{
		b = false;
		m_beem->push = false;
		beem = false;
		DeleteGO(FindGO<Bullet>("beem"));
	}
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
void Game::STOP()
{
	active = false;
	DeleteGO(Map);
	DeleteGO(mp);
	DeleteGO(Aim);
	DeleteGO(m_mob);
	DeleteGO(hart);
	DeleteGO(m_camera);
}
void Game::RESTART()
{
	active = true;
	Map = NewGO<prefab::CSpriteRender>(0);
	mp = NewGO<MapPlayer>(0, "mapPlayer");
	Map->Init(L"sprite/rayder.dds", 250, 250);
	Map->SetPosition({ 500,200,0.0f });
	Aim = NewGO<prefab::CSpriteRender>(0);
	Aim->Init(L"sprite/aim.dds", 50, 50);
	m_mob = NewGO<MainObject>(0, "targetOb");
	hart = NewGO<Hart>(0, "hart");
	hart->setingHart(p->HP, 0);
	m_camera = NewGO<GameCamera>(0, "camera");
	p->ReFind();
}
void Game::Render(CRenderContext& rc)
{
	(void)rc;
}
void Game::PostRender(CRenderContext& rc)
{
	if (active)
	{
		wchar_t text[256];
		wchar_t wcha[256];
		//p = FindGO<point>("p");
		//poi = p->POINT;
		swprintf_s(text, L"bom:%04d", p->POINT);
		font.Begin(rc);
		font.Draw(text, { 0.0f, -270.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, 0.0f, 1.0f, {0.0f,0.0f });
		std::string t = ueponN(uec);
		mbstowcs(wcha, t.c_str(), t.length() + 1);
		swprintf_s(text, L"%s", wcha);
		font.Draw(text, { 0.0f,-100.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, 0.0f, 1.0f, { 0.0f,0.0f });
		/*swprintf_s(text, L"HP:%02d", hp);
		font.Draw(text, { 0.0f, -330.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, 0.0f, 1.0f, { 0.0f,1.0f });*/
		font.End(rc);
	}
	/*std::vector<
	Object*>::iterator it = std::find(m_flist.begin(), m_flist.end(), p);
	m_flist.erase(it);*/
}