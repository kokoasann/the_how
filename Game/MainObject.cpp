#include "stdafx.h"
#include "MainObject.h"
#include "KeySet.h"

MainObject::MainObject()
{
}
MainObject::~MainObject()
{
	DeleteGO(m_skinModelRender);
}
bool MainObject::Start()
{
	ks = FindGO<KeySet>("KS");
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f,0.1f,0.1f });
	m_skinModelRender->SetPosition({ 0.0f,5.0f, 0.0f });
	rol.SetRotationDeg(CVector3::AxisY, 90.0f);
	m_skinModelRender->SetRotation(rol);

	CCC.Init(0.0f, 0.0f, { 0.0f,5.0f, 0.0f });
	return true;
}
void MainObject::Rotation()
{
	float by = 2.0f;
	if (Pad(0).IsPress(ks->speedDown))
	{
		by = 1.0f;
	}
	else if (Pad(0).IsPress(ks->speedUP))
	{
		by = 4.0f;
	}
	angle += Pad(0).GetLStickXF()*ks->speed*by;
	if (angle < 0)
	{
		angle = 360.0f - abs(angle);
	}
	if (angle > 360.0f)
	{
		angle = angle - 360.0f;
	}
	moveSpeed.x = radius * sinf(CMath::PI / 180.0f * angle) + 0.000001f;
	moveSpeed.z = radius * cosf(CMath::PI / 180.0f * angle) + 0.000001f;

	angleY += Pad(0).GetLStickYF()*ks->speed*by;
	if (angleY < 0)
	{
		angleY = 360.0f - abs(angleY);
	}
	if (angleY > 360.0f)
	{
		angleY = angleY - 360.0f;
	}
	moveSpeed.y = radius * tanf(CMath::PI / 180.0f * angleY) + 0.000001f;

	//mouse
	angle += Pad(0).GetMouseX()*ks->speed*by;
	if (angle < 0)
	{
		angle = 360.0f - abs(angle);
	}
	if (angle > 360.0f)
	{
		angle = angle - 360.0f;
	}
	moveSpeed.x = radius * sinf(CMath::PI / 180.0f * angle) + 0.000001f;
	moveSpeed.z = radius * cosf(CMath::PI / 180.0f * angle) + 0.000001f;

	angleY += Pad(0).GetMouseY()*ks->speed*by;
	if (angleY < 0)
	{
		angleY = 360.0f - abs(angleY);
	}
	if (angleY > 360.0f)
	{
		angleY = angleY - 360.0f;
	}
	moveSpeed.y = radius * tanf(CMath::PI / 180.0f * angleY) + 0.000001f;
	
	//keybord
	/*if (Pad(0).IsPress(enButtonUp))
	{
		if (moveSpeed.y < 360.0f)
		{
			moveSpeed.y += 30.0f*by;
		}
	}
	if (Pad(0).IsPress(enButtonDown))
	{
		if (moveSpeed.y > 0)
		{
			moveSpeed.y -= 30.0f*by;
		}
	}
	if (Pad(0).IsPress(enButtonRight))
	{
		angle -= speed * by;
		if (angle < 0)
		{
			angle = 360.0f - abs(angle);
		}
		moveSpeed.x = radius * cosf(CMath::PI / 180.0f * angle) + 0.000001f;
		moveSpeed.z = radius * sinf(CMath::PI / 180.0f * angle) + 0.000001f;
	}
	if (Pad(0).IsPress(enButtonLeft))
	{
		angle += speed * by;
		if (angle > 360.0f)
		{
			angle = angle - 360.0f;
		}
		moveSpeed.x = radius * cosf(CMath::PI / 180.0f * angle) + 0.000001f;
		moveSpeed.z = radius * sinf(CMath::PI / 180.0f * angle) + 0.000001f;
	}*/
	//pos = CCC.Execute(GameTime().GetFrameDeltaTime(), moveSpeed);
	m_skinModelRender->SetPosition(moveSpeed);
}

void MainObject::Update()
{
	Rotation();
}
void MainObject::END()
{
	m_isActive = false;
}

CVector3 MainObject::ROL(float f)
{
	float pre = angle+f;
	CVector3 r;
	if (pre < 0)
	{
		pre = 360.0f - abs(pre);
	}
	if (pre > 360.0f)
	{
		pre = pre - 360.0f;
	}
	r.x = radius * sinf(CMath::PI / 180.0f * pre) + 0.000001f;
	r.z = radius * cosf(CMath::PI / 180.0f * pre) + 0.000001f;
	return r;
}