#include "stdafx.h"
#include "FollingObject.h"
#include "Bullet.h"
#include "point.h"
#include "Rayder.h"
#include "Game.h"
#include "GameCamera.h"
#include "SoundManager.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/light/tkPointLight.h"
#include "EffectTextureManeger.h"
FollingObject::~FollingObject()
{
	if (rd != nullptr)
	{
		DeleteGO(rd);
	}
	if (m_follingOb != nullptr)
	{
		DeleteGO(m_follingOb);
	}
	if (flash != nullptr)
	{
		DeleteGO(flash);
	}
}

bool FollingObject::Start()
{
	ETM = FindGO<EffectTextureManeger>("etm");
	soundM = FindGO<SoundManager>("SM");
	rd = NewGO<Rayder>(0);
	
	p = FindGO<point>("p");
	prefab::CSoundSource* SE;
	//game = FindGO<Game>("Game");
	float r1 = Random().GetRandDouble() * 600;
	float r2 = Random().GetRandDouble() * 600;
	float de;
	while (r1 < 150.0f & r2 < 150.0f)
	{
		r1 = Random().GetRandDouble() * 600;
		r2 = Random().GetRandDouble() * 600;
	}
	if (Random().GetRandDouble() <= 0.5f)
	{
		r1 *= -1;
	}
	if (Random().GetRandDouble() <= 0.5f)
	{
		r2 *= -1;
	}
	switch (B)
	{
	case fatman:
		HP = 1;
		//pos = { r1,500.0f, r2 };
		m_follingOb = NewGO<prefab::CSkinModelRender>(0);
		m_follingOb->Init(L"modelData/fatman.3.cmo");
		m_follingOb->SetScale({ 0.35f,0.35f,0.35f });
		m_follingOb->SetPosition(pos);
		rol.SetRotationDeg(CVector3::AxisX, 90.0f);
		m_follingOb->SetRotation(rol);

		soundM->PlaySE(7);
		m_normalMapSRV = ETM->Load(L"sprite/fatman_nor.dds");
		m_specularMapSRV = ETM->Load(L"sprite/fatman_spe.dds");
		m_follingOb->FindMaterial([&](auto material)
		{
			material->SetNormalMap(m_normalMapSRV->GetBody());
			material->SetSpecularMap(m_specularMapSRV->GetBody());
		});


		//CCC.Init(20.0f, 100.0f, pos);
		break;
	case littleboy:
		HP = 1;
		//pos = { r1,500.0f, r2 };
		m_follingOb = NewGO<prefab::CSkinModelRender>(0);
		m_follingOb->Init(L"modelData/littleboy.cmo");
		m_follingOb->SetScale({ 0.2f,0.2f,0.2f });
		m_follingOb->SetPosition(pos);
		rol.SetRotationDeg(CVector3::AxisX, 90.0f);
		m_follingOb->SetRotation(rol);

		soundM->PlaySE(7);
		//CCC.Init(20.0f, 100.0f, pos);
		m_normalMapSRV = ETM->Load(L"sprite/littleboy_bump.dds");
		m_specularMapSRV = ETM->Load(L"sprite/littleboy_spe.dds");
		m_follingOb->FindMaterial([&](auto material)
		{
			material->SetNormalMap(m_normalMapSRV->GetBody());
			material->SetSpecularMap(m_specularMapSRV->GetBody());
		});
		break;
	case SeaUrchin:
		HP = 1;
		//pos = { r1,500.0f, r2 };
		m_follingOb = NewGO<prefab::CSkinModelRender>(0);
		m_follingOb->Init(L"modelData/unni.cmo");
		m_follingOb->SetScale({ 0.35f,0.35f,0.35f });
		m_follingOb->SetPosition(pos);
		rol.SetRotationDeg(CVector3::AxisX, 90.0f);
		m_follingOb->SetRotation(rol);

		soundM->PlaySE(7);
		//CCC.Init(20.0f, 100.0f, pos);
		break;
	case ShipFoll:
		HP = 1;
		m_follingOb = NewGO<prefab::CSkinModelRender>(0);
		m_follingOb->Init(L"modelData/fatman.3.cmo");
		m_follingOb->SetScale({ 0.35f,0.35f,0.35f });
		m_follingOb->SetPosition(pos);
		rol.SetRotationDeg(CVector3::AxisX, 90.0f);
		m_follingOb->SetRotation(rol);

		soundM->PlaySE(7);
		//CCC.Init(20.0f, 100.0f, pos);
		m_normalMapSRV = ETM->Load(L"sprite/fatman_nor.dds");
		m_specularMapSRV = ETM->Load(L"sprite/fatman_spe.dds");
		m_follingOb->FindMaterial([&](auto material)
		{
			material->SetNormalMap(m_normalMapSRV->GetBody());
			material->SetSpecularMap(m_specularMapSRV->GetBody());
		});
		break;
	case ShipFoll2:
		HP = 1;
		m_follingOb = NewGO<prefab::CSkinModelRender>(0);
		m_follingOb->Init(L"modelData/littleboy.cmo");
		m_follingOb->SetScale({ 0.1f,0.1f,0.1f });
		m_follingOb->SetPosition(pos);
		de = atan2(MainCamera().GetPosition().x-pos.x, MainCamera().GetPosition().z - pos.z);
		rol.SetRotation(CVector3::AxisY, de);
		m_follingOb->SetRotation(rol);

		m_normalMapSRV = ETM->Load(L"sprite/littleboy_bump.dds");
		m_specularMapSRV = ETM->Load(L"sprite/littleboy_spe.dds");
		m_follingOb->FindMaterial([&](auto material)
		{
			material->SetNormalMap(m_normalMapSRV->GetBody());
			material->SetSpecularMap(m_specularMapSRV->GetBody());
		});
		//CCC.Init(20.0f, 100.0f, pos);
		rd->advance = true;
		break;
	case wing:
		HP = 1;
		m_follingOb = NewGO<prefab::CSkinModelRender>(0);
		m_follingOb->Init(L"modelData/missile.cmo");
		m_follingOb->SetScale({ 1,1,1 });
		m_follingOb->SetPosition(pos);
		m_follingOb->SetRotation(rol);
		/*float de = atan2(MainCamera().GetPosition().x - pos.x, MainCamera().GetPosition().z - pos.z);
		rol.SetRotation(CVector3::AxisY, de);
		m_follingOb->SetRotation(rol);*/
		//CCC.Init(20.0f, 100.0f, pos);
		rd->advance = true;

		//soundM->PlaySE(6);
		break;
	case SpaceSeaUrchin:
		HP = 1;
		float ry = Random().GetRandDouble() * 1500;
		if (Random().GetRandDouble() <= 0.5)
			ry *= -1;
		pos = { r1*3,ry, r2*3 };
		m_follingOb = NewGO<prefab::CSkinModelRender>(0);
		m_follingOb->Init(L"modelData/unni.cmo");
		m_follingOb->SetScale({ 0.35f,0.35f,0.35f });
		m_follingOb->SetPosition(pos);
		rol.SetRotationDeg(CVector3::AxisX, 90.0f);
		m_follingOb->SetRotation(rol);
		add = pos;
		add.Normalize();
		add *= -1;
		rd->advance = true;
		soundM->PlaySE(8);
		break;
	}
	m_follingOb->SetShadowCasterFlag(true);
	m_follingOb->SetShadowReceiverFlag(true);
	rd->CreatEnemy(pos);
	return true;
}
void FollingObject::Update()
{
	if (!Dead)
	{
		Chain();
		switch (B)
		{
		case fatman:
			Fall(10.0f);
			break;
		case littleboy:
			Fall(15.0f);
			break;
		case SeaUrchin:
			Fall(15.0f);
			break;
		case ShipFoll:
			Fall(10.0f);
			break;
		case ShipFoll2:
			pos += add;
			m_follingOb->SetPosition(pos);

			rd->po = pos;
			if (pos.Length() < 150)
			{
				p->damage(1);
				DeleteGO(this);
			}
			if (abs(pos.x) > 6000 || abs(pos.z) > 6000)
			{
				DeleteGO(this);
			}
			break;
		case wing:
			MoveWing();
			rd->po = pos;
			time++;
			break;
		case SpaceSeaUrchin:
			pos += add * 15;
			m_follingOb->SetPosition(pos);
			CVector3 dif = pos - MainCamera().GetPosition();
			if (dif.Length() < 150)
			{
				DeleteGO(this);
			}
			break;
		}

		if (pos.y < -200.0f && B != SpaceSeaUrchin)
		{
			soundM->PlaySE(5);
			prefab::CEffect* Effe = NewGO<prefab::CEffect>(0, "effe");
			Effe->Play(L"effect/kinoko.efk");
			//FindGO<GameCamera>("camera")->GroundShake();
			CVector3 po = pos;
			po.y += 130.0f;
			float diff = po.Length();
			/*if (diff < 40) {
				std::abort();
			}*/
			Effe->SetPosition(po);
			Effe->SetScale({ 25.0f,25.0f,25.0f });
			if (B != SeaUrchin)
			{
				p->damage(1);
			}
			flash = NewGO<prefab::CPointLight>(0);
			pos.y = 0;
			flash->SetPosition(pos);
			flash->SetColor({ 50000.0f,50000.0f,50000.0f,1.0f });
			FP = { 10,1.0f,0 };
			flash->SetAttn(FP);
			time = 0;
			Dead = true;
			//Gameのインスタンスにアクセスする。
			//Gameクラスのm_flistから、要素を削除する。
			/*
				std::vector<FollingObject*>::iterator it = std::find(m_flist.begin(), m_flist.end(), this);
				m_flist.erase(it);
			*/

			/*std::vector<FollingObject*>::iterator it = std::find(game->m_flist.begin(), game->m_flist.end(), this);
			game->m_flist.erase(it);*/
			DeleteGO(m_follingOb);
		}
		if (HP <= 0)
		{
			BOM();
		}
	}
	else
	{
		if (time < 10)
		{
			FP.x += 55;
			flash->SetAttn(FP);
		}
		else
		{
			FP.x -= 60;
			flash->SetAttn(FP);
		}
		if (time > 20)
		{
			DeleteGO(flash);
			DeleteGO(this);
		}
		time++;
	}
}
void FollingObject::BOM()
{
	soundM->PlaySE(4);
	prefab::CEffect* Effe = NewGO<prefab::CEffect>(0,"effe");
	Effe->Play(L"effect/bom.efk");
	CVector3 po = pos;
	po.y += 130.0f;
	float diff = po.Length();
	/*if (diff < 40) {
		std::abort();
	}*/
	Effe->SetPosition(po);
	Effe->SetScale({ 25.0f,25.0f,25.0f });
	if (B != SeaUrchin && B != SpaceSeaUrchin)
	{
		p->addPOINT(1);
	}
	else
	{
		p->addPOINT(1);
		p->recovery(2);
	}
	bom = true;
	/*std::vector<FollingObject*>::iterator it = std::find(game->m_flist.begin(), game->m_flist.end(), this);
	game->m_flist.erase(it);*/
	DeleteGO(this);
}
void FollingObject::Chain()
{
	QueryGOs<FollingObject>("f", [&](FollingObject* fo)->bool
	{
		CVector3 d = fo->pos - pos;
		if (fo->bom && d.Length() < 200.0f && this != fo)
		{
			HP--;
		}
		return true;
	});
}
void FollingObject::END()
{
	
}

