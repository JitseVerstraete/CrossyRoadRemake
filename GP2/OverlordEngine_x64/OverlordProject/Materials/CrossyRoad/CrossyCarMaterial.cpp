#include "stdafx.h"
#include "CrossyCarMaterial.h"

CrossyCarMaterial::CrossyCarMaterial(): Material<CrossyCarMaterial>(L"Effects/CrossyRoad/CrossyCar.fx")
{
}

void CrossyCarMaterial::SetDiffuseTexture(const std::wstring& path)
{
	TextureData* texture = ContentManager::Load<TextureData>(path);
	SetVariable_Texture(L"gDiffuseMap", texture);
	m_pDiffuseTexture = texture;
}

void CrossyCarMaterial::SetChassisMap(const std::wstring& path)
{
	TextureData* texture = ContentManager::Load<TextureData>(path);
	SetVariable_Texture(L"gChassisMap", texture);
	m_pDiffuseTexture = texture;
}

void CrossyCarMaterial::SetCustomColor(const XMFLOAT4& color)
{
	SetVariable_Vector(L"gColor", color);
}

void CrossyCarMaterial::InitializeEffectVariables()
{
	
}

void CrossyCarMaterial::OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* ) const
{
	SetVariable_Vector(L"gLightDirection", sceneContext.pLights->GetDirectionalLight().direction);
}

