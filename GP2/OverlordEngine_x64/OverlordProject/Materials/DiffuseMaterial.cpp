#include "stdafx.h"
#include "DiffuseMaterial.h"

DiffuseMaterial::DiffuseMaterial(): Material<DiffuseMaterial>(L"Effects/PosNormTex3D.fx")
{
}

void DiffuseMaterial::SetDiffuseTexture(const std::wstring& path) const
{
	TextureData* texture = ContentManager::Load<TextureData>(path);
	SetVariable_Texture(L"gDiffuseMap", texture);
}

void DiffuseMaterial::InitializeEffectVariables()
{
}
