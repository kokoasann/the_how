#include "stdafx.h"
#include "CollectionMode.h"
#include "ModeSelect.h"
#include "Fade.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"
#include "SaveLoad.h"
#include "EffectTextureManeger.h"

CollectionMode::CollectionMode()
{
}
CollectionMode::~CollectionMode()
{
	for (auto lig : lightList) {
		DeleteGO(lig);
	}
	for (int i = 0; i < 2; i++)
	{
		for (auto skn : SMR[i])
		{
			DeleteGO(skn);
		}
		for (auto skn : frame[i])
		{
			DeleteGO(skn);
		}
	}
	DeleteGO(BOX);
}

bool CollectionMode::Start()
{
	EffectTextureManeger* ETM = FindGO<EffectTextureManeger>("etm");
	SaveLoad SL;
	FindGO<Fade>("Fade")->StartFadeIn();
	/*wchar_t* path[2][5];
	path[0][0] = L"modelData/cannon.2.cmo";
	path[0][1] = L"modelData/asu.cmo";
	path[0][2] = L"modelData/univerceBOM.2.cmo";
	path[0][3] = L"modelData/unibom.cmo";
	path[0][4] = L"modelData/fatman.3.cmo";
	path[1][0] = L"modelData/littleboy.cmo";
	path[1][1] = L"modelData/missile.cmo";
	path[1][2] = L"modelData/unni.cmo";
	path[1][3] = L"modelData/ship2.cmo";
	path[1][4] = L"modelData/ship1.2.cmo";*/
	int rk = 5;
	for (int iy = 0; iy < 2; iy++)
	{
		for (int ix = 0; ix < 5; ix++)
		{
			sel[iy][ix] = SL.Load(rk);
			rk++;
			frame[iy][ix] = NewGO<prefab::CSpriteRender>(1);
			frame[iy][ix]->Init(L"sprite/frame.dds", 80, 80, true);
			frame[iy][ix]->SetPosition({ float(ix * 80),float(iy * -80),50.0f });
			frame[iy][ix]->SetMulColor({ 4.0f, 4.0f, 4.0f, 1.0f });
			SMR[iy][ix] = NewGO<prefab::CSkinModelRender>(0);
			switch (iy)
			{
			case 0:
				switch (ix)
				{
				case 0:
					if (sel[iy][ix])
					{
						SMR[iy][ix]->Init(L"modelData/cannon2.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.05f,0.05f,0.05f });
					}
					else
					{
						SMR[iy][ix]->Init(L"modelData/hatena.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.2f,0.2f,0.2f });
					}
					break;
				case 1:
					if (sel[iy][ix])
					{
						SMR[iy][ix]->Init(L"modelData/asu.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.1f,0.1f,0.1f });
					}
					else
					{
						SMR[iy][ix]->Init(L"modelData/hatena.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.2f,0.2f,0.2f });
					}
					break;
				case 2:
					if (sel[iy][ix])
					{
						SMR[iy][ix]->Init(L"modelData/univerceBOM.2.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.05f,0.05f,0.05f });
					}
					else
					{
						SMR[iy][ix]->Init(L"modelData/hatena.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.2f,0.2f,0.2f });
					}
					break;
				case 3:
					if (sel[iy][ix])
					{
						SMR[iy][ix]->Init(L"modelData/unibom.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.05f,0.05f,0.05f });
					}
					else
					{
						SMR[iy][ix]->Init(L"modelData/hatena.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.2f,0.2f,0.2f });
					}
					break;
				case 4:
					if (sel[iy][ix])
					{
						SMR[iy][ix]->Init(L"modelData/fatman.3.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.05f,0.05f,0.05f });
						
						m_normalMapSRV = ETM->Load(L"sprite/fatman_nor.dds");
						m_specularMapSRV = ETM->Load(L"sprite/fatman_spe.dds");
						SMR[iy][ix]->FindMaterial([&](auto material)
						{
							material->SetNormalMap(m_normalMapSRV->GetBody());
							material->SetSpecularMap(m_specularMapSRV->GetBody());
						});
						//SMR[iy][ix]->SetShadowCasterFlag(true);
						//SMR[iy][ix]->SetShadowReceiverFlag(true);
					}
					else
					{
						SMR[iy][ix]->Init(L"modelData/hatena.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.2f,0.2f,0.2f });
					}
					break;
				}
				break;
			case 1:
				switch (ix)
				{
				case 0:
					if (sel[iy][ix])
					{
						SMR[iy][ix]->Init(L"modelData/littleboy.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.05f,0.05f,0.05f });

						m_normalMapSRV = ETM->Load(L"sprite/littleboy_bump2.dds");
						m_specularMapSRV = ETM->Load(L"sprite/littleboy_spe.dds");
						SMR[iy][ix]->FindMaterial([&](auto material)
						{
							material->SetNormalMap(m_normalMapSRV->GetBody());
							material->SetSpecularMap(m_specularMapSRV->GetBody());
						});
					}
					else
					{
						SMR[iy][ix]->Init(L"modelData/hatena.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.2f,0.2f,0.2f });
					}
					break;
				case 1:
					if (sel[iy][ix])
					{
						SMR[iy][ix]->Init(L"modelData/missile.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.5f,0.5f,0.5f });
					}
					else
					{
						SMR[iy][ix]->Init(L"modelData/hatena.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.2f,0.2f,0.2f });
					}
					break;
				case 2:
					if (sel[iy][ix])
					{
						SMR[iy][ix]->Init(L"modelData/unni.cmo");
						SMR[iy][ix]->SetScale({ 0.05f,0.05f,0.05f });
					}
					else
					{
						SMR[iy][ix]->Init(L"modelData/hatena.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.2f,0.2f,0.2f });
					}
					break;
				case 3:
					if (sel[iy][ix])
					{
						SMR[iy][ix]->Init(L"modelData/ship2.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.005f,0.005f,0.005f });
					}
					else
					{
						SMR[iy][ix]->Init(L"modelData/hatena.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.2f,0.2f,0.2f });
					}
					break;
				case 4:
					if (sel[iy][ix])
					{
						SMR[iy][ix]->Init(L"modelData/ship1.2.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.005f,0.005f,0.005f });
					}
					else
					{
						SMR[iy][ix]->Init(L"modelData/hatena.cmo", 0, 0, CSkinModel::enFbxUpAxisY);
						SMR[iy][ix]->SetScale({ 0.2f,0.2f,0.2f });
					}
					break;
				}
				break;
			}
			SMR[iy][ix]->SetPosition({ float(ix * 80),float(iy * -80),30.0f });
		}
	}
	MainCamera().SetPosition({ 160,-40,-600 });
	MainCamera().SetTarget({ 160,-40,50 });
	MainCamera().SetViewAngle(CMath::DegToRad(25.0f));
	MainCamera().Update();
	sel[0][0] = true;
	frame[0][0]->Init(L"sprite/frames.dds", 80, 80, true);

	auto light = NewGO<prefab::CDirectionLight>(0);
	lightpos.Set(-1.0f, 0.1f, 0.0f);
	GraphicsEngine().GetShadowMap().SetLightDirection(lightpos);
	light->SetDirection(lightpos);
	light->SetColor({ 30.3f, 30.3f, 30.3f, 1.0f });
	lightList.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	lightpos.Set(1.0f, 0.1f, 0.0f);
	light->SetDirection(lightpos);
	light->SetColor({ 310.3f, 310.3f, 310.3f, 1.0f });
	lightList.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	lightpos.Set(0.0, 0.1f, 1.0f);
	light->SetDirection(lightpos);
	light->SetColor({ 10.3f, 10.3f, 10.3f, 1.0f });
	lightList.push_back(light);

	light = NewGO<prefab::CDirectionLight>(0);
	lightpos.Set(0.0, 0.1f, -1.0f);
	light->SetDirection(lightpos);
	light->SetColor({ 10.3f, 10.3f, 10.3f, 1.0f });
	lightList.push_back(light);

	LightManager().SetAmbientLight({ 1.4f, 1.4f, 1.4f });

	auto PL = NewGO<prefab::CPointLight>(0);
	PL->SetPosition({ 0.0f,-80.0f,30.0f });
	PL->SetColor({ 100.0f,100.0f,100.0f,1.0f });
	PL->SetAttn({ 50.0f,1.0f,0.0f });

	BOX = NewGO < prefab::CSkinModelRender>(0);
	BOX->Init(L"modelData/box.cmo",0,0,CSkinModel::enFbxUpAxisY);
	BOX->SetPosition({ 160,-120,-600 });
	BOX->SetScale({ 5,3,5 });
	return true;
}

void CollectionMode::Update()
{
	if (!select)
	{
		if (Pad(0).IsTriggerAnyKey())
		{
			int ox, oy;
			ox = x;
			oy = y;
			if (Pad(0).IsTrigger(enButtonDown) && y < 1)
			{
				y++;
				Move(oy, ox, y, x);
				prefab::CSoundSource* SE = NewGO<prefab::CSoundSource>(0);
				SE->Init("sound/button.wav");
				SE->Play(false);
			}
			else if (Pad(0).IsTrigger(enButtonUp) && y > 0)
			{
				y--;
				Move(oy, ox, y, x);
				prefab::CSoundSource* SE = NewGO<prefab::CSoundSource>(0);
				SE->Init("sound/button.wav");
				SE->Play(false);
			}
			else if (Pad(0).IsTrigger(enButtonLeft) && x > 0)
			{
				x--;
				Move(oy, ox, y, x);
				prefab::CSoundSource* SE = NewGO<prefab::CSoundSource>(0);
				SE->Init("sound/button.wav");
				SE->Play(false);
			}
			else if (Pad(0).IsTrigger(enButtonRight) && x < 4)
			{
				x++;
				Move(oy, ox, y, x);
				prefab::CSoundSource* SE = NewGO<prefab::CSoundSource>(0);
				SE->Init("sound/button.wav");
				SE->Play(false);
			}
			else if (Pad(0).IsTrigger(enButtonA))
			{
				oSca = SMR[y][x]->GetScale()/2/30;
				objP = SMR[y][x]->GetPosition();
				CVector3 tar = { 500,-40,-660 };
				objM = objP - tar;
				objM /= -30;
				Cmove = true;
				select = true;
				prefab::CSoundSource* SE = NewGO<prefab::CSoundSource>(0);
				SE->Init("sound/pickup.wav");
				SE->Play(false);
			}
			else if (Pad(0).IsTrigger(enButtonB))
			{
				prefab::CSoundSource* SE = NewGO<prefab::CSoundSource>(0);
				SE->Init("sound/button.wav");
				SE->Play(false);
				NewGO<ModeSelect>(0, "modesel");
				DeleteGO(this);
			}
		}
		ang += 0.3;
		if (ang == 360)
		{
			ang = 0;
		}
		rot.SetRotationDeg(CVector3::AxisY, ang);
		for (int iy = 0; iy < 2; iy++)
		{
			for (int ix = 0; ix < 5; ix++)
			{
				SMR[iy][ix]->SetRotation(rot);
			}
		}
	}
	else
	{
		if (Cmove)
		{
			cam += 3;
			camT.x = 50 * sin(CMath::PI/180*cam) + 160;
			camT.z = 50 * cos(CMath::PI/180*cam) - 600;
			MainCamera().SetTarget(camT);
			MainCamera().Update();
			objP += objM;
			SMR[y][x]->SetPosition(objP);
			CVector3 sc = SMR[y][x]->GetScale() + oSca;
			SMR[y][x]->SetScale(sc);
			if (cam >= 90)
			{
				
				Cmove = false;
			}
		}
		else if (Cback)
		{
			cam -= 3;
			camT.x = 50 * sin(CMath::PI / 180 * cam) + 160;
			camT.z = 50 * cos(CMath::PI / 180 * cam) - 600;
			MainCamera().SetTarget(camT);
			MainCamera().Update();
			objP -= objM;
			SMR[y][x]->SetPosition(objP);
			CVector3 sc = SMR[y][x]->GetScale() - oSca;
			SMR[y][x]->SetScale(sc);
			if (cam <= 0)
			{
				SMR[y][x]->SetScale(oSca * 60);
				Cback = false;
				select = false;
			}
		}
		else
		{
			if (Pad(0).IsTrigger(enButtonB))
			{
				prefab::CSoundSource* SE = NewGO<prefab::CSoundSource>(0);
				SE->Init("sound/button.wav");
				SE->Play(false);
				Cback = true;
			}
			if (Pad(0).IsPress(enButtonRB1))
			{
				CVector3 sc = SMR[y][x]->GetScale() + oSca;
				SMR[y][x]->SetScale(sc);
			}
			if (Pad(0).IsPress(enButtonLB1))
			{
				CVector3 sc = SMR[y][x]->GetScale() - oSca;
				SMR[y][x]->SetScale(sc);
			}
			//Y軸周りの回転。
			float fY = Pad(0).GetLStickXF() * 2.0f;
			//X軸周りの回転。
			float fX = Pad(0).GetLStickYF() * 2.0f;
			//Y軸周りの回転クォータニオンを作成。
			CQuaternion qRotY;
			qRotY.SetRotationDeg(CVector3::AxisY, fY);
			CQuaternion me = SMR[y][x]->GetRotation();
			me.Multiply(qRotY, me);
			//X軸周りの回転クォータニオンを作成。
			CQuaternion qRotX;
			qRotX.SetRotationDeg(CVector3::AxisX, fX);
			me.Multiply(qRotX, me);
			SMR[y][x]->SetRotation(me);
			
		}
	}
}

void CollectionMode::Move(int oy,int ox,int y, int x)
{
	frame[oy][ox]->Init(L"sprite/frame.dds", 80, 80, true);
	frame[y][x]->Init(L"sprite/frames.dds", 80, 80, true);
}