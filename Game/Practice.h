#pragma once
#include "tkEngine/sound/tkSoundSource.h"
#include "tkEngine/graphics/effect/tkEffect.h"

class Player;
class GameCamera;
class MainObject;
class BulletPR;
class pointPR;
class BackGround;
class MapPlayer;
class EnemyGeneratorPR;
class Fade;
class KeySet;
class SoundManager;
class PracticeConfig;
class PracticeDrawing;
class Practice:public IGameObject
{
public:
	Practice();
	~Practice();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext &rc) override;
	void END();

	CFont font;

	pointPR* p = nullptr;
	PracticeConfig* PC = nullptr;
	PracticeDrawing* PD = nullptr;
	bool Seting = false;

	MainObject* m_mob = nullptr;
	GameCamera* m_camera = nullptr;
	BulletPR* m_bullet = nullptr;
	BulletPR* m_beem = nullptr;
	Fade* fade = nullptr;
	KeySet* ks = nullptr;
	SoundManager* soundM = nullptr;

	prefab::CSpriteRender* Map;
	prefab::CSpriteRender* Aim;
	MapPlayer* mp = nullptr;

	int time = 0;

	int uec = 0;
	int uej = 3;
	bool UB3R = false;
	bool unibom3 = false;
	bool Sunibom = false;
	bool Kunibom = false;
	bool unibeem = false;
};

