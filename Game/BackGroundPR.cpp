#include "stdafx.h"
#include "BackGroundPR.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "EffectTextureManeger.h"

BackGroundPR::BackGroundPR()
{
}
BackGroundPR::~BackGroundPR()
{
	for (auto l : lightList)
	{
		DeleteGO(l);
	}
	switch (BG)
	{
	case 0:
		DeleteGO(SMR);
		DeleteGO(BR);
		DeleteGO(BL);
		DeleteGO(BIL);
		DeleteGO(MT);
		DeleteGO(FLOOR);
		break;
	case 1:
		DeleteGO(SMR);
		DeleteGO(SUN);
		DeleteGO(MOON);
		break;
	case 2:
		break;
	}
}

bool BackGroundPR::Start()
{
	ETM = FindGO<EffectTextureManeger>("etm");
	auto light = NewGO<prefab::CDirectionLight>(0);
	lightList.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	lightList.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	lightList.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	lightList.push_back(light);

	LightManager().SetAmbientLight({ 1.4f, 1.4f, 1.4f });

	SetBackGround(0);
	return true;
}

void BackGroundPR::SetBackGround(int i)
{
	BG = i;
	CQuaternion rot = CQuaternion::Identity;
	switch (i)
	{
	case 0:
		lightpos.Set(-0.707, -0.707f, 0.0f);
		GraphicsEngine().GetShadowMap().SetLightDirection(lightpos);
		lightList[0]->SetDirection(lightpos);
		lightList[0]->SetColor({ 5005.3f, 5005.3f, 5005.3f, 1.0f });

		lightpos.Set(0.027, -0.207f, 0.0f);
		lightList[1]->SetDirection(lightpos);
		lightList[1]->SetColor({ 1000.3f, 1000.3f, 1000.3f, 1.0f });

		lightpos.Set(0.0, 0.0f, 1.0f);
		lightList[2]->SetDirection(lightpos);
		lightList[2]->SetColor({ 1000.3f, 1000.3f, 1000.3f, 1.0f });

		lightpos.Set(0.0, 0.0f, -1.0f);
		lightList[3]->SetDirection(lightpos);
		lightList[3]->SetColor({ 1000.3f, 1000.3f, 1000.3f, 1.0f });

		LightManager().SetAmbientLight({ 1.4f, 1.4f, 1.4f });

		SMR = NewGO<prefab::CSkinModelRender>(0);
		SMR->Init(L"modelData/ball.cmo");
		SMR->SetScale({ 0.8f, 0.8f, 0.8f });
		SMR->SetPosition({ 0.0f,-80.0f,0.0f });
		rot.SetRotationDeg(CVector3::AxisX, 90.0f);
		SMR->SetRotation(rot);

		shader.Load("shader/model.fx", "PSMainBG", CShader::EnType::PS);
		SMR->FindMaterial([&](CModelEffect* mat) {
			mat->SetRender3DModelPSShader(shader);
		});

		MT = NewGO<prefab::CSkinModelRender>(0);
		MT->Init(L"modelData/mountain.cmo");
		MT->SetScale({ 0.8f, 0.8f, 0.8f });
		MT->SetPosition({ 0.0f,-80.0f,0.0f });
		MT->SetRotation(rot);
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
		//Rpos.Set(0.0f, -80.0f, 0.0f);
		BR->SetPosition({ 0.0f, -80.0f, 0.0f });
		BR->SetRotation(rot);
		BR->SetShadowCasterFlag(true);
		BR->SetShadowReceiverFlag(true);

		BL = NewGO<prefab::CSkinModelRender>(0);
		BL->Init(L"modelData/bilL.cmo");
		BL->SetScale({ 0.8f, 0.8f, 0.8f });
		//Lpos.Set(0.0f, -80.0f, 0.0f);
		BL->SetPosition({ 0.0f, -80.0f, 0.0f });
		BL->SetRotation(rot);
		BL->SetShadowCasterFlag(true);
		BL->SetShadowReceiverFlag(true);
		break;
	case 1:
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

		MOON = NewGO<prefab::CSkinModelRender>(0);
		MOON->Init(L"modelData/moon.cmo");
		MOON->SetPosition({ -1000,700,4000 });
		MOON->SetScale({ 4,4,4 });
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

		SMR = NewGO<prefab::CSkinModelRender>(0);
		SMR->Init(L"modelData/utyu.cmo");
		SMR->SetScale({ 200,200,200 });

		shader.Load("shader/model.fx", "PSSpaceBG", CShader::EnType::PS);
		SMR->FindMaterial([&](CModelEffect* mat) {
			mat->SetRender3DModelPSShader(shader);
		});
		break;
	case 2:
		break;
	}
}

void BackGroundPR::RemBackGround(int i)
{
	switch (i)
	{
	case 0:
		DeleteGO(FLOOR);
		DeleteGO(BIL);
		DeleteGO(BR);
		DeleteGO(BL);
		DeleteGO(MT);
		DeleteGO(SMR);
		break;
	case 1:
		DeleteGO(SUN);
		DeleteGO(MOON);
		DeleteGO(SMR);
		break;
	case 2:
		break;
	}
}