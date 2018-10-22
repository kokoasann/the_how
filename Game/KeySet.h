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
		if (b == enButtonA) return "A�{�^��";
		if (b == enButtonB) return "B�{�^��";
		if (b == enButtonX) return "X�{�^��";
		if (b == enButtonY) return "Y�{�^��";
		if (b == enButtonLB1) return "L1�{�^��";
		if (b == enButtonLB2) return "L2�{�^��";
		if (b == enButtonLB3) return "L3�{�^��";
		if (b == enButtonRB1) return "R1�{�^��";
		if (b == enButtonRB2) return "R2�{�^��";
		if (b == enButtonRB3) return "R3�{�^��";
		if (b == enButtonSelect) return "Select�{�^��";
		if (b == enButtonStart) return "Start�{�^��";
		if (b == enButtonUp) return "��{�^��";
		if (b == enButtonDown) return "���{�^��";
		if (b == enButtonLeft) return "���{�^��";
		if (b == enButtonRight) return "�E�{�^��";
	}
};

