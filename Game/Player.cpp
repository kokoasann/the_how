#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}
Player::~Player()
{
}

bool Player::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f,0.1f,0.1f });
	m_skinModelRender->SetPosition({ 0.0f,0.0f, 0.0f });
	rol.SetRotationDeg(CVector3::AxisY, 90.0f);
	m_skinModelRender->SetRotation(rol);
	return true;
}

void Player::Update()
{
}