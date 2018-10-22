#pragma once
class pointPR:public IGameObject
{
public:
	pointPR();
	~pointPR();
	void addPOINT();
	void ChainStop();

	int POINT = 0;
};

