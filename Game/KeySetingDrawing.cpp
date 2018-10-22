#include "stdafx.h"
#include "KeySetingDrawing.h"
#include "KeySet.h"
#include "Fade.h"
#include "ModeSelect.h"
#include "SoundManager.h"
#include "tkEngine/light/tkDirectionLight.h"

KeySetingDrawing::KeySetingDrawing()
{
}
KeySetingDrawing::~KeySetingDrawing()
{
	DeleteGO(ball);
	DeleteGO(light);
}

bool KeySetingDrawing::Start()
{

	ks = FindGO<KeySet>("KS");
	fade = FindGO<Fade>("Fade");
	fade->StartFadeIn();
	soundM = FindGO<SoundManager>("SM");

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
void KeySetingDrawing::Update()
{
	if (!seting)
	{
		if (Pad(0).IsTrigger(enButtonDown))
		{
			if (c < 6)
			{
				c++;
				soundM->PlaySE(0);
			}
		}
		if (Pad(0).IsTrigger(enButtonUp))
		{
			if (c > 0)
			{
				c--;
				soundM->PlaySE(0);
			}
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			seting = true;
			soundM->PlaySE(1);
		}
	}
	else
	{
		switch (c)
		{
		case 0:
			if (Pad(0).IsTrigger(enButtonLeft))
			{
				ks->speed -= 0.05f;
				soundM->PlaySE(0);
			}
			if (Pad(0).IsTrigger(enButtonRight))
			{
				ks->speed += 0.05f;
				soundM->PlaySE(0);
			}
			if (Pad(0).IsTrigger(enButtonA))
			{
				seting = false;
				soundM->PlaySE(1);
			}
			break;
		case 1:
			if (Pad(0).IsTriggerAnyKey())
			{
				ks->Firing = Pad(0).GetPushKey();
				seting = false;
				soundM->PlaySE(1);
			}
			break;
		case 2:
			if (Pad(0).IsTriggerAnyKey())
			{
				ks->speedUP = Pad(0).GetPushKey();
				seting = false;
				soundM->PlaySE(1);
			}
			break;
		case 3:
			if (Pad(0).IsTriggerAnyKey())
			{
				ks->speedDown = Pad(0).GetPushKey();
				seting = false;
				soundM->PlaySE(1);
			}
			break;
		case 4:
			if (Pad(0).IsTriggerAnyKey())
			{
				ks->ueponChengeL = Pad(0).GetPushKey();
				seting = false;
				soundM->PlaySE(1);
			}
			break;
		case 5:
			if (Pad(0).IsTriggerAnyKey())
			{
				ks->ueponChengeR = Pad(0).GetPushKey();
				seting = false;
				soundM->PlaySE(1);
			}
			break;
		case 6:
			soundM->PlaySE(1);
			NewGO<ModeSelect>(0);
			DeleteGO(this);
			break;
		}
	}
}
void KeySetingDrawing::PostRender(CRenderContext& rc)
{
	wchar_t text[256];
	wchar_t wcha[256];
	font.Begin(rc);
	CVector4 s = { 1.0f, 1.0f, 0.0f, 1.0f };
	CVector4 f = { 1.0f, 1.0f, 0.0f, 1.0f };
	CVector4 su = { 1.0f, 1.0f, 0.0f, 1.0f };
	CVector4 sd = { 1.0f, 1.0f, 0.0f, 1.0f };
	CVector4 cl = { 1.0f, 1.0f, 0.0f, 1.0f };
	CVector4 cr = { 1.0f, 1.0f, 0.0f, 1.0f };
	CVector4 end = { 1.0f, 1.0f, 0.0f, 1.0f };
	switch (c)
	{
	case 0:
		s = { 1.0f, 0.0f, 0.0f, 1.0f };
		break;
	case 1:
		f = { 1.0f, 0.0f, 0.0f, 1.0f };
		break;
	case 2:
		su = { 1.0f, 0.0f, 0.0f, 1.0f };
		break;
	case 3:
		sd = { 1.0f, 0.0f, 0.0f, 1.0f };
		break;
	case 4:
		cl = { 1.0f, 0.0f, 0.0f, 1.0f };
		break;
	case 5:
		cr = { 1.0f, 0.0f, 0.0f, 1.0f };
		break;
	case 6:
		end = { 1.0f, 0.0f, 0.0f, 1.0f };
		break;
	}
	float x =10, y = -70;
	swprintf_s(text, L"アナログスティック感度:%.2f", ks->speed);
	font.Draw(text, { x,y }, s, 0.0f, 1.0f, { 0.0f,0.0f });

	std::string text2 = ks->buttonTOstring(ks->Firing);
	mbstowcs(wcha, text2.c_str(), text2.length()+1);
	swprintf_s(text, L"発射ボタン:%s", wcha);
	font.Draw(text, { x,y*2 }, f, 0.0f, 1.0f, { 0.0f,0.0f });

	text2 = ks->buttonTOstring(ks->speedUP);
	mbstowcs(wcha, text2.c_str(), strlen(text2.c_str()) + 1);
	swprintf_s(text, L"ティック感度UPボタン:%s", wcha);
	font.Draw(text, { x,y*3 }, su, 0.0f, 1.0f, { 0.0f,0.0f });

	text2 = ks->buttonTOstring(ks->speedDown);
	mbstowcs(wcha, text2.c_str(), strlen(text2.c_str()) + 1);
	swprintf_s(text, L"スティック感度DOWNボタン:%s", wcha);
	font.Draw(text, { x,y*4 }, sd, 0.0f, 1.0f, { 0.0f,0.0f });

	text2 = ks->buttonTOstring(ks->ueponChengeL);
	mbstowcs(wcha, text2.c_str(), strlen(text2.c_str()) + 1);
	swprintf_s(text, L"武器変更LEFT:%s", wcha);
	font.Draw(text, { x,y*5 }, cl, 0.0f, 1.0f, { 0.0f,0.0f });

	text2 = ks->buttonTOstring(ks->ueponChengeR);
	mbstowcs(wcha, text2.c_str(), strlen(text2.c_str()) + 1);
	swprintf_s(text, L"武器変更RIGHT:%s", wcha);
	font.Draw(text, { x,y*6 }, cr, 0.0f, 1.0f, { 0.0f,0.0f });

	swprintf_s(text, L"終わる");
	font.Draw(text, { x,y*7 }, end, 0.0f, 1.0f, { 0.0f,0.0f });

	font.End(rc);
}