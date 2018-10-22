#pragma once
class MainObject;
class MapPlayer:public IGameObject
{
public:
	MapPlayer();
	~MapPlayer();
	bool Start();
	void Update();
	MainObject* mo = nullptr;
	prefab::CSpriteRender* mp;
	CQuaternion rol;
};

