#pragma once
class Game;
class Fade;
class point;
class SoundManager;
class END:public IGameObject
{
public:
	END();
	~END();
	void Awake();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc);
	void CoE();

	prefab::CSpriteRender* contenew;
	prefab::CSpriteRender* owali;
	prefab::CSpriteRender* titleGO;
	Game* game = nullptr;
	Fade* fade = nullptr;
	point* p = nullptr;
	SoundManager* soundM = nullptr;
	CVector3 tar = { 0.000001f,0.0f,0.0f }, pos = {300.0f,30.0f,0.0f};
	float radi = 300.0f,angle = 0.0f,tsc1 = 8.0f,tsc2 = 7.5f,tsc3 = 1.0f;
	int count = 0,c = 0,select = 0,ent = 0;
	int score[6] = { 0 };
	bool PAK = true,conORend = true,enter = true,waitFade = false,litleStay = false;
	CFont font;
};

