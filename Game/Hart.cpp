#include "stdafx.h"
#include "Hart.h"


Hart::Hart()
{
}
Hart::~Hart()
{
	for (auto H : hart)
	{
		DeleteGO(H);
	}
}

bool Hart::Start()
{
	for (int i = 0; i < 25; i++)
	{
		hart.push_back(NewGO<prefab::CSpriteRender>(0));
		hart[i]->Init(L"sprite/hato1.dds",20.0f,20.0f);
		hart[i]->SetPosition({ i * 20.0f-500.0f,-120.0f,0.0f });
	}

	return true;
}

void Hart::setingHart(int p,int old)
{
	if (p > hart.size() * 2)
	{
		for (int i = hart.size() - 1; int(p / 2)> i; i++)
		{
			int h;
			int w;
			if (hart.size() % 25 == 0)
			{
				h = hart.size() / 25;
				w = 0;
			}
			else
			{
				h = int(hart.size() / 25);
				w = hart.size() % 25;
			}
			hart.push_back(NewGO<prefab::CSpriteRender>(0));
			hart[hart.size()-1]->Init(L"sprite/hato0.dds", 20.0f, 20.0f);
			hart[hart.size()-1]->SetPosition({ w * 20.0f - 500.0f,h*20.0f-120.0f,0.0f });
		}
	}

	if (p > old)
	{
		for (int i = int(old / 2); i < int(p / 2); i++)
		{
			hart[i]->Init(L"sprite/hato1.dds", 20.0f, 20.0f);
		}
		if (p % 2 != 0)
		{
			hart[int(p / 2)]->Init(L"sprite/hato05.dds", 20.0f, 20.0f);
		}
	}
	else
	{
		
		for (int i = int(old / 2)-1; i > int(p / 2)-1; i--)
		{
			hart[i]->Init(L"sprite/hato0.dds", 20.0f, 20.0f);
		}
		/*if (p % 2 != 0)
		{
			hart[int(p / 2) - 1]->Init(L"sprite/hato05.dds", 20.0f, 20.0f);
			if (hart.size() - 1 > int(p / 2) + 1)
			{
				hart[int(p / 2) + 1]->Init(L"sprite/hato0.dds", 20.0f, 20.0f);
			}
		}*/

		if (p % 2 != 0)
		{
			hart[int(p / 2)]->Init(L"sprite/hato05.dds", 20.0f, 20.0f);
		}
		else
		{
			hart[int(p / 2)]->Init(L"sprite/hato0.dds", 20.0f, 20.0f);
		}
	}
	
	while (int(p/2) < hart.size()-1 && hart.size() > 25)
	{
		DeleteGO(hart[hart.size() - 1]);
		hart.pop_back();
	}
}

void Hart::recovery(int p)
{
	if (p > hart.size() * 2)
	{
		int h = hart.size() - 1;
		for (int i = hart.size() - 1; p / 2> i; i++)
		{
			hart.push_back(NewGO<prefab::CSpriteRender>(0));
			hart[hart.size() - 1]->Init(L"sprite/hato1.dds", 20.0f, 20.0f);
			hart[hart.size() - 1]->SetPosition({ (hart.size() - 1) * 20.0f - 500.0f,-120.0f,0.0f });
		}
	}
	for (int i = 0; i < hart.size(); i++)
	{
		hart[i]->Init(L"sprite/hato0.dds", 20.0f, 20.0f);
	}
	for (int i = 0; i < int(p / 2); i++)
	{
		hart[i]->Init(L"sprite/hato1.dds", 20.0f, 20.0f);
	}
	if (p % 2 != 0)
	{
		hart[int(p / 2)]->Init(L"sprite/hato05.dds", 20.0f, 20.0f);
	}
}
void Hart::damage(int p)
{

}
void Hart::del()
{
	DeleteGO(this);
}