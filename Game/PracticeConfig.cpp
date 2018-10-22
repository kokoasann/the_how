#include "stdafx.h"
#include "PracticeConfig.h"
#include "pointPR.h"
#include "BackGroundPR.h"
#include "EnemyGeneratorPR.h"


PracticeConfig::PracticeConfig()
{
}
PracticeConfig::~PracticeConfig()
{
	DeleteGO(EGP);
	DeleteGO(BG);
}

bool PracticeConfig::Start()
{
	//p = NewGO<point>(0, "p");
	//BG = NewGO<BackGround>(0, "BG");
	
	EGP = NewGO<EnemyGeneratorPR>(0, "EGP");
	BG = NewGO<BackGroundPR>(0, "BG");

	m_font = std::make_unique < DirectX::SpriteFont>(GraphicsEngine().GetD3DDevice(), L"font/hato_pop.spritefont");
	font.SetFont(m_font.get());
	font.SetShadowParam(true, 2.0f, { 26.0f / 255.0f, 49 / 255.0f, 103 / 255.0f, 1.0f });

	return true;
}
void PracticeConfig::Update()
{

}

void PracticeConfig::SceneChenge(int s)
{
	BG->RemBackGround(Scene);
	BG->SetBackGround(s);
	Scene = s;
}

void PracticeConfig::appEnemy(int i, bool b)
{
	EGP->app[i] = b;
}

bool PracticeConfig::GetAppEnemy(int i)
{
	return EGP->app[i];
}

void PracticeConfig::probEne(int i, float f)
{
	EGP->Probabilitys[i] = f;
}

void PracticeConfig::SetBackGround(int i)
{
	BG->RemBackGround(BG->BG);
	BG->SetBackGround(i);
}

void PracticeConfig::RemoveBackGround(int i)
{
	BG->RemBackGround(i);
}

void PracticeConfig::SetProbability(int i,float f)
{
	if(f >= 0 && f <= 1)
		EGP->Probabilitys[i] = f;
}

float PracticeConfig::GetProbability(int i)
{
	return EGP->Probabilitys[i];
}
