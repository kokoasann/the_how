#include "stdafx.h"
#include "ModeSelect.h"
#include "Fade.h"
#include "Game.h"
#include "DifficultyDrawing.h"
#include "KeySetingDrawing.h"
#include "CollectionMode.h"
#include "SoundManager.h"
#include "Practice.h"
#include "tkEngine/light/tkDirectionLight.h"

ModeSelect::ModeSelect()
{
}
ModeSelect::~ModeSelect()
{
	DeleteGO(s_start);
	DeleteGO(s_difficulty);
	DeleteGO(s_practis);
	DeleteGO(s_collection);
	DeleteGO(s_keySeting);
	DeleteGO(ball);
	DeleteGO(light);
}

bool ModeSelect::Start()
{
	fade = FindGO<Fade>("Fade");
	fade->StartFadeIn();
	soundM = FindGO<SoundManager>("SM");

	float x = 400.0f, y = 250.0f, xd = 30.0f, yd = 130.0f;
	s_start = NewGO < prefab::CSpriteRender>(0);
	s_start->Init(L"sprite/start.dds", 300.0f*1.3f, 187.5f*1.3f);
	s_start->SetPosition({ x,y,0.0f });

	s_difficulty = NewGO < prefab::CSpriteRender>(0);
	s_difficulty->Init(L"sprite/difficalyR.dds", 300.0f, 187.5f);
	s_difficulty->SetPosition({ x - xd,y - yd,0.0f });

	s_practis = NewGO < prefab::CSpriteRender>(0);
	s_practis->Init(L"sprite/practisR.dds", 300.0f, 187.5f);
	s_practis->SetPosition({ x - xd*2,y - yd*2,0.0f });

	s_collection = NewGO < prefab::CSpriteRender>(0);
	s_collection->Init(L"sprite/collectionR.dds", 300.0f, 187.5f);
	s_collection->SetPosition({ x - xd * 3,y - yd * 3,0.0f });

	s_keySeting = NewGO < prefab::CSpriteRender>(0);
	s_keySeting->Init(L"sprite/keysetingR.dds", 300.0f, 187.5f);
	s_keySeting->SetPosition({ x - xd * 4,y - yd * 4,0.0f });

	MainCamera().SetTarget({ 30.0f, 0.0f, 0.0f });
	MainCamera().SetNear(0.1f);
	MainCamera().SetFar(100000.0f);
	MainCamera().SetViewAngle(CMath::DegToRad(60.0f));
	MainCamera().SetPosition({ 0.000001f, 10.0f, 0.0f });
	MainCamera().Update();

	ball = NewGO<prefab::CSkinModelRender>(0);
	ball->Init(L"modelData/ballmose.cmo");
	ball->SetPosition({ 0.000001f, 10.0f, 0.0f });
	ball->SetScale({ 10,10,10 });

	light = NewGO < prefab::CDirectionLight>(0);
	light->SetDirection({ 1.0f,1.5f,0 });
	light->SetColor({ 35,35,35,1.0f });
	GraphicsEngine().GetShadowMap().SetLightDirection({ 1.0f,1.5f,0 });
	LightManager().SetAmbientLight({ 1.5f, 1.5f, 1.5f });
	return true;
}
void ModeSelect::Update()
{
	if (!Waitfade)
	{
		if (!fade->IsFade())
		{
			if (Pad(0).IsTrigger(enButtonDown))
			{
				if (c < 4)
				{
					c++;
					sel = Getsel(c);
					SetSprite();
					soundM->PlaySE(0);
				}
			}
			if (Pad(0).IsTrigger(enButtonUp))
			{
				if (c > -1)
				{
					c--;
					sel = Getsel(c);
					SetSprite();
					soundM->PlaySE(0);
				}
			}

			if (Pad(0).IsTrigger(enButtonA))
			{
				soundM->PlaySE(1);
				switch (sel)
				{
				case start:
					m_start();
					break;
				case difficulty:
					m_difficulty();
					break;
				case practis:
					m_practis();
					break;
				case collection:
					m_collection();
					break;
				case keySeting:
					m_keySeting();
					break;
				}
			}
		}
	}
	else
	{
		switch (sel)
		{
		case start:
			if (fade->IsFade())
			{
				NewGO<Game>(0, "Game");
				DeleteGO(this);
			}
			break;
		case difficulty:
			if (fade->IsFade())
			{
				NewGO<DifficultyDrawing>(0);
				DeleteGO(this);
			}
			break;
		case practis:
			NewGO<Practice>(0,"practice");
			DeleteGO(this);
			break;
		case collection:
			NewGO<CollectionMode>(0);
			DeleteGO(this);
			break;
		case keySeting:
			NewGO<KeySetingDrawing>(0);
			DeleteGO(this);
			break;
		}
	}
}
void ModeSelect::SetSprite()
{
	switch (sel)
	{
	case start:
		s_start->Init(L"sprite/start.dds", 300.0f*1.3f, 187.5f*1.3f);
		s_difficulty->Init(L"sprite/difficalyR.dds", 300.0f, 187.5f);
		break;
	case difficulty:
		s_start->Init(L"sprite/startR.dds", 300.0f, 187.5f);
		s_difficulty->Init(L"sprite/difficaly.dds", 300.0f*1.3f, 187.5f*1.3f);
		s_practis->Init(L"sprite/practisR.dds", 300.0f, 187.5f);
		break;
	case practis:
		s_difficulty->Init(L"sprite/difficalyR.dds", 300.0f, 187.5f);
		s_practis->Init(L"sprite/practis.dds", 300.0f*1.3f, 187.5f*1.3f);
		s_collection->Init(L"sprite/collectionR.dds", 300.0f, 187.5f);
		break;
	case collection:
		s_practis->Init(L"sprite/practisR.dds", 300.0f, 187.5f);
		s_collection->Init(L"sprite/collection.dds", 300.0f*1.3f, 187.5f*1.3f);
		s_keySeting->Init(L"sprite/keysetingR.dds", 300.0f, 187.5f);
		break;
	case keySeting:
		s_collection->Init(L"sprite/collectionR.dds", 300.0f, 187.5f);
		s_keySeting->Init(L"sprite/keyseting.dds", 300.0f*1.3f, 187.5f*1.3f);
		break;
	}
}
void ModeSelect::m_start()
{
	Waitfade = true;
	fade->StartFadeOut();
}
void ModeSelect::m_difficulty()
{
	Waitfade = true;
	fade->StartFadeOut();
}
void ModeSelect::m_practis()
{
	Waitfade = true;
	fade->StartFadeOut();
}
void ModeSelect::m_collection()
{
	Waitfade = true;
	fade->StartFadeOut();
}
void ModeSelect::m_keySeting()
{
	Waitfade = true;
	fade->StartFadeOut();
}

void ModeSelect::Render(CRenderContext& rc)
{

}
void ModeSelect::PostRender(CRenderContext& rc)
{

}