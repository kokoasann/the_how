#include "stdafx.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"
#include "ModeSelect.h"
#include "Difficulty.h"
#include "KeySet.h"
#include "EffectTextureManeger.h"
#include "tkEngine/light/tkDirectionLight.h"

Title::Title()
{
}
Title::~Title()
{
	DeleteGO(cannon);
	DeleteGO(sprite);
	DeleteGO(bilding);
	DeleteGO(floor);
	DeleteGO(ball);
	DeleteGO(light);
	if(bils != nullptr)
		DeleteGO(bils);
}

bool Title::Start()
{
	MainCamera().SetTarget({ -50.0f, 80.0f,30.0f });
	MainCamera().SetNear(0.1f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetViewAngle(CMath::DegToRad(90.0f));
	MainCamera().SetPosition({20.0f, 17.0f, 90.0f });
	MainCamera().Update();

	cannon = NewGO <prefab::CSkinModelRender>(0);
	cannon->Init(L"modelData/cannon2.cmo");
	cannon->SetPosition({ 0.0f,10.0f,0.0f });
	cannon->SetScale({ 0.1f,0.1f,0.1f });
	rol.SetRotationDeg(CVector3::AxisX, 90.0f);
	cannon->SetRotation(rol);
	cannon->SetShadowCasterFlag(true);
	cannon->SetShadowReceiverFlag(false);

	texture.CreateFromDDSTextureFromFile(L"sprite/thehow.dds");
	//sprite.Init(texture, GraphicsEngine().Get2DSpaceScreenWidth(), GraphicsEngine().Get2DSpaceScreenHeight());
	sprite = NewGO<prefab::CSpriteRender>(0);
	sprite->Init(L"sprite/title4.dds", 500.0f, 305.0f);
	sprite->SetPosition({ -380.0f,170.0f,0.0f });
	//sprite.Init(texture, 500.0f, 264.5f);

	light = NewGO < prefab::CDirectionLight>(0);
	light->SetDirection({ -1.9f,-1.3f,-1.0 });
	light->SetColor({ 35,35,35,1.0f });
	GraphicsEngine().GetShadowMap().SetLightDirection({ -1.9f,-1.3f,-1.0 });
	LightManager().SetAmbientLight({ 1.5f, 1.5f, 1.5f });

	bilding = NewGO < prefab::CSkinModelRender>(0);
	bilding->Init(L"modelData/bilti.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
	bilding->SetScale({ 0.7f,0.7f,0.7f });
	//m_normalMapSRV.CreateFromDDSTextureFromFile(L"sprite/fatman_bump2.dds");
	//m_specularMapSRV.CreateFromDDSTextureFromFile(L"sprite/bilti_spe.dds");
	//bilding->FindMaterial([&](auto material)
	//{
	//	//material->SetNormalMap(m_normalMapSRV.GetBody());
	//	material->SetSpecularMap(m_specularMapSRV.GetBody());
	//});

	ball = NewGO<prefab::CSkinModelRender>(0);
	ball->Init(L"modelData/utyu.cmo");
	ball->SetPosition(CVector3::Zero);
	ball->SetScale({ 10,10,10 });
	shader.Load("shader/model.fx", "PSSpaceBG", CShader::EnType::PS);
	ball->FindMaterial([&](CModelEffect* mat) {
		mat->SetRender3DModelPSShader(shader);
	});

	floor = NewGO<prefab::CSkinModelRender>(0);
	floor->Init(L"modelData/FLOOR.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
	floor->SetScale({ 10,10,10 });
	floor->SetPosition({ 0,10.0f,0 });

	fade = FindGO<Fade>("Fade");
	fade->StartFadeIn();

	NewGO<KeySet>(0,"KS");
	NewGO<Difficulty>(0, "diffi");
	ETM = NewGO<EffectTextureManeger>(0, "etm");
	return true;
}
void Title:: Update()
{
	if (waitFade)
	{
		if (!fade->IsFade())
		{
			//NewGO<Game>(0, "Game");
			NewGO<ModeSelect>(0,"modesel");
			DeleteGO(this);
		}
	}
	else if(Pad(0).IsTrigger(enButtonA))
	{
		if (s != stay)
		{
			s = stay;
			first = true;
			fade->fadeSpeed = 4.0f;
			fade->StartFadeOut();
		}
		else if(!fade->IsFade())
		{
			waitFade = true;
			fade->fadeSpeed = 2.0f;
			fade->StartFadeOut();
		}
		
	}
	switch (s)
	{
	case pan1:
		if (first)
		{
			wait = 50;
			MainCamera().SetViewAngle(CMath::DegToRad(90.0f));
			waiting = 0;
			//Pan1();
			first = false;
			bilpo = {-350,0,-590};
			bilding->SetPosition(bilpo);
		}
		else if(waiting <= wait)
		{
			MainCamera().SetTarget({ -50.0f+waiting*1.5f, 20.0f,30.0f });
			MainCamera().SetPosition({ -50.0f+waiting*1.5f, 17.0f, 90.0f });
			MainCamera().Update();
			bilpo.x + waiting * 0.75f;
			bilding->SetPosition(bilpo);

			waiting++;
			if (waiting == 45)
			{
				SwaitFade = true;
				fade->fadeSpeed = 4.0f;
				fade->StartFadeOut();
			}
		}
		else
		{
			first = true;
			s = pan2;
		}
		break;
	case pan2:
		if (first)
		{
			SwaitFade = false;
			fade->fadeSpeed = 4.0f;
			fade->StartFadeIn();
			wait = 90;
			MainCamera().SetViewAngle(CMath::DegToRad(20.0f));
			waiting = 0;
			//Pan2();
			bilpo = { -150,0, 0 };
			bilding->SetPosition(bilpo);
			CQuaternion Q = CQuaternion::Identity;
			Q.SetRotationDeg(CVector3::AxisY, -95);
			bilding->SetRotation(Q);
			first = false;
		}
		else if (waiting <= wait)
		{
			MainCamera().SetTarget({ -50.0f, 20.0f,-90.0f+waiting*2 });
			MainCamera().SetPosition({ 75.0f, 17.0f, -90.0f + waiting * 2 });
			MainCamera().Update();
			//bilpo.z += waiting * 2;
			//bilding->SetPosition(bilpo);
			waiting++;
			if (waiting == 85)
			{
				SwaitFade = true;
				fade->fadeSpeed = 4.0f;
				fade->StartFadeOut();
			}
		}
		else
		{
			first = true;
			s = setup;
		}
		break;
	case setup:
		if (first)
		{
			fade->fadeSpeed = 4.0f;
			fade->StartFadeIn();
			wait = 70;
			MainCamera().SetViewAngle(CMath::DegToRad(90.0f));
			waiting = 0;
			//Setup();
			
			bilding->SetPosition({ -250,0,-400 });
			CQuaternion Q = CQuaternion::Identity;
			Q.SetRotationDeg(CVector3::AxisY, 230);
			bilding->SetRotation(Q);

			bils = NewGO < prefab::CSkinModelRender>(0);
			bils->Init(L"modelData/bilti.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
			bils->SetScale({ 0.7f,0.7f,0.7f });
			bils->SetPosition({ -700,0,700 });
			Q.SetRotationDeg(CVector3::AxisY, -190);
			bils->SetRotation(Q);

			first = false;
		}
		else if (waiting <= wait)
		{
			/*MainCamera().SetTarget({ -50.0f, 80.0f,30.0f });
			MainCamera().SetPosition({ 20.0f, 17.0f, 90.0f });*/
			MainCamera().SetTarget({ -300.0f - waiting * -3.5715f,80.0f,180.0f - waiting * 2.1428f });
			MainCamera().SetPosition({ 120.0f - waiting * 1.4285f, 17.0f, 540.0f - waiting * 6.4285f });
			MainCamera().Update();
			waiting++;
		}
		else
		{
			s = stay;
			first = true;
			//s = pan1;
		}
		break;
	case stay:
		if (first)
		{
			fade->fadeSpeed = 4.0f;
			fade->StartFadeIn();
			MainCamera().SetViewAngle(CMath::DegToRad(90.0f));
			MainCamera().SetTarget({ -50.0f, 80.0f,30.0f });
			MainCamera().SetPosition({ 20.0f, 17.0f, 90.0f });
			MainCamera().Update();



			bilding->SetPosition({ -250,0,-400 });

			CQuaternion Q = CQuaternion::Identity;
			Q.SetRotationDeg(CVector3::AxisY, 230);
			bilding->SetRotation(Q);
			first = false;

			if (bils == nullptr)
			{		
				bils = NewGO < prefab::CSkinModelRender>(0);
				bils->Init(L"modelData/bilti.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
				bils->SetScale({ 0.7f,0.7f,0.7f });
			}
			bils->SetPosition({ -700,0,700 });
			Q.SetRotationDeg(CVector3::AxisY, -190);
			bils->SetRotation(Q);
		}
		break;
	}

	//angle += 1.0f;
	//if (angle > 360.0f)
	//{
	//	angle = 0.0f;
	//}
	//pos.x = radi * cosf(CMath::PI / 180.0f * angle) + 0.000001f;
	//pos.z = radi * sinf(CMath::PI / 180.0f * angle) + 0.000001f;
	////4MainCamera().SetTarget(tar);
	//MainCamera().SetPosition(pos);

	//MainCamera().Update();
}

void Title::Render(CRenderContext& rc)
{

}
void Title::PostRender(CRenderContext& rc)
{
	wchar_t text[256];
	font.Begin(rc);
	swprintf_s(text, L"PUSH \"A\" KEY PLEASE");
	font.Draw(text, { 660.0f,-650.0f }, CVector4::Black, 0, 1, { 0.5f,0.5f });
	font.End(rc);
	//sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}