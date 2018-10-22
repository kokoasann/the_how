#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	//CVector3 pos = CVector3::Zero;
	//CVector3 move = CVector3::Zero;
	CQuaternion rol = { 0.0f,0.0f ,0.0f ,1.0f };
};

