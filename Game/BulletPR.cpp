#include "stdafx.h"
#include "BulletPR.h"
#include "MainObject.h"
#include "FollingObjectPR.h"
#include "EnemyShipPR.h"
#include "SoundManager.h"
#include "tkEngine/graphics/effect/tkEffect.h"

BulletPR::BulletPR()
{
}
BulletPR::~BulletPR()
{
	if (m_bullet != nullptr)
	{
		DeleteGO(m_bullet);
	}

}

bool BulletPR::Start()
{
	soundM = FindGO<SoundManager>("SM");
	//smd.Load(L"modelData/ray.cmo");
	//sm.Init(smd,0);
	//game = FindGO<Game>("Game");
	CMatrix mView = MainCamera().GetViewMatrixInv();
	mView.m[3][0] = 0.0f;
	mView.m[3][1] = 0.0f;
	mView.m[3][2] = 0.0f;

	CQuaternion qRot;
	qRot.SetRotation(mView);
	mo = FindGO<MainObject>("targetOb");

	target = MainCamera().GetTarget();
	switch (ue)
	{
	case uniBOM:
		m_bullet = NewGO <prefab::CSkinModelRender>(0);
		m_bullet->Init(L"modelData/univerceBOM.2.cmo", 0, 0, CSkinModel::enFbxUpAxisY);

		pos = MainCamera().GetPosition();
		m_bullet->SetPosition(pos);
		m_bullet->SetScale({ 0.1f,0.1f ,0.1f });
		m_bullet->SetRotation(qRot);
		CCC.Init(20.0f, 100.0f, pos);

		soundM->PlaySE(3);
		break;
	case uniBOM3:
		m_bullet = NewGO <prefab::CSkinModelRender>(0);
		m_bullet->Init(L"modelData/univerceBOM.2.cmo");
		pos = MainCamera().GetPosition();
		m_bullet->SetPosition(pos);
		m_bullet->SetScale({ 0.1f,0.1f ,0.1f });
		CCC.Init(20.0f, 100.0f, pos);

		for (int i = 0; i<2; i++)
		{
			child[i] = NewGO<prefab::CSkinModelRender>(0, "c");
			child[i]->Init(L"modelData/univerceBOM.2.cmo");
			child[i]->SetPosition(pos);
			child[i]->SetScale({ 0.1f,0.1f ,0.1f });
			poc[i] = pos;
			//smc[i].Init(smd,0);
			if (i)
			{
				CVector3 a = mo->ROL(90);
				a.y = target.y;

				tac[i] = a;
			}
			else
			{
				CVector3 a = mo->ROL(-90);
				a.y = target.y;
				tac[i] = a;
			}

		}
		soundM->PlaySE(3);
		break;
	case S_uniBOM:
		m_bullet = NewGO <prefab::CSkinModelRender>(0);
		m_bullet->Init(L"modelData/unibom.cmo", nullptr, 0, CSkinModel::enFbxUpAxisZ);
		pos = MainCamera().GetPosition();
		m_bullet->SetPosition(target / 790);
		m_bullet->SetScale({ 0.05f,0.05f ,0.05f });
		m_bullet->SetRotation(qRot);
		CCC.Init(10.0f, 10.0f, pos);

		soundM->PlaySE(3);
		break;
	case K_uniBOM:
		m_bullet = NewGO <prefab::CSkinModelRender>(0);
		m_bullet->Init(L"modelData/unityChan.cmo");

		pos = MainCamera().GetPosition();
		m_bullet->SetPosition(pos);
		CCC.Init(20.0f, 100.0f, pos);
		soundM->PlaySE(3);
		break;
	case uniBEEM:
		beemIN = NewGO<prefab::CEffect>(0,"pe");
		beemIN->Play(L"effect/beem_in.efk");
		beemIN->SetPosition({ target.x / 50.0f, 8 + target.y / 50.0f, target.z / 50.0f });
		beemIN->SetScale({ 1.5,1.5,1.5 });
		/*beem->SetRotation(rolY);
		beem->SetPosition(MainCamera().GetPosition());*/

		break;
	}
	return true;
}
void BulletPR::Update()
{
	CVector3 raypo = pos;
	switch (ue)
	{
	case uniBOM:
		move += target * 5;
		pos = CCC.Execute(GameTime().GetFrameDeltaTime(), move);
		//pos += target*2;
		m_bullet->SetPosition(pos);
		for (int i = 0; i < 50; i++)
		{
			raypo += target / 10;

			//sm.Update(raypo, CQuaternion::Identity, { 1,1,1 });
			QueryGOs<FollingObjectPR>("f", [&](FollingObjectPR* fo)->bool
			{
				CVector3 d = raypo - fo->pos;
				if (d.Length() < 200.0f)
				{
					fo->HP--;
				}
				return true;
			});
			QueryGOs<EnemyShipPR>("s", [&](EnemyShipPR* fo)->bool
			{
				if (fo != nullptr)
				{
					std::vector<CVector3> pd = fo->Jud();
					for (auto qb : pd)
					{
						CVector3 d = raypo - qb;
						if (d.Length() < 200.0f)
						{
							prefab::CEffect* e = NewGO < prefab::CEffect>(0,"pe");
							e->Play(L"effect/booon.efk");
							e->SetPosition(raypo);
							switch (fo->ship)
							{
							case 0:
								e->SetScale({ 50,50,50 });
								break;
							case 1:
								e->SetScale({ 5,5,5 });
								break;
							case 2:
								e->SetScale({ 50,50,50 });
								break;
							}
							fo->HP--;
						}
					}
				}
				return true;
			});
		}

		if (abs(pos.x) > 6000.0f || abs(pos.y) > 6000.0f || abs(pos.z) > 6000.0f)
		{
			//std::vector<Bullet*>::iterator it = std::find(game->m_blist.begin(), game->m_blist.end(), this);
			//game->m_blist.erase(it);
			DeleteGO(this);
		}
		break;
	case uniBOM3:
		move += target * 5;
		pos = CCC.Execute(GameTime().GetFrameDeltaTime(), move);
		m_bullet->SetPosition(pos);
		for (int i = 0; i<2; i++)
		{
			moc[i] += tac[i] * 5;
			poc[i] = CCC.Execute(GameTime().GetFrameDeltaTime(), moc[i]);
			child[i]->SetPosition(poc[i]);
		}
		for (int i = 0; i < 50; i++)
		{
			raypo += target / 10;
			/*rayc[0] += tac[0]/10;
			rayc[1] += tac[1] / 10;*/
			//sm.Update(raypo, CQuaternion::Identity, { 1,1,1 });
			/*smc[0].Update(rayc[0], CQuaternion::Identity, { 1,1,1 });
			smc[1].Update(rayc[1], CQuaternion::Identity, { 1,1,1 });*/
			QueryGOs<FollingObjectPR>("f", [&](FollingObjectPR* fo)->bool
			{
				CVector3 d[3];
				d[0] = raypo - fo->pos;
				d[1] = tac[0] / 10 - fo->pos;
				d[2] = tac[1] / 10 - fo->pos;
				//for (auto def : d)
				//{
				if (d[0].Length() < 200.0f || d[1].Length()< 200.0f || d[2].Length()< 200.0f)
				{
					fo->HP--;
				}
				//}
				return true;
			});
			QueryGOs<EnemyShipPR>("s", [&](EnemyShipPR* fo)->bool
			{
				if (fo != nullptr)
				{
					std::vector<CVector3> pd = fo->Jud();
					for (auto qb : pd)
					{
						CVector3 d = raypo - qb;
						if (d.Length() < 200.0f)
						{
							prefab::CEffect* e = NewGO < prefab::CEffect>(0,"pe");
							e->Play(L"effect/booon.efk");
							e->SetPosition(raypo);
							switch (fo->ship)
							{
							case 0:
								e->SetScale({ 50,50,50 });
								break;
							case 1:
								e->SetScale({ 5,5,5 });
								break;
							case 2:
								e->SetScale({ 50,50,50 });
								break;
							}
							fo->HP--;
						}
					}
				}
				return true;
			});
		}
		if (abs(pos.x) > 6000.0f || abs(pos.y) > 6000.0f || abs(pos.z) > 6000.0f)
		{
			DeleteGO(child[1]);
			DeleteGO(child[0]);
			DeleteGO(this);
		}
		break;
	case S_uniBOM:
		if (!BOOON)
		{
			move += target / 2;
			pos = CCC.Execute(GameTime().GetFrameDeltaTime(), move);
			m_bullet->SetPosition(pos);
			for (int i = 0; i < 5; i++)
			{
				raypo += pos + target / 10;
				//sm.Update(raypo, CQuaternion::Identity, { 1,1,1 });
				QueryGOs<FollingObjectPR>("f", [&](FollingObjectPR* fo)->bool
				{
					CVector3 d = raypo - fo->pos;
					if (fo->B == 5)
					{
						CVector3 pon = fo->pos;
						for (int i = 1; i <= 10; i++)
						{
							if (d.Length() < 200.0f)
							{
								prefab::CEffect* e = NewGO < prefab::CEffect>(0,"pe");
								e->Play(L"effect/boon.efk");
								e->SetPosition(raypo);
								e->SetScale({ 50,50,50 });
								DeleteGO(m_bullet);
								pos = raypo;
								BOOON = true;
								fo->HP--;
							}
							pon += fo->add * -4;
							d = raypo - pon;
						}
					}
					if (d.Length() < 200.0f)
					{
						prefab::CEffect* e = NewGO < prefab::CEffect>(0,"pe");
						e->Play(L"effect/boon.efk");
						e->SetPosition(raypo);
						e->SetScale({ 50,50,50 });
						DeleteGO(m_bullet);
						pos = raypo;
						BOOON = true;
						fo->HP--;
					}
					return true;
				});
				QueryGOs<EnemyShipPR>("s", [&](EnemyShipPR* fo)->bool
				{
					if (fo != nullptr)
					{
						std::vector<CVector3> pd = fo->Jud();
						for (auto qb : pd)
						{
							CVector3 d = raypo - qb;
							if (d.Length() < 200.0f)
							{
								prefab::CEffect* e = NewGO < prefab::CEffect>(0,"pe");
								e->Play(L"effect/booon.efk");
								e->SetPosition(raypo);
								switch (fo->ship)
								{
								case 0:
									e->SetScale({ 50,50,50 });
									break;
								case 1:
									e->SetScale({ 5,5,5 });
									break;
								case 2:
									e->SetScale({ 50,50,50 });
									break;
								}
								fo->HP--;
								DeleteGO(m_bullet);
								BOOON = true;
								pos = raypo;
							}
						}
					}
					return true;
				});

			}


			if (abs(pos.x) > 6000.0f || abs(pos.y) > 6000.0f || abs(pos.z) > 6000.0f)
			{
				/*std::vector<Bullet*>::iterator it = std::find(game->m_blist.begin(), game->m_blist.end(), this);
				game->m_blist.erase(it);*/
				DeleteGO(this);
			}
		}
		break;
	case K_uniBOM:
		break;
	case uniBEEM:
		if (beemIN->IsPlay())
		{
			target = MainCamera().GetTarget();
			CMatrix mView = MainCamera().GetViewMatrixInv();
			mView.m[3][0] = 0.0f;
			mView.m[3][1] = 0.0f;
			mView.m[3][2] = 0.0f;

			CQuaternion qRot;
			qRot.SetRotation(mView);
			beemIN->SetRotation(qRot);
			beemIN->SetPosition({ target.x / 50.0f, 8 + target.y / 50.0f, target.z / 50.0f });
			if (time >= 20 && beemin)
			{
				//game->b = true;
				beemin = false;
				time = 0;
				//DeleteGO(beemIN);

				beem = NewGO<prefab::CEffect>(0,"pe");
				beem->Play(L"effect/beem.efk");
				beem->SetRotation(qRot);
				beem->SetScale({ 3.5,3.5,3.5 });
				beem->SetPosition({ target.x / 50.0f, 8 + target.y / 50.0f, target.z / 50.0f });
				//beem->SetPosition({ 10.0f,10.0f,10.0f });
			}
			else if (beemin)
			{
				time++;
			}
		}
		if (push)
		{
			BEEEEEEEEEEEEEEE();
		}
		break;
	}
	if (BOOON)
	{
		if (time < 10)
		{
			BOOoooON += 50.0f;
			QueryGOs<FollingObjectPR>("f", [&](FollingObjectPR* fo)->bool
			{
				CVector3 d = pos - fo->pos;
				if (d.Length() <= BOOoooON)
				{
					fo->HP--;
				}
				return true;
			});
			QueryGOs<EnemyShipPR>("s", [&](EnemyShipPR* fo)->bool
			{
				if (fo != nullptr)
				{
					std::vector<CVector3> pd = fo->Jud();
					for (auto qb : pd)
					{
						CVector3 d = raypo - qb;
						if (d.Length() < 200.0f)
						{
							prefab::CEffect* e = NewGO < prefab::CEffect>(0,"pe");
							e->Play(L"effect/booon.efk");
							e->SetPosition(raypo);
							switch (fo->ship)
							{
							case 0:
								e->SetScale({ 50,50,50 });
								break;
							case 1:
								e->SetScale({ 5,5,5 });
								break;
							case 2:
								e->SetScale({ 50,50,50 });
								break;
							}
							fo->HP--;
						}
					}
				}
				return true;
			});
		}
		else if (time > 6)
		{
			DeleteGO(this);
		}
		time++;
	}
}
void BulletPR::BEEEEEEEEEEEEEEE()
{
	if (!beemin)
	{
		target = MainCamera().GetTarget();
		//カメラ行列の逆行列は、カメラのワールド行列。
		//ワールド行列とは、平行移動と回転と拡大を全て合成した行列。
		//そして、平行移動成分は、行列の4行目にあるため、
		//回転行列のみを取得したいので、4行目を０にしている。
		CMatrix mView = MainCamera().GetViewMatrixInv();
		mView.m[3][0] = 0.0f;
		mView.m[3][1] = 0.0f;
		mView.m[3][2] = 0.0f;

		CQuaternion qRot;
		qRot.SetRotation(mView);
		beem->SetRotation(qRot);
		beem->SetScale({ 1.5,1.5,1.5 });
		beem->SetPosition({ target.x / 50.0f, 8 + target.y / 50.0f, target.z / 50.0f });
		if (time >= 50)
		{
			beem->Play(L"effect/beem.efk");
			time = 0;
		}
		else
		{
			time++;
		}
	}
}

void BulletPR::BOOOOOOOOOOOONNN()
{

}