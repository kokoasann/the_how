#include "stdafx.h"
#include "EffectTextureManeger.h"

CShaderResourceView* EffectTextureManeger::Load(const wchar_t* path)
{
	CShaderResourceView* retexture = nullptr;
	auto t = textures.find(path);
	if (t == textures.end())
	{
		retexture = new CShaderResourceView;
		retexture->CreateFromDDSTextureFromFile(path);
		
		textures.insert({ path,retexture});
	}
	else
	{
		retexture = textures[path];
		//retexture = textures.at(path);
	}
	return retexture;
}
void EffectTextureManeger::Release()
{
	for (auto& tex : textures) {
		delete tex.second;
	}
	textures.clear();
}