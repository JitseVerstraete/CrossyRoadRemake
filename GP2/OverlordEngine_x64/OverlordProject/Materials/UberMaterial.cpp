#include "stdafx.h"
#include "UberMaterial.h"

UberMaterial::UberMaterial(): Material<UberMaterial>(L"Effects/UberShader.fx")
{
}

void UberMaterial::InitializeEffectVariables()
{
	//diffuse
	SetDiffuseColor({ 1.f, 1.f, 1.f, 1.f });
	SetUsingDiffuseMap(false);
	
	//normal map
	SetFlipGreenChannel(true);
	SetUseNormalMapping(false);
	SetNormalMapStrenght(1.f);

	//specular
	SetSpecularColor({ 1.f, 1.f, 1.f, 1.f });
	SetUsingSpecularMap(false);
	SetShininess(15.f);
	SetUseBlinn(false);
	SetUsePhong(false);

	//ambient
	SetAmbientColor({ 0.1f, 0.1f, 0.1f, 1.f });
	SetAmbientIntensity(0.05f);

	//envirnoment
	SetUseEnvironmentMapping(false);
	SetReflectionStrength(0.f);
	SetRefractionStrength(0.f);
	SetRefractionIndex(0.3f);

	//fresnel
	SetUseFresnelFalloff(false);
	SetFresnelColor({ 1.f, 1.f, 1.f, 1.f });
	SetFresnelPower(2.f);
	SetFresnelMultiplier(1.f);
	SetFresnelHardness(1.f);

	//opacity
	SetOpacityIntensity(1.f);
	SetUseOpacityMap(false);
}

void UberMaterial::SetDiffuseColor(const XMFLOAT4& color)
{
	SetVariable_Vector(L"gColorDiffuse", color);
}

void UberMaterial::SetUsingDiffuseMap(bool useDiffMap)
{
	SetVariable_Scalar(L"gUseTextureDiffuse", useDiffMap);
}

void UberMaterial::SetDiffuseTexture(const std::wstring& path)
{	
	TextureData* texture = ContentManager::Load<TextureData>(path);
	SetVariable_Texture(L"gTextureDiffuse", texture);
	m_pDiffuseTexture = texture;
}

void UberMaterial::SetFlipGreenChannel(bool flipGreen)
{
	SetVariable_Scalar(L"gFlipGreenChannel", flipGreen);
}

void UberMaterial::SetUseNormalMapping(bool useNormalMap)
{
	SetVariable_Scalar(L"gUseTextureNormal", useNormalMap);
}

void UberMaterial::SetNormalMapStrenght(float strength)
{
	SetVariable_Scalar(L"gNormalMapStrength", strength);
}

void UberMaterial::SetNormalMap(const std::wstring& path)
{
	TextureData* texture = ContentManager::Load<TextureData>(path);
	SetVariable_Texture(L"gTextureNormal", texture);
	m_pNormalTexture = texture;
}

void UberMaterial::SetSpecularColor(const XMFLOAT4& color)
{
	SetVariable_Vector(L"gColorSpecular", color);
}

void UberMaterial::SetUsingSpecularMap(bool useSpecMap)
{
	SetVariable_Scalar(L"gUseTextureSpecularIntensity", useSpecMap);
}

void UberMaterial::SetShininess(float shininess)
{
	SetVariable_Scalar(L"gShininess", shininess);
}

void UberMaterial::SetSpecularTexture(const std::wstring& path)
{
	TextureData* texture = ContentManager::Load<TextureData>(path);
	SetVariable_Texture(L"gTextureSpecularIntensity", texture);
	m_pSpecularTexture = texture;
}

void UberMaterial::SetUseBlinn(bool blinn)
{
	SetVariable_Scalar(L"gUseSpecularBlinn", blinn);
}

void UberMaterial::SetUsePhong(bool phong)
{
	SetVariable_Scalar(L"gUseSpecularPhong", phong);
}

void UberMaterial::SetAmbientColor(const XMFLOAT4& color)
{
	SetVariable_Vector(L"gColorAmbient", color);
}

void UberMaterial::SetAmbientIntensity(float intensity)
{
	SetVariable_Scalar(L"gAmbientIntensity", intensity);
}

void UberMaterial::SetUseEnvironmentMapping(bool useEnvMap)
{
	SetVariable_Scalar(L"gUseEnvironmentMapping", useEnvMap);
}

void UberMaterial::SetReflectionStrength(float reflection)
{
	SetVariable_Scalar(L"gReflectionStrength", reflection);
}

void UberMaterial::SetRefractionStrength(float refraction)
{
	SetVariable_Scalar(L"gRefractionStrength", refraction);

}

void UberMaterial::SetRefractionIndex(float refractionIndex)
{
	SetVariable_Scalar(L"gRefractionIndex", refractionIndex);
}

void UberMaterial::SetEnvironmentCubeMap(const std::wstring& path)
{
	TextureData* texture = ContentManager::Load<TextureData>(path);
	SetVariable_Texture(L"gCubeEnvironment", texture);
	m_pEnvironmentCube = texture;
}

void UberMaterial::SetUseFresnelFalloff(bool useFresnel)
{
	SetVariable_Scalar(L"gUseFresnelFalloff", useFresnel);
}

void UberMaterial::SetFresnelColor(const XMFLOAT4& color)
{
	SetVariable_Vector(L"gColorFresnel", color);
}

void UberMaterial::SetFresnelPower(float power)
{
	SetVariable_Scalar(L"gFresnelPower", power);
}

void UberMaterial::SetFresnelMultiplier(float multiplier)
{
	SetVariable_Scalar(L"gFresnelMultiplier", multiplier);
}

void UberMaterial::SetFresnelHardness(float hardness)
{
	SetVariable_Scalar(L"gFresnelHardness", hardness);
}

void UberMaterial::SetOpacityIntensity(float intensity)
{
	SetVariable_Scalar(L"gOpacityIntensity", intensity);
}

void UberMaterial::SetUseOpacityMap(bool useOpacityMap)
{
	SetVariable_Scalar(L"gTextureOpacityIntensity", useOpacityMap);
}

void UberMaterial::SetOpacityTexture(const std::wstring& path)
{
	TextureData* texture = ContentManager::Load<TextureData>(path);
	SetVariable_Texture(L"gTextureOpacity", texture);
	m_pOpacityTexture = texture;

}
