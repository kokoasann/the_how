#pragma once
#include "tkEngine/character/tkCharacterController.h"
class KeySet;
class MainObject:public IGameObject
{
public:
	MainObject();
	~MainObject();
	bool Start();
	void Update();
	void Rotation();
	CVector3 ROL(float f);
	void END();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 moveSpeed = CVector3::Zero;
	CCharacterController CCC;
	CQuaternion rol = { 0.0f,0.0f ,0.0f ,1.0f };
	float angle = 0,angleY = 0 , cx = 0, cz = 0, speed = 5.0f, radius = 800.0f, xstick = 0.0f, ystick = 0.0f;

	KeySet* ks = nullptr;
};

