#pragma once
#include "tkEngine/sound/tkSoundSource.h"
#include "tkEngine/graphics/effect/tkEffect.h"

class Player;
class GameCamera;
class MainObject;
class FollingObject;
class Bullet;
class point;
class BackGround;
class MapPlayer;
class Fade;
class KeySet;
class Hart;
class SoundManager;
class EnemyMator;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void STOP();
	void RESTART();
	void Render(CRenderContext& rc);
	void PostRender(CRenderContext& rc);

	prefab::CSpriteRender* Map;
	prefab::CSpriteRender* Aim;

	MainObject* m_mob = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_camera = nullptr;
	FollingObject* m_fObj = nullptr;
	Bullet* m_bullet = nullptr;
	Bullet* m_beem = nullptr;
	point* p = nullptr;
	BackGround* BG = nullptr;
	MapPlayer* mp = nullptr;
	Fade* fade = nullptr;
	KeySet* ks = nullptr;
	Hart* hart = nullptr;
	SoundManager* soundM = nullptr;
	EnemyMator* em = nullptr;

	//std::vector<prefab::CDirectionLight*> lightList;
	//CVector3 lightpos = CVector3::Zero;

	CFont font;
	std::unique_ptr<DirectX::SpriteFont> m_font;

	std::vector<FollingObject*> m_flist;
	std::vector<Bullet*> m_blist;

	bool active = true;
	bool beem = false;
	bool b = false;

	bool UB3R = false;
	bool unibom3 = false;
	bool Sunibom = false;
	bool Kunibom = false;
	bool unibeem = false;
	/*bool UB3R = true;
	bool unibom3 = true;
	bool Sunibom = true;
	bool Kunibom = true;
	bool unibeem = false;*/
	//Bullet::uepon ue = Bullet::uepon::uniBOM;

	int uec =0;
	int uej = 0;
	int poi = 0;
	int hp = 0;
	int time = 0;

	std::string ueponN(int c)
	{
		switch (c)
		{
		case 0:
			return "uniBOM";
			break;
		case 1:
			return "uniBOM3";
			break;
		case 2:
			return "S_uniBOM";
			break;
		case 3:
			return "K_uniBOM";
			break;
		case 4:
			return "uniBEEM";
			break;
		}
	}
};

