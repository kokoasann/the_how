#include "stdafx.h"
#include "Practice.h"
#include "PracticeDrawing.h"
#include "PracticeConfig.h"
#include "Fade.h"
#include "NumberDisplay.h"
#include "SoundManager.h"

PracticeDrawing::PracticeDrawing()
{
}
PracticeDrawing::~PracticeDrawing()
{
	DeleteGO(Manu);
	for (auto C : Choice)
	{
		DeleteGO(C);
	}
}

bool PracticeDrawing::Start()
{
	soundM = FindGO<SoundManager>("SM");
	PC = FindGO<PracticeConfig>("PC");
	Manu = NewGO<prefab::CSpriteRender>(0);
	Manu->Init(L"sprite/Manu.dds", 350, 530);
	MP = { -850,60,0 };
	Manu->SetPosition(MP);
	for (int i = 0; i < 4; i++)
	{
		Choice[i] = NewGO < prefab::CSpriteRender>(0);
		switch (i)
		{
		case 0:
			Choice[i]->Init(L"sprite/sskrY.dds", 1000.0f*0.3f, 399.0f*0.3f);
			break;
		case 1:
			Choice[i]->Init(L"sprite/sghtN.dds", 1000.0f*0.3f, 399.0f*0.3f);
			break;
		case 2:
			Choice[i]->Init(L"sprite/bebsN.dds", 1000.0f*0.3f, 399.0f*0.3f);
			break;
		case 3:
			Choice[i]->Init(L"sprite/rssrN.dds", 1000.0f*0.3f, 399.0f*0.3f);
			break;
		}
		float y = 220 - i * 120;
		float x = -850 - i * 80;
		ChoP[i] = {x,y,0};
		Choice[i]->SetPosition(ChoP[i]);
	}

	FindGO<Fade>("Fade")->StartFadeIn();
	return true;
}

