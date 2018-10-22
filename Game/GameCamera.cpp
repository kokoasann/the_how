#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
}
GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	m_target = FindGO<MainObject>("targetOb");

	MainCamera().SetTarget({ 30.0f, 0.0f, 0.0f });
	MainCamera().SetNear(0.1f);
	MainCamera().SetFar(100000.0f);
	MainCamera().SetViewAngle(CMath::DegToRad(60.0f));
	MainCamera().SetPosition(pos);
	MainCamera().Update();
	
	return true;
}
void GameCamera::Rotation()
{
	float by = 1.0f;
	if (Pad(0).IsPress(enButtonB))
	{
		by = 2.0f;
	}
	if (Pad(0).IsPress(enButtonUp))
	{
		if (moveSpead.y < 360.0f)
		{
			moveSpead.y += 10.0f*by;
		}
	}
	if (Pad(0).IsPress(enButtonDown))
	{
		if (moveSpead.y > 0)
		{
			moveSpead.y -= 10.0f*by;
		}
	}
	if (Pad(0).IsPress(enButtonRight))
	{
		angle -= speed * by;
		if (angle < 0)
		{
			angle = 360.0f - abs(angle);
		}
		moveSpead.x = radius * cosf(CMath::PI / 180.0f * angle) + 0.000001f;
		moveSpead.z = radius * sinf(CMath::PI / 180.0f * angle) + 0.000001f;
	}
	if (Pad(0).IsPress(enButtonLeft))
	{
		angle += speed * by;
		if (angle > 360.0f)
		{
			angle = angle - 360.0f;
		}
		moveSpead.x = radius * cosf(CMath::PI / 180.0f * angle) + 0.000001f;
		moveSpead.z = radius * sinf(CMath::PI / 180.0f * angle) + 0.000001f;
	}
	MainCamera().SetTarget(moveSpead);
	MainCamera().Update();
}
void GameCamera::Update()
{
	if (m_isActive)
	{
		target = m_target->moveSpeed;
		MainCamera().SetTarget(target);
		MainCamera().Update();

		if (reaction)
		{
			MainCamera().SetPosition(MainCamera().GetPosition() - back / 10.0f);
			if ((MainCamera().GetPosition() - pos).Length() <= 5.0f | (back).Length() < (MainCamera().GetPosition()).Length())
			{
				MainCamera().SetPosition(pos);
				reaction = false;
			}
		}
		if (GS)
		{
			shake *= -1;
			MainCamera().SetPosition(shake);
			if (shake.Length() == 0.0f)
			{
				GS = false;
			}
			if (shake.z < 0)
			{
				shake.z++;
			}
			else
			{
				shake.z--;
			}
		}
	}
}
void GameCamera::Reaction()
{
	back = m_target->moveSpeed/10.0f;
	back.y = 0.0f;
	if (!reaction)
	{
		MainCamera().SetPosition(pos-back);
		reaction = true;
	}
}
void GameCamera::GroundShake()
{
	shake.z = 25.0f;
	if (!GS)
	{
		MainCamera().SetPosition(shake);
		GS = true;
	}
	
}
void GameCamera::END()
{
	m_isActive = false;
	//DeleteGO(this);
}