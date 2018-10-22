#pragma once
class Rayder:public IGameObject
{
public:
	Rayder();
	~Rayder();
	void Update();
	void CreatEnemy(CVector3 pos);
	void CreatShip(CVector3 pos);

	prefab::CSpriteRender* enemy = nullptr;
	bool ship = false;
	bool advance = false;
	CVector3 po;
};