void PracticeDrawing::Update()
{
	if (UpMove)
	{
		UP();
	}
	else if (DownMove)
	{
		DOWN();
	}
	else if (Pad(0).IsTrigger(enButtonSelect))
	{
		DownMove = true;
		if (ChildM != nullptr)
		{
			DeleteGO(Select);
			DeleteGO(ChildM);
			switch (cho)
			{
			case 0:
				for (auto n : ND)
					DeleteGO(n);
				for (auto ene : enemys)
				{
					DeleteGO(ene);
				}
				break;
			case 1:
				for (auto a : enemys)
					DeleteGO(a);
				for (auto a : mark)
					if(a != nullptr)
						DeleteGO(a);
				break;
			case 2:
				for (auto a : map)
					DeleteGO(a);
				break;
			}
		}
	}
	else if (!chenge)
	{
		if (Pad(0).IsTrigger(enButtonDown) && cho != 3)
		{
			switch (cho)
			{
			case 0:
				Choice[cho]->Init(L"sprite/sskrN.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			case 1:
				Choice[cho]->Init(L"sprite/sghtN.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			case 2:
				Choice[cho]->Init(L"sprite/bebsN.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			case 3:
				Choice[cho]->Init(L"sprite/rssrN.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			}
			cho++;
			switch (cho)
			{
			case 0:
				Choice[cho]->Init(L"sprite/sskrY.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			case 1:
				Choice[cho]->Init(L"sprite/sghtY.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			case 2:
				Choice[cho]->Init(L"sprite/bebsY.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			case 3:
				Choice[cho]->Init(L"sprite/rssrY.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			}
			soundM->PlaySE(0);
		}
		if (Pad(0).IsTrigger(enButtonUp) && cho != 0)
		{
			switch (cho)
			{
			case 0:
				Choice[cho]->Init(L"sprite/sskrN.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			case 1:
				Choice[cho]->Init(L"sprite/sghtN.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			case 2:
				Choice[cho]->Init(L"sprite/bebsN.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			case 3:
				Choice[cho]->Init(L"sprite/rssrN.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			}
			cho--;
			switch (cho)
			{
			case 0:
				Choice[cho]->Init(L"sprite/sskrY.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			case 1:
				Choice[cho]->Init(L"sprite/sghtY.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			case 2:
				Choice[cho]->Init(L"sprite/bebsY.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			case 3:
				Choice[cho]->Init(L"sprite/rssrY.dds", 1000.0f*0.3f, 399.0f*0.3f);
				break;
			}
			soundM->PlaySE(0);
		}

		if (Pad(0).IsTrigger(enButtonA))
		{
			switch (cho)
			{
			case 0:
			{
				ChildM = NewGO<prefab::CSpriteRender>(0);
				ChildM->Init(L"sprite/childM.dds", 240, 650);
				ChildM->SetPosition({ -250,30,0 });
				for (int i = 0; i < 5; i++)
				{

					enemys[i] = NewGO < prefab::CSpriteRender>(0);
					switch (i)
					{
					case 0:
						enemys[i]->Init(L"sprite/fat.dds", 100, 100);
						break;
					case 1:
						enemys[i]->Init(L"sprite/lit.dds", 100, 100);
						break;
					case 2:
						enemys[i]->Init(L"sprite/un.dds", 100, 100);
						break;
					case 3:
						enemys[i]->Init(L"sprite/sh.dds", 100, 100);
						break;
					case 4:
						enemys[i]->Init(L"sprite/s2.dds", 100, 100);
						break;
					}
					float y = 220 - i * 100;
					enemys[i]->SetPosition({ -250,y,0 });
				}
				Select = NewGO<prefab::CSpriteRender>(0);
				Select->Init(L"sprite/left.dds", 55, 34.2f);
				SelP.Set(10, 220, 0);
				Select->SetPosition(SelP);

				
				for (int i = 0; i < 5; i++)
				{
					ND[i] = NewGO<NumberDisplay>(0);
					float y = 220 - i * 100;
					ND[i]->NumDisplay(PC->GetProbability(i)*100,-130,y);
				}
				chenge = true;
			}
				break;
			case 1:
			{
				ChildM = NewGO<prefab::CSpriteRender>(0);
				ChildM->Init(L"sprite/childM.dds", 120, 650);
				ChildM->SetPosition({ -250,30,0 });
				for (int i = 0; i < 5; i++)
				{

					enemys[i] = NewGO < prefab::CSpriteRender>(0);
					switch (i)
					{
					case 0:
						enemys[i]->Init(L"sprite/fat.dds", 100, 100);
						break;
					case 1:
						enemys[i]->Init(L"sprite/lit.dds", 100, 100);
						break;
					case 2:
						enemys[i]->Init(L"sprite/un.dds", 100, 100);
						break;
					case 3:
						enemys[i]->Init(L"sprite/sh.dds", 100, 100);
						break;
					case 4:
						enemys[i]->Init(L"sprite/s2.dds", 100, 100);
						break;
					}
					float y = 220 - i * 100;
					enemys[i]->SetPosition({ -250,y,0 });
					if (PC->GetAppEnemy(i))
					{
						mark[i] = NewGO<prefab::CSpriteRender>(0);
						mark[i]->Init(L"sprite/mark.dds", 120, 120);
						mark[i]->SetPosition({ -250,y,0 });
					}
				}
				Select = NewGO<prefab::CSpriteRender>(0);
				Select->Init(L"sprite/left.dds", 55, 34.2f);
				SelP.Set(-200, 220, 0);
				Select->SetPosition(SelP);
				chenge = true;
			}
				break;
			case 2:
			{
				ChildM = NewGO<prefab::CSpriteRender>(0);
				ChildM->Init(L"sprite/childM.dds", 120, 650);
				ChildM->SetPosition({ -250,30,0 });
				for (int i = 0; i < 3; i++)
				{

					map[i] = NewGO < prefab::CSpriteRender>(0);
					switch (i)
					{
					case 0:
						map[i]->Init(L"sprite/map_earth.dds", 100, 100);
						break;
					case 1:
						map[i]->Init(L"sprite/map_space.dds", 100, 100);
						break;
					case 2:
						map[i]->Init(L"sprite/map_mystery.dds", 100, 100);
						break;
					}
					float y = 220 - i * 100;
					map[i]->SetPosition({ -250,y,0 });
					/*if (PC->GetAppEnemy(i))
					{
						mark[i] = NewGO<prefab::CSpriteRender>(0);
						mark[i]->Init(L"sprite/mark.dds", 120, 120);
						mark[i]->SetPosition({ -250,y,0 });
					}*/
				}
				Select = NewGO<prefab::CSpriteRender>(0);
				Select->Init(L"sprite/left.dds", 55, 34.2f);
				SelP.Set(-200, 220, 0);
				Select->SetPosition(SelP);
				chenge = true;
			}
				break;
			case 3:
				FindGO<Practice>("practice")->END();
				break;
			}
			soundM->PlaySE(1);
		}
		if (Pad(0).IsTrigger(enButtonB))
		{
			DownMove = true;
		}
	}
	else
	{
		switch (cho)
		{
		case 0:
			SSKR();
			break;
		case 1:
			SGHT();
			break;
		case 2:
			BEBS();
			break;
		case 3:
			break;
		}
	}
}

void PracticeDrawing::SSKR()
{
	if (Pad(0).IsTrigger(enButtonDown) && ECho < 4)
	{
		ECho++;
		float y = 220 - ECho * 100;
		SelP.Set(10, y, 0);
		Select->SetPosition(SelP);
		soundM->PlaySE(0);
	}
	if (Pad(0).IsTrigger(enButtonUp) && ECho > 0)
	{
		ECho--;
		float y = 220 - ECho * 100;
		SelP.Set(10, y, 0);
		Select->SetPosition(SelP);
		soundM->PlaySE(0);
	}
	if (Pad(0).IsTrigger(enButtonRight))
	{
		PC->SetProbability(ECho, PC->GetProbability(ECho)+0.05f);
		float y = 220 - ECho * 100;
		ND[ECho]->NumDisplay(PC->GetProbability(ECho)*100, -130, y);
		soundM->PlaySE(0);
	}
	if (Pad(0).IsTrigger(enButtonLeft))
	{
		PC->SetProbability(ECho, PC->GetProbability(ECho)-0.05f);
		float y = 220 - ECho * 100;
		ND[ECho]->NumDisplay(PC->GetProbability(ECho) * 100, -130, y);
		soundM->PlaySE(0);
	}
	if (Pad(0).IsTrigger(enButtonB))
	{
		for (auto n : ND)
			DeleteGO(n);
		DeleteGO(ChildM);
		DeleteGO(Select);
		for (auto ene : enemys)
		{
			DeleteGO(ene);
		}
		ECho = 0;
		chenge = false;
	}
}

void PracticeDrawing::SGHT()
{
	if (Pad(0).IsTrigger(enButtonDown) && ECho < 4)
	{
		ECho++;
		float y = 220 - ECho * 100;
		SelP.Set(-200, y, 0);
		Select->SetPosition(SelP);
		soundM->PlaySE(0);
	}
	if (Pad(0).IsTrigger(enButtonUp) && ECho > 0)
	{
		ECho--;
		float y = 220 - ECho * 100;
		SelP.Set(-200, y, 0);
		Select->SetPosition(SelP);
		soundM->PlaySE(0);
	}
	if (Pad(0).IsTrigger(enButtonA))
	{
		if (PC->GetAppEnemy(ECho))
		{
			PC->appEnemy(ECho,false);
			DeleteGO(mark[ECho]);
		}
		else
		{
			PC->appEnemy(ECho, true);
			float y = 220 - ECho * 100;
			mark[ECho] = NewGO<prefab::CSpriteRender>(1);
			mark[ECho]->Init(L"sprite/mark.dds", 120, 120);
			mark[ECho]->SetPosition({ -250,y,0 });
		}
		soundM->PlaySE(1);
	}
	if (Pad(0).IsTrigger(enButtonB))
	{
		DeleteGO(ChildM);
		DeleteGO(Select);
		for (auto ene : enemys)
		{
			DeleteGO(ene);
		}
		for (auto m : mark)
		{
			DeleteGO(m);
		}
		ECho = 0;
		chenge = false;
	}
}

void PracticeDrawing::BEBS()
{
	if (Pad(0).IsTrigger(enButtonDown) && ECho < 2)
	{
		ECho++;
		float y = 220 - ECho * 100;
		SelP.Set(-200, y, 0);
		Select->SetPosition(SelP);
		soundM->PlaySE(0);
	}
	if (Pad(0).IsTrigger(enButtonUp) && ECho > 0)
	{
		ECho--;
		float y = 220 - ECho * 100;
		SelP.Set(-200, y, 0);
		Select->SetPosition(SelP);
		soundM->PlaySE(0);
	}
	if (Pad(0).IsTrigger(enButtonA))
	{
		PC->SetBackGround(ECho);
		soundM->PlaySE(1);
	}
	if (Pad(0).IsTrigger(enButtonB))
	{
		DeleteGO(ChildM);
		DeleteGO(Select);
		for (auto m : map)
		{
			DeleteGO(m);
		}
		ECho = 0;
		chenge = false;
	}
}

void PracticeDrawing::UP()
{
	for (int i = 0; i < 4; i++)
	{
		if (ChoP[i].x <= -470)
		{
			ChoP[i].x += 40;
			Choice[i]->SetPosition(ChoP[i]);
		}
		else
		{
			if (i == 3)
			{
				UpMove = false;
			}
		}
	}
	if (MP.x <= -470)
	{
		MP.x += 40;
		Manu->SetPosition(MP);
	}
}
void PracticeDrawing::DOWN()
{
	for (int i = 0; i < 4; i++)
	{
		if (ChoP[i].x >= -850)
		{
			ChoP[i].x -= 40;
			Choice[i]->SetPosition(ChoP[i]);
		}
		else
		{
			if (i == 3)
			{
				DeleteGO(this);
				FindGO<Practice>("practice")->Seting = false;
				UpMove = false;
			}
		}
	}
	if (MP.x >= -850)
	{
		MP.x -= 40;
		Manu->SetPosition(MP);
	}
}

void PracticeDrawing::PostRender(CRenderContext &rc)
{
	/*if (cho == 0 && chenge)
	{
		wchar_t text[256];
		font.Begin(rc);
		for (int i = 0; i < 5; i++)
		{
			swprintf_s(text, L"%.1f", PC->GetProbability(i)*100.0f);
			float y = 220 - i * 100;
			font.Draw(text, { 200,-y }, { 255,0,255,0 });
		}
		font.End(rc);
	}*/
}