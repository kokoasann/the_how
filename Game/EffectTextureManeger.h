#pragma once
class EffectTextureManeger:public IGameObject
{
public:
	CShaderResourceView* Load(const wchar_t* path);
	void Release();
	std::map<std::wstring,CShaderResourceView*> textures;
};

