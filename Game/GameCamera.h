#pragma once
#include "MainObject.h"
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void Rotation();
	void Reaction();
	void END();
	void waikUP()
	{
		m_isActive = true;
	}
	void GroundShake();
	float radius = 800.0f;
	float speed = 5.0f;
	float angle = 0;
	//float angley = 0;
	float cx = 0, cz = 0;
	CVector3 moveSpead = CVector3::Zero;
	CVector3 target = CVector3::Zero;
	CVector3 pos = { 0.000001f, 10.0f, 0.0f };
	CVector3 back = CVector3::Zero;
	CVector3 shake = CVector3::Zero;
private:
	MainObject* m_target;
	bool reaction = false,GS = false;
};