void FollingObject::Fall(float f)
{
	pos.y -= f;
	m_follingOb->SetPosition(pos);
}

void FollingObject::MoveWing()
{
	if (time <= wait)
	{
		pos += add;
		m_follingOb->SetPosition(pos);
		//float f = acosf((pos.z - addw.z)/sqrtf(pow(pos.x - addw.x, 2) + pow(pos.y - addw.y, 2) + pow(pos.z - addw.z, 2)));

		if (time % 3 == 0)
		{
			prefab::CEffect* effe = NewGO<prefab::CEffect>(0,"effe");
			effe->Play(L"effect/kem.efk");
			effe->SetPosition(pos);
			effe->SetScale({ 45,45,45 });
		}
		if (time == wait)
		{
			CVector3 pl = { 0.000001f,-20.0f,0.0f };
			CVector3 din = add;
			add = pos - pl;
			add.Normalize();
			//add *= -20;

			CVector3 v1;
			v1 = add;
			float theta = v1.ThetaVector(din);
			
			/*v1.Normalize();
			v2 = addw;
			v2.Normalize();
			float nai = v1.Dot(v2);
			float sita = acos(nai);
			v1.Cross(v2, v1);
			v1.Normalize();*/
			CQuaternion quater;
			quater.SetRotation(v1, theta);
			CQuaternion me = m_follingOb->GetRotation();
			quater.Multiply(me, quater);
			m_follingOb->SetRotation(quater);
		}
	}
	else
	{
		/*if (time % 3 == 0)
		{
			prefab::CEffect* effe = NewGO<prefab::CEffect>(0);
			effe->Play(L"effect/kem.efk");
			effe->SetPosition(pos);
			CVector3 dv = { 45,45,45 };
			dv /= (time - 25) / 5;
			effe->SetScale(dv);
		}*/
		pos += add * -20;
		m_follingOb->SetPosition(pos);
	}
	if (pos.Length() < 150)
	{
		p->damage(1);
		DeleteGO(this);
	}
	if (abs(pos.x) > 6000 || abs(pos.z) > 6000)
	{
		DeleteGO(this);
	}
}