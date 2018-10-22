#include "stdafx.h"
#include "NumberDisplay.h"


NumberDisplay::NumberDisplay()
{
}


NumberDisplay::~NumberDisplay()
{
	for (auto n : num)
	{
		DeleteGO(n);
	}
}

void NumberDisplay::NumDisplay(float f,float x,float y)
{
	Clean();
	std::string st = std::to_string(f);
	bool last = false;
	int count = 0;
	float addx = 0;
	for (auto c : st)
	{
		prefab::CSpriteRender* sr = NewGO < prefab::CSpriteRender>(0);
		switch (c)
		{
		case '0':
			sr->Init(L"sprite/num_0.dds", 100, 100);
			sr->SetPosition({ x + addx,y,0 });
			num.push_back(sr);
			break;
		case '1':
			sr->Init(L"sprite/num_1.dds", 100, 100);
			sr->SetPosition({ x + addx,y,0 });
			num.push_back(sr);
			break;
		case '2':
			sr->Init(L"sprite/num_2.dds", 100, 100);
			sr->SetPosition({ x + addx,y,0 });
			num.push_back(sr);
			break;
		case '3':
			sr->Init(L"sprite/num_3.dds", 100, 100);
			sr->SetPosition({ x + addx,y,0 });
			num.push_back(sr);
			break;
		case '4':
			sr->Init(L"sprite/num_4.dds", 100, 100);
			sr->SetPosition({ x + addx,y,0 });
			num.push_back(sr);
			break;
		case '5':
			sr->Init(L"sprite/num_5.dds", 100, 100);
			sr->SetPosition({ x + addx,y,0 });
			num.push_back(sr);
			break;
		case '6':
			sr->Init(L"sprite/num_6.dds", 100, 100);
			sr->SetPosition({ x + addx,y,0 });
			num.push_back(sr);
			break;
		case '7':
			sr->Init(L"sprite/num_7.dds", 100, 100);
			sr->SetPosition({ x + addx,y,0 });
			num.push_back(sr);
			break;
		case '8':
			sr->Init(L"sprite/num_8.dds", 100, 100);
			sr->SetPosition({ x + addx,y,0 });
			num.push_back(sr);
			break;
		case '9':
			sr->Init(L"sprite/num_9.dds", 100, 100);
			sr->SetPosition({ x + addx,y,0 });
			num.push_back(sr);
			break;
		case '.':
			sr->Init(L"sprite/num_pili.dds", 100, 100);
			sr->SetPosition({ x + addx,y,0 });
			num.push_back(sr);
			last = true;
			break;
		}
		addx += 80;
		if (last)
		{
			count++;
			if (count == 2)
			{
				break;
			}
		}
	}
}

void NumberDisplay::NumDisplay(int i,float x,float y)
{
}

void NumberDisplay::Clean()
{
	for (auto n : num)
	{
		DeleteGO(n);
		/*std::vector<prefab::CSpriteRender*>::iterator it = std::find(num.begin(), num.end(), n);
		num.erase(it);*/
	}
	num.resize(0);
}
