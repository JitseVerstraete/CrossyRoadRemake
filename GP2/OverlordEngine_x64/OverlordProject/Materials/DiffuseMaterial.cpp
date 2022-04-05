#include "stdafx.h"
#include "DiffuseMaterial.h"

DiffuseMaterial::DiffuseMaterial(): Material<DiffuseMaterial>(L"Effects/PosNormTex3D.fx")
{
}

void DiffuseMaterial::SetDiffuseTexture(const std::wstring& path) 
{
	TextureData* texture = ContentManager::Load<TextureData>(path);
	SetVariable_Texture(L"gDiffuseMap", texture);
	m_pDiffuseTexture = texture;
}

void DiffuseMaterial::InitializeEffectVariables()
{
}
