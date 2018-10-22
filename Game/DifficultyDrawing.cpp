#include "stdafx.h"
#include "DifficultyDrawing.h"
#include "ModeSelect.h"
#include "Difficulty.h"
#include "Fade.h"
#include "SoundManager.h"
#include "tkEngine/light/tkDirectionLight.h"

DifficultyDrawing::DifficultyDrawing()
{
}
DifficultyDrawing::~DifficultyDrawing()
{
	DeleteGO(Left);
	DeleteGO(Right);
	DeleteGO(E);
	DeleteGO(N);
	DeleteGO(D);
	DeleteGO(ball);
	DeleteGO(light);
}

bool DifficultyDrawing::Start()
{
	soundM = FindGO<SoundManager>("SM");
	fade = FindGO<Fade>("Fade");
	fade->StartFadeIn();
	dif = FindGO<Difficulty>("diffi");
	Left = NewGO<prefab::CSpriteRender>(0);
	Left->Init(L"sprite/l.dds", 20.0f, 20.0f);
	Left->SetPosition({ -50.0f,0.0f,0.0f });
	Right = NewGO<prefab::CSpriteRender>(0);
	Right->Init(L"sprite/r.dds", 20.0f, 20.0f);
	Right->SetPosition({ 50.0f,0.0f,0.0f });

	E = NewGO<prefab::CSpriteRender>(0);
	E->Init(L"sprite/i.dds", 500.0f, 500.0f);
	N = NewGO<prefab::CSpriteRender>(0);
	N->Init(L"sprite/f.dds", 500.0f, 500.0f);
	D = NewGO<prefab::CSpriteRender>(0);
	D->Init(L"sprite/m.dds", 500.0f, 500.0f);

	switch (dif->D)
	{
	case Difficulty::difficulty::easy:
		control = 0;
		Nx = 800;
		Dx = 1600;
		E->SetPosition({ Ex,0,0 });
		N->SetPosition({ Nx,0,0 });
		D->SetPosition({ Dx,0,0 });
		break;
	case Difficulty::difficulty::normal:
		control = 1;
		Ex = -800;
		Dx = 800;
		N->SetPosition({ Nx,0,0 });
		E->SetPosition({ Ex,0,0 });
		D->SetPosition({ Dx,0,0 });
		break;
	case Difficulty::difficulty::diff:
		control = 2;
		Nx = -800;
		Ex = -1600;
		D->SetPosition({ Dx,0,0 });
		N->SetPosition({ Nx,0,0 });
		E->SetPosition({ Ex,0,0 });
		break;
	}

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

void DifficultyDrawing::Update()
{
	if (Pad(0).IsTrigger(enButtonLeft))
	{
		if (control > 0)
		{
			control--;
			Ex += 800;
			Nx += 800;
			Dx += 800;
			E->SetPosition({ Ex,0,0 });
			N->SetPosition({ Nx,0,0 });
			D->SetPosition({ Dx,0,0 });
			
			soundM->PlaySE(0);
		}
		/*switch (dif->D)
		{
		case Difficulty::difficulty::easy:
			movesprite(E, true);
			break;
		case Difficulty::difficulty::normal:
			movesprite(N, true);
			break;
		case Difficulty::difficulty::diff:
			movesprite(D, true);
			break;
		}*/
	}
	if (Pad(0).IsTrigger(enButtonRight))
	{
		if (control < 2)
		{
			control++;
			Ex -= 800;
			Nx -= 800;
			Dx -= 800;
			E->SetPosition({ Ex,0,0 });
			N->SetPosition({ Nx,0,0 });
			D->SetPosition({ Dx,0,0 });

			soundM->PlaySE(0);
		}
		/*switch (dif->D)
		{
		case Difficulty::difficulty::easy:
			movesprite(E, false);
			break;
		case Difficulty::difficulty::normal:
			movesprite(N, false);
			break;
		case Difficulty::difficulty::diff:
			movesprite(D, false);
			break;
		}*/
	}
	if (Pad(0).IsTrigger(enButtonA))
	{
		soundM->PlaySE(1);
		dif->D = dif->GetDIiff(control);
		NewGO<ModeSelect>(0,"modesel");
		DeleteGO(this);
	}
	if (Pad(0).IsTrigger(enButtonB))
	{
		soundM->PlaySE(1);
		NewGO<ModeSelect>(0, "modesel");
		DeleteGO(this);
	}
}

void DifficultyDrawing::movesprite(prefab::CSpriteRender* d, bool LR)
{

}