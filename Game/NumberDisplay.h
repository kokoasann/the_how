#pragma once
class NumberDisplay:public IGameObject
{
public:
	NumberDisplay();
	~NumberDisplay();
	void NumDisplay(float f,float x,float y);
	void NumDisplay(int i,float x,float y);
	void Clean();

	std::vector<prefab::CSpriteRender*> num;

};

