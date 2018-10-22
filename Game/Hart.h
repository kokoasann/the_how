#pragma once
class Hart:public IGameObject
{
public:
	Hart();
	~Hart();
	bool Start();
	void setingHart(int p,int old);
	void recovery(int p);
	void damage(int p);
	void del();
	std::vector<prefab::CSpriteRender*> hart;
};

