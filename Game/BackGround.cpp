#include "stdafx.h"
#include "BackGround.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "GameCamera.h"
#include "Fade.h"
#include "Game.h"
#include "FollingObjectGenerator.h"
#include "SoundManager.h"
#include "EffectTextureManeger.h"

BackGround::BackGround()
{
}
BackGround::~BackGround()
{
	DeleteGO(SMR);
	if(BR != nullptr)
		DeleteGO(BR);
	if (BL != nullptr)
		DeleteGO(BL);
	if (MT != nullptr)
	{
		DeleteGO(MT);
		DeleteGO(FLOOR);
		DeleteGO(BIL);
	}
	if (MOON != nullptr)
	{
		DeleteGO(MOON);
		DeleteGO(SUN);
	}
	for (auto li : lightList)
	{
		DeleteGO(li);
	}
	BGM->StopBGM();
	DeleteGO(BGM);
}

bool BackGround::Start()
{
	
	auto light = NewGO<prefab::CDirectionLight>(0);
	lightpos.Set(-0.707, -0.707f, 0.0f);
	GraphicsEngine().GetShadowMap().SetLightDirection(lightpos);
	light->SetDirection(lightpos);
	light->SetColor({ 5005.3f, 5005.3f, 5005.3f, 1.0f });
	lightList.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	lightpos.Set(0.027, -0.207f, 0.0f);
	light->SetDirection(lightpos);
	light->SetColor({ 1000.3f, 1000.3f, 1000.3f, 1.0f });
	lightList.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	lightpos.Set(0.0, 0.0f, 1.0f);
	light->SetDirection(lightpos);
	light->SetColor({ 1000.3f, 1000.3f, 1000.3f, 1.0f });
	lightList.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	lightpos.Set(0.0, 0.0f, -1.0f);
	light->SetDirection(lightpos);
	light->SetColor({ 1000.3f, 1000.3f, 1000.3f, 1.0f });
	lightList.push_back(light);

	LightManager().SetAmbientLight({ 1.4f, 1.4f, 1.4f });

	txtu.CreateFromDDSTextureFromFile(L"sprite/smok.dds");
	SMO.Init(txtu, 1280.0f, 720.0f);

	f = FindGO<Fade>("Fade");

	shader.Load("shader/model.fx", "PSMainBG", CShader::EnType::PS);
	SMR = NewGO<prefab::CSkinModelRender>(0);
	SMR->Init(L"modelData/ball.cmo");
	SMR->SetScale({ 0.8f, 0.8f, 0.8f });
	SMR->SetPosition({ 0.0f,-80.0f,0.0f });
	CQuaternion rot = CQuaternion::Identity;
	rot.SetRotationDeg(CVector3::AxisX, 90.0f);
	SMR->SetRotation(rot);
	SMR->FindMaterial([&](CModelEffect* mat) {
		mat->SetRender3DModelPSShader(shader);
	});

	MT = NewGO<prefab::CSkinModelRender>(0);
	MT->Init(L"modelData/mountain.cmo");
	MT->SetScale({ 0.8f, 0.8f, 0.8f });
	MT->SetPosition({ 0.0f,-80.0f,0.0f });
	MT->SetRotation(rot);

	EffectTextureManeger* ETM = FindGO<EffectTextureManeger>("etm");
	m_normalMapSRV = ETM->Load(L"sprite/mountain_normal.dds");
	m_specularMapSRV = ETM->Load(L"sprite/mountain_spe.dds");
	MT->FindMaterial([&](auto material)
	{
		material->SetNormalMap(m_normalMapSRV->GetBody());
		material->SetSpecularMap(m_specularMapSRV->GetBody());
	});

	FLOOR = NewGO<prefab::CSkinModelRender>(0);
	FLOOR->Init(L"modelData/floor.cmo");
	FLOOR->SetScale({ 0.8f, 0.8f, 0.8f });
	FLOOR->SetPosition({ 0.0f,-80.0f,0.0f });
	FLOOR->SetRotation(rot);

	BIL = NewGO<prefab::CSkinModelRender>(0);
	BIL->Init(L"modelData/bildings.cmo");
	BIL->SetScale({ 0.8f, 0.8f, 0.8f });
	BIL->SetPosition({ 0.0f,-80.0f,0.0f });
	BIL->SetRotation(rot);
	BIL->SetShadowCasterFlag(true);
	m_normalMapSRV = ETM->Load(L"sprite/map2_Normal.dds");
	m_specularMapSRV = ETM->Load(L"sprite/map2_spe.dds");
	BIL->FindMaterial([&](auto material)
	{
		material->SetNormalMap(m_normalMapSRV->GetBody());
		material->SetSpecularMap(m_specularMapSRV->GetBody());
	});
	//BIL->SetShadowReceiverFlag(true);
	
	BR = NewGO<prefab::CSkinModelRender>(0);
	BR->Init(L"modelData/bilR.cmo");
	BR->SetScale({ 0.8f, 0.8f, 0.8f });
	Rpos.Set(0.0f, -80.0f, 0.0f);
	BR->SetPosition(Rpos);
	BR->SetRotation(rot);
	BR->SetShadowCasterFlag(true);
	BR->SetShadowReceiverFlag(true);
	BR->FindMaterial([&](auto material)
	{
		material->SetNormalMap(m_normalMapSRV->GetBody());
		material->SetSpecularMap(m_specularMapSRV->GetBody());
	});
	
	BL = NewGO<prefab::CSkinModelRender>(0);
	BL->Init(L"modelData/bilL.cmo");
	BL->SetScale({ 0.8f, 0.8f, 0.8f });
	Lpos.Set(0.0f, -80.0f, 0.0f);
	BL->SetPosition(Lpos);
	BL->SetRotation(rot);
	BL->SetShadowCasterFlag(true);
	BL->SetShadowReceiverFlag(true);
	BL->FindMaterial([&](auto material)
	{
		material->SetNormalMap(m_normalMapSRV->GetBody());
		material->SetSpecularMap(m_specularMapSRV->GetBody());
	});
/*
	light = NewGO < prefab::CDirectionLight>(0);
	lightpos.Set(0.0f, 1.0f, 0.0f);
	light->SetDirection(lightpos);
	light->SetColor({ 0.3f, 0.3f, 0.3f, 1.0f});*/


	BGM = FindGO<SoundManager>("SM");
	BGM->PlayBGM(0);
	return true;
}
void BackGround::Update()
{
	if (action)
	{
		if (Open)
		{
			Rpos.x += 0.05f;
			Lpos.x -= 0.05f;
			BL->SetPosition(Lpos);
			BR->SetPosition(Rpos);
			if (Rpos.x >= 10)
			{
				Open = false;
				Cdown = true;
			}
		}
		if (Cdown)
		{
			Cpos.y -= 0.05f;
			Cannon->SetPosition(Cpos);
			if (Cpos.y < -48)
			{
				DeleteGO(BR);
				DeleteGO(BL);
				DeleteGO(Cannon);
				DeleteGO(MT);
				DeleteGO(FLOOR);
				DeleteGO(BIL);
				//DeleteGO(light);
				f->fadeSpeed = 2.0f;
				f->StartFadeOut();
				ACup = true;
				Cdown = false;
				ASrot.SetRotationDeg(CVector3::AxisY, -90);
				ASC = NewGO < prefab::CSkinModelRender>(0);
				ASC->Init(L"modelData/asu.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
				ASC->SetPosition(CVector3::Zero);
				ASC->SetRotation(ASrot);
				ASC->SetScale({ 5,5,5 });
				CAMtar.Set(1100, 0, 0);
				CAMpos.Set(1200, -150, 0);
				ang = 60;
				MainCamera().SetViewAngle(CMath::DegToRad(ang));

				MOON = NewGO<prefab::CSkinModelRender>(0);
				MOON->Init(L"modelData/moon.cmo");
				MOON->SetPosition({ -1000,700,4000 });
				MOON->SetScale({ 4,4,4 });
				EffectTextureManeger* ETM = FindGO<EffectTextureManeger>("etm");
				m_normalMapSRV = ETM->Load(L"sprite/moon_bump.dds");
				m_specularMapSRV = ETM->Load(L"sprite/moon_spe.dds");
				MOON->FindMaterial([&](auto material)
				{
					material->SetNormalMap(m_normalMapSRV->GetBody());
					material->SetSpecularMap(m_specularMapSRV->GetBody());
				});

				SUN = NewGO<prefab::CSkinModelRender>(0);
				SUN->Init(L"modelData/sun.cmo");
				SUN->SetPosition({ -1500,300,-800 });
				SUN->SetScale({ 2,2,2 });

				SMR->Init(L"modelData/utyu.cmo");
				SMR->SetScale({ 200,200,200 });

				/*lightpos.Set(-1500,300,-800);
				light->SetDirection(lightpos);*/
			}
		}
		if (ACup && !f->IsFade())
		{
			if (ALP == 0)
			{
				ALP = 1;
				f->StartFadeIn();
			}
			else
			{
				ALP -= 0.005f;
			}
			MainCamera().SetPosition(CAMpos);
			MainCamera().SetTarget(CAMtar);
			MainCamera().Update();

			if (CAMpos.x > 400)
			{
				CAMpos.x -= CAMpos.x*0.007;
				CAMtar.x -= CAMtar.x*0.007;
			}
			else
			{
				ACup = false;
				AChki = true;
			}
		}
		if (AChki)
		{
			/*CAMpos.z -= 3;
			CAMpos.x += 5;
			CAMpos.y += 2;*/

			CAMpos.z -= CAMpos.x*0.0022;
			CAMpos.x += CAMpos.x*0.005;
			CAMpos.y += CAMpos.x*0.002;
			CAMtar.z += CAMpos.x*0.002;
			ang += MainCamera().GetViewAngle()*0.0006;
			MainCamera().SetViewAngle(CMath::DegToRad(ang));
			MainCamera().SetPosition(CAMpos);
			MainCamera().SetTarget(CAMtar);
			MainCamera().Update();
			if (CAMpos.x > 1200)
			{
				AChki = false;
				GO = true;
			}
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			if (GO)
			{
				DeleteGO(ASC);
				FindGO<Game>("Game")->RESTART();
				FindGO<GameCamera>("camera")->SetActiveFlag(true);
				MainCamera().SetViewAngle(CMath::DegToRad(60));
				FollingObjectGenerator* FOG = FindGO<FollingObjectGenerator>("FOG");
				FOG->LV = FollingObjectGenerator::level::G;
				FOG->first = true;
				action = false;
			}
			else
			{
				if (Open || Cdown)
				{
					DeleteGO(BR);
					DeleteGO(BL);
					DeleteGO(Cannon);
					DeleteGO(MT);
					DeleteGO(FLOOR);
					DeleteGO(BIL);
					//DeleteGO(light);

					ASrot.SetRotationDeg(CVector3::AxisY, -90);
					ASC = NewGO < prefab::CSkinModelRender>(0);
					ASC->Init(L"modelData/asu.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
					ASC->SetPosition(CVector3::Zero);
					ASC->SetRotation(ASrot);
					ASC->SetScale({ 5,5,5 });

					MOON = NewGO<prefab::CSkinModelRender>(0);
					MOON->Init(L"modelData/moon.cmo",0,0,CSkinModel::enFbxUpAxisY);
					MOON->SetPosition({ -1000,700,4000 });
					MOON->SetScale({ 4,4,4 });
					CQuaternion qua = CQuaternion::Identity;
					qua.SetRotationDeg(CVector3::AxisY, 150);
					MOON->SetRotation(qua);

					SUN = NewGO<prefab::CSkinModelRender>(0);
					SUN->Init(L"modelData/sun.cmo");
					SUN->SetPosition({ -1500,300,-800 });
					SUN->SetScale({ 2,2,2 });

					SMR->Init(L"modelData/utyu.cmo");
					SMR->SetScale({ 200,200,200 });

					
					lightpos.Set(-0.707, -0.707f, 0.0f);
					GraphicsEngine().GetShadowMap().SetLightDirection(lightpos);
					lightList[0]->SetDirection(lightpos);
					lightList[0]->SetColor({ 30.3f, 30.3f, 30.3f, 1.0f });

					lightpos.Set(0.707, -0.707f, 0.0f);
					lightList[1]->SetDirection(lightpos);
					lightList[1]->SetColor({ 10.3f, 10.3f, 10.3f, 1.0f });

					lightpos.Set(0.0, 0.0f, 1.0f);
					lightList[2]->SetDirection(lightpos);
					lightList[2]->SetColor({ 10.3f, 10.3f, 10.3f, 1.0f });

					lightpos.Set(0.0, 0.0f, -1.0f);
					lightList[3]->SetDirection(lightpos);
					lightList[3]->SetColor({ 10.3f, 10.3f, 10.3f, 1.0f });

					LightManager().SetAmbientLight({ 1.4f, 1.4f, 1.4f });
				}
				f->StartFadeIn();
				CAMpos.z = -355.059;
				CAMpos.x = 1205.255;
				CAMpos.y = 174.394;
				CAMtar.z = 324.394;
				CAMtar.x = 365.11;
				MainCamera().SetViewAngle(1.049);
				MainCamera().SetPosition(CAMpos);
				MainCamera().SetTarget(CAMtar);
				MainCamera().Update();
				Open = false;
				Cdown = false;
				ACup = false;
				AChki = false;
				GO = true;
			}
		}
	}
}

void BackGround::OPEN()
{
	Open = true;
	action = true;
	//FindGO<GameCamera>("camera")->SetActiveFlag(false);
	FindGO<Game>("Game")->STOP();
	MainCamera().SetPosition({ 15,-80,30 });
	MainCamera().SetTarget({ 50.0f, -30.0f, 0.0f });
	MainCamera().SetViewAngle(CMath::DegToRad(90));
	MainCamera().Update();
	Cannon = NewGO < prefab::CSkinModelRender>(0);
	Cannon->Init(L"modelData/cannon2.cmo",0,0,CSkinModel::enFbxUpAxisY);
	Cpos.Set(25.0f, -47.0f, 0.0f);
	Cannon->SetPosition(Cpos);
	Cannon->SetScale({ 0.05f,0.05f ,0.05f });
	BGM->StopBGM();
}

void BackGround::PostRender(CRenderContext& rc)
{
	/*wchar_t txt[256];
	swprintf_s(txt, L"x:%20f\ny:%20f\nz:%20f\na:%20f", MainCamera().GetTarget().x, MainCamera().GetTarget().y, MainCamera().GetTarget().z, MainCamera().GetViewAngle());
	font.Begin(rc);
	font.Draw(txt, { 0,0 });
	font.End(rc);*/
	SMO.SetMulColor({ 1,1,1,ALP });
	SMO.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}