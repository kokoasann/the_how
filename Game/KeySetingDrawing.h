#pragma once
#include <string.h>
class KeySet;
class Fade;
class SoundManager;
class KeySetingDrawing:public IGameObject
{
public:
	KeySetingDrawing();
	~KeySetingDrawing();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc);
	KeySet* ks = nullptr;
	CFont font;
	Fade* fade;
	SoundManager* soundM = nullptr;
	int c = 0;
	bool seting = false;

	prefab::CSkinModelRender* ball = nullptr;
	prefab::CDirectionLight* light = nullptr;
};

