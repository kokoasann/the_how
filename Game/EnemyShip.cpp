#include "stdafx.h"
#include "EnemyShip.h"
#include "FollingObject.h"
#include "Bullet.h"
#include "point.h"
#include "Rayder.h"
#include "SoundManager.h"

EnemyShip::EnemyShip()
{
}
EnemyShip::~EnemyShip()
{
	DeleteGO(m_ship);
	DeleteGO(r);
}

bool EnemyShip::Start()
{
	soundM = FindGO<SoundManager>("SM");
	SoundManager* soundMr = NewGO<SoundManager>(0);
	soundMr->PlaySE(8, true);
	p = FindGO<point>("p");
	dp.resize(4);
	switch (ship)
	{
	case Mdl_Calico:
		if (firstShip)
		{
			HP = 100;
		}
		else
		{
			HP = 200;
		}
		x = Random().GetRandDouble();
		z = Random().GetRandDouble();
		while (x < 0.5f || z < 0.5f)
		{
			x = Random().GetRandDouble();
			z = Random().GetRandDouble();
		}
		if (Random().GetRandDouble() <= 0.5f)
		{
			x *= -1;
		}
		if (Random().GetRandDouble() <= 0.5f)
		{
			z *= -1;
		}
		x *= 5000.0f;
		z *= 5000.0f;
		m_ship = NewGO < prefab::CSkinModelRender>(0);
		m_ship->Init(L"modelData/ship2.cmo",0,0,CSkinModel::enFbxUpAxisY);
		m_ship->SetScale({ 0.35f,0.35f, 0.35f });
		m_ship->SetPosition({x,550.0f, z });
		pos.Set(x, 550.0f, z);
		add = pos / 2000.0f;
		add *= -1;
		add.y = 0.0f;
		
		Q = CQuaternion::Identity;

		/*CVector3 xx = CVector3::Zero - 

		CVector3 yy = CVector3::Cross();*/
		atan = atan2(MainCamera().GetPosition().x - x, MainCamera().GetPosition().z -z);
		//atan *= -1;
		//Q.y = atan;
		Q.SetRotation(CVector3::AxisY, atan);
		m_ship->SetRotation(Q);

		break;
	case MCBOM:
		HP = 50;
		m_ship = NewGO < prefab::CSkinModelRender>(0);
		m_ship->Init(L"modelData/ship2.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
		m_ship->SetScale({ 0.02f,0.02f,0.02f });
		m_ship->SetRotation(Q);
		break;
	case GBBBShip:
		HP = 300;
		x = Random().GetRandDouble();
		z = Random().GetRandDouble();
		while (x < 0.5f || z < 0.5f)
		{
			x = Random().GetRandDouble();
			z = Random().GetRandDouble();
		}
		if (Random().GetRandDouble() <= 0.5f)
		{
			x *= -1;
		}
		if (Random().GetRandDouble() <= 0.5f)
		{
			z *= -1;
		}
		x *= 4000.0f;
		z *= 4000.0f;
		pos.Set(x, 10.0f, z);

		/*QueryGOs<EnemyShip>("b", [&](EnemyShip* bu)->bool
		{
			if (bu->ship == GBBBShip)
			{
				CVector3 di = pos - bu->pos;
				while (di.Length() < 1200.0f)
				{
					x = Random().GetRandDouble();
					z = Random().GetRandDouble();
					while (x < 0.5f || z < 0.5f)
					{
						x = Random().GetRandDouble();
						z = Random().GetRandDouble();
					}
					if (Random().GetRandDouble() <= 0.5f)
					{
						x *= -1;
					}
					if (Random().GetRandDouble() <= 0.5f)
					{
						z *= -1;
					}
					x *= 4000.0f;
					z *= 4000.0f;
					pos.Set(x, 10.0f, z);
					di = pos - bu->pos;
				}
			}
			return true;
		});*/

		m_ship = NewGO < prefab::CSkinModelRender>(0);
		m_ship->Init(L"modelData/ship1.2.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
		m_ship->SetScale({ 0.2f,0.2f, 0.2f });
		m_ship->SetPosition({ x,0.0f, z });
		add = pos / 2000.0f;
		add *= -1;
		add.y = 0.0f;

		Q = CQuaternion::Identity;
		atan = atan2(MainCamera().GetPosition().x - x, MainCamera().GetPosition().z - z);
		Q.SetRotation(CVector3::AxisY, atan);
		m_ship->SetRotation(Q);
		
		dp[0] = { 0,0,0 };
		dp[1] = { 600,0,0 };
		dp[2] = { -600,0,0 };
		CMatrix mTrans, mRot, mWorld;
		mTrans.MakeTranslation(pos);
		mRot.MakeRotationFromQuaternion(Q);
		mWorld.Mul(mRot, mTrans);
		for (int i = 0; i < 3; i++)
		{
			mWorld.Mul(dp[i]);
		}
		break;
	}
	m_ship->SetShadowCasterFlag(true);
	m_ship->SetShadowReceiverFlag(true);
	k = add*-1;
	if (k.x > k.z)
	{

		k.x /= abs(k.x);
		k.z /= abs(add.x);
	}
	else
	{
		k.z /= abs(k.z);
		k.x /= abs(add.z);
	}
	k.y = 0;
	r = NewGO<Rayder>(0);
	r->CreatShip(pos);
	return true;
}
void EnemyShip::Update()
{
	//CVector3 d;
	//switch (ship)
	//{
	//case Mdl_Calico:
	//	dp[0] = pos;
	//	dp[0].y = 800.0f;
	//	dp[1] = pos;
	//	dp[1] += k * 500;
	//	dp[1].y = 800.0f;
	//	
	//	QueryGOs<Bullet>("b", [&](Bullet* bu)->bool
	//	{
	//		for (int i = 0;i < 2;i++)
	//		{
	//			d = bu->pos - dp[i];
	//			if (d.Length() < 500.0f)
	//			{
	//				prefab::CEffect* e = NewGO < prefab::CEffect>(0);
	//				e->Play(L"effect/booon.efk");
	//				e->SetScale({ 50,50,50 });
	//				//dp[i].y -= 1000.0f;
	//				e->SetPosition(bu->pos);
	//				HP--;
	//			}
	//			if (bu->BOOON)
	//			{
	//				if (d.Length() < bu->BOOoooON)
	//					HP--;
	//			}
	//		}
	//		return true;
	//	});
	//	break;
	//case GBBBShip:
	//	QueryGOs<Bullet>("b", [&](Bullet* bu)->bool
	//	{
	//		for (int i = 0; i < 2; i++)
	//		{
	//			d = bu->pos - dp[i];
	//			if (d.Length() < 500.0f)
	//			{
	//				prefab::CEffect* e = NewGO < prefab::CEffect>(0);
	//				e->Play(L"effect/booon.efk");
	//				e->SetScale({ 50,50,50 });
	//				//dp[i].y -= 1000.0f;
	//				e->SetPosition(bu->pos);
	//				HP--;
	//			}
	//			if (bu->BOOON)
	//			{
	//				if (d.Length() < bu->BOOoooON)
	//					HP--;
	//			}
	//		}
	//		return true;
	//	});
	//	break;
	//case MCBOM:
	//	QueryGOs<Bullet>("b", [&](Bullet* bu)->bool
	//	{
	//		d = bu->pos - pos;
	//		if (d.Length() < 100.0f)
	//		{
	//			prefab::CEffect* e = NewGO < prefab::CEffect>(0);
	//			e->Play(L"effect/booon.efk");
	//			e->SetScale({ 50,50,50 });
	//			//dp[i].y -= 1000.0f;
	//			e->SetPosition(bu->pos);
	//			HP--;
	//		}
	//		if (bu->BOOON)
	//		{
	//			if (d.Length() < bu->BOOoooON)
	//				HP--;
	//		}
	//		return true;
	//	});
	//	break;
	//}
	if (!Dead)
	{
		switch (step)
		{
			//Step(2)
		case cross:

			if (wait <= time && abs(pos.x) <= 600.0f && abs(pos.z) <= 600.0f)
			{
				FollingObject* f = NewGO<FollingObject>(0, "f");
				f->B = FollingObject::BOMB::ShipFoll;
				f->pos = pos;
				time = 0;
			}
			pos += add;
			m_ship->SetPosition(pos);
			break;
			//Step(0)
		case first:
			break;
			//Step(1)
		case drop:
			if (Random().GetRandDouble() < 0.01f)
			{
				EnemyShip* ene = NewGO<EnemyShip>(0, "s");
				ene->ship = MCBOM;
				ene->step = advance;
				CVector3 posa = m_ship->GetPosition();
				CQuaternion rot = m_ship->GetRotation();
				CMatrix mTrans, mRot, mWorld;
				mTrans.MakeTranslation(posa);
				mRot.MakeRotationFromQuaternion(rot);
				mWorld.Mul(mRot, mTrans);

				ene->pos = CVector3::Zero;
				if (Random().GetRandDouble() <= 0.5)
				{
					ene->pos.x = 600;
				}
				else
				{
					ene->pos.x = -600;
				}
				ene->pos.z = 800;
				ene->pos.y = 10;
				//ローカル座標をワールド座標に変換する。
				mWorld.Mul(ene->pos);
				ene->Q = Q;
				ene->add = add * 5;
			}
			if (wait <= time && Random().GetRandDouble() <= 0.1)
			{
				soundM->PlaySE(6);
				CVector3 aaa[8];
				aaa[0] = { 200,90,0 };
				aaa[1] = { -200,90,0 };
				aaa[2] = { 150.0f,130,0 };
				aaa[3] = { -150.0f,130,0 };
				aaa[4] = { 100.5f,170,0 };
				aaa[5] = { -100.5f,170,0 };
				aaa[6] = { 50,200,0 };
				aaa[7] = { -50,200,0 };
				for (auto a : aaa)
				{
					FollingObject* fo = NewGO<FollingObject>(0, "s");
					fo->B = FollingObject::BOMB::wing;
					CQuaternion rot = m_ship->GetRotation();
					CMatrix mTrans, mRot, mWorld;
					mTrans.MakeTranslation(CVector3::Zero);
					mRot.MakeRotationFromQuaternion(rot);
					mWorld.Mul(mRot, mTrans);
					fo->add = a;
					mWorld.Mul(fo->add);
					fo->add.Normalize();
					fo->add *= 30;
					CVector3 poi = pos;
					poi.y += 50;
					fo->pos = pos;


					CVector3 v1;
					v1 = fo->add;
					float theta = v1.ThetaVector(CVector3::AxisZ);
					/*v1.Normalize();
					v2 = CVector3::AxisZ;
					float nai = v1.Dot(v2);
					float sita = acos(nai);
					v1.Cross(v2,v1);
					v1.Normalize();*/
					CQuaternion quater;
					quater.SetRotation(v1, theta);
					CQuaternion me = CQuaternion::Identity;
					quater.Multiply(me, quater);
					fo->rol = quater;
				}
				time = 0;
			}
			else if (wait <= time)
			{
				time = 0;
			}
			break;
		case advance:
			pos += add;
			m_ship->SetPosition(pos);
			if (wait <= time && Random().GetRandDouble() < 0.5)
			{
				FollingObject* f = NewGO<FollingObject>(0, "f");
				f->B = FollingObject::BOMB::ShipFoll2;
				f->pos = pos;
				CVector3 di = pos - MainCamera().GetPosition();
				di.Normalize();
				f->add = di * 10 * -1;
				f->add.y = 0;
				time = 0;
			}

			break;
		}

		if (HP <= 0)
		{
			if (firstShip)
			{
				p->firstShipBreak = true;
			}
			if (firstShip && ship == GBBBShip)
			{
				p->GBBBpoi++;
			}
			p->addPOINT(1);
			Dead = true;
			time = 0;
			//DeleteGO(this);
		}
		if (abs(pos.x) > 6000 || abs(pos.z) > 6000)
		{
			if (firstShip)
			{
				p->firstShipEnd = true;
			}
			DeleteGO(this);
		}
	}
	else
	{
		switch (ship)
		{
		case Mdl_Calico:
			if (Random().GetRandDouble() < 0.3 && time < 150)
			{
				prefab::CEffect* ef = NewGO<prefab::CEffect>(0,"effe");
				ef->Play(L"effect/bom.efk");
				ef->SetScale({ 50,50,50 });
				CVector3 epos = CVector3::Zero;
				epos.x = Random().GetRandDouble() * 400 * (Random().GetRandDouble() <= 0.5 ? -1 : 1);
				epos.y = Random().GetRandDouble() * 400 * (Random().GetRandDouble() <= 0.5 ? -1 : 1);
				epos.z = Random().GetRandDouble() * 400 * (Random().GetRandDouble() <= 0.5 ? -1 : 1);
				epos += pos;
				ef->SetPosition(epos);
				soundM->PlaySE(4);
			}
			else if (time == 150)
			{
				prefab::CSkinModelRender* booom = NewGO<prefab::CSkinModelRender>(0, "booom");
				booom->Init(L"modelData/booom.cmo");
				booom->SetPosition(pos);
				booom->SetScale(CVector3({ 5,5,5 })*time);
				/*prefab::CEffect* ef = NewGO<prefab::CEffect>(0);
				ef->Play(L"effect/bom.efk");
				ef->SetPosition(pos);
				ef->SetScale({ 400,400,400 });*/

			}
			else if (time > 200)
			{
				DeleteGO(FindGO < prefab::CSkinModelRender>("booom"));
				DeleteGO(this);
			}
			else if (time >= 150)
			{
				FindGO<prefab::CSkinModelRender>("booom")->SetScale(CVector3({ 5,5,5 })*time);
			}
			break;
		case MCBOM:
			DeleteGO(this);
			break;
		case GBBBShip:
			if (Random().GetRandDouble() < 0.3 && time < 150)
			{
				prefab::CEffect* ef = NewGO<prefab::CEffect>(0,"effe");
				ef->Play(L"effect/bom.efk");
				ef->SetScale({ 50,50,50 });
				CVector3 epos = CVector3::Zero;
				epos.x = Random().GetRandDouble() * 600 * (Random().GetRandDouble() <= 0.5 ? -1 : 1);
				epos.y = Random().GetRandDouble() * 500 * (Random().GetRandDouble() <= 0.5 ? -1 : 1);
				epos.z = Random().GetRandDouble() * 600 * (Random().GetRandDouble() <= 0.5 ? -1 : 1);
				epos += pos;
				ef->SetPosition(epos);
				soundM->PlaySE(4);
			}
			else if (time == 150)
			{
				prefab::CSkinModelRender* booom = NewGO<prefab::CSkinModelRender>(0, "booom");
				booom->Init(L"modelData/booom.cmo");
				booom->SetPosition(pos);
				booom->SetScale(CVector3({ 5,5,5 })*time);
				/*prefab::CEffect* ef = NewGO<prefab::CEffect>(0);
				ef->Play(L"effect/bom.efk");
				ef->SetPosition(pos);
				ef->SetScale({ 400,400,400 });*/

			}
			else if (time > 200)
			{
				DeleteGO(FindGO < prefab::CSkinModelRender>("booom"));
				DeleteGO(this);
			}
			else if (time >= 150)
			{
				FindGO<prefab::CSkinModelRender>("booom")->SetScale(CVector3({ 5,5,5 })*time);
			}
			break;
		}
	}
	time++;
	r->po = pos;
}
void EnemyShip::ShipBrain()
{

}

std::vector<CVector3> EnemyShip::Jud()
{
	switch (ship)
	{
	case Mdl_Calico:
		dp.clear();
		dp.push_back(pos);
		dp[0].y = 800.0f;
		dp.push_back(pos);
		dp[1] += k * 500;
		dp[1].y = 800.0f;
		return dp;
		break;
	case MCBOM:
		dp.clear();
		dp.push_back(pos);
		return dp;
		break;
	case GBBBShip:
		dp.resize(3);
		return dp;
		break;
	}
}