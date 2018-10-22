#pragma once
class Hart;
class Game;
class FollingObjectGenerator;
class Difficulty;
class point :public IGameObject
{
public:
	point();
	~point();
	bool Start();
	void addPOINT(int i);
	void damage(int i);
	void recovery(int i);
	void End();
	void breakHart();
	void Bonus();
	void ReFind();

	Hart* hart = nullptr;
	Game* game = nullptr;
	FollingObjectGenerator* FOG = nullptr;
	Difficulty* diffi = nullptr;
	int POINT = 0;
	int GBBBpoi = 0;
	int lug = 0;
	int HP = 50;
	bool firstShipBreak = false;
	bool firstShipEnd = false;
	bool F110 = true;
	bool superWave = false;
	bool noHit = false;
	bool GBBB = true;
};

