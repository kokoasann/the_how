#pragma once
class Fade;
class SoundManager;
class ModeSelect:public IGameObject
{
public:
	ModeSelect();
	~ModeSelect();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void PostRender(CRenderContext& rc);
	void SetSprite();

	void m_start();
	void m_difficulty();
	void m_practis();
	void m_collection();
	void m_keySeting();

	bool Waitfade = false;
	int c = 0;
	Fade* fade = nullptr;
	SoundManager* soundM = nullptr;

	enum select
	{
		start,
		difficulty,
		practis,
		collection,
		keySeting
	};
	const select Getsel(int c)
	{
		switch (c)
		{
		case 0:
			return start;
			break;
		case 1:
			return difficulty;
			break;
		case 2:
			return practis;
			break;
		case 3:
			return collection;
			break;
		case 4:
			return keySeting;
			break;
		}
	}
	select sel = start;

	prefab::CSpriteRender* s_start = nullptr;
	prefab::CSpriteRender* s_difficulty = nullptr;
	prefab::CSpriteRender* s_practis = nullptr;
	prefab::CSpriteRender* s_collection = nullptr;
	prefab::CSpriteRender* s_keySeting = nullptr;

	prefab::CSkinModelRender* ball = nullptr;

	prefab::CDirectionLight* light = nullptr;
};

