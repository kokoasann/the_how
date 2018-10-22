#pragma once
class KeySet:public IGameObject
{
public:
	KeySet();
	~KeySet();
	bool Start();

	float speed = 2.0f;
	tkEngine::EnButton Firing = tkEngine::EnButton::enButtonA;
	tkEngine::EnButton speedUP = tkEngine::EnButton::enButtonRB1;
	tkEngine::EnButton speedDown = tkEngine::EnButton::enButtonLB1;
	tkEngine::EnButton ueponChengeL = tkEngine::EnButton::enButtonX;
	tkEngine::EnButton ueponChengeR = tkEngine::EnButton::enButtonY;

	std::string buttonTOstring(EnButton b) const
	{
		if (b == enButtonA) return "Aボタン";
		if (b == enButtonB) return "Bボタン";
		if (b == enButtonX) return "Xボタン";
		if (b == enButtonY) return "Yボタン";
		if (b == enButtonLB1) return "L1ボタン";
		if (b == enButtonLB2) return "L2ボタン";
		if (b == enButtonLB3) return "L3ボタン";
		if (b == enButtonRB1) return "R1ボタン";
		if (b == enButtonRB2) return "R2ボタン";
		if (b == enButtonRB3) return "R3ボタン";
		if (b == enButtonSelect) return "Selectボタン";
		if (b == enButtonStart) return "Startボタン";
		if (b == enButtonUp) return "上ボタン";
		if (b == enButtonDown) return "下ボタン";
		if (b == enButtonLeft) return "左ボタン";
		if (b == enButtonRight) return "右ボタン";
	}
};

