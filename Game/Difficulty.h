#pragma once
class Difficulty:public IGameObject
{
public:
	Difficulty();
	~Difficulty();
	enum difficulty
	{
		easy,
		normal,
		diff
	};
	difficulty D = normal;

	const difficulty GetDIiff(int i)
	{
		switch (i)
		{
		case 0:
			return easy;
			break;
		case 1:
			return normal;
			break;
		case 2:
			return diff;
			break;
		}
	}
};

