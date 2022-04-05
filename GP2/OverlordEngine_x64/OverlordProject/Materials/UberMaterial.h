#pragma once
#include "C:\DAE_Local\GraphicsProgramming2\GP2\OverlordEngine_x64\OverlordEngine\Misc\Material.h"
class UberMaterial : public Material<UberMaterial>
{
public:
	UberMaterial();
	~UberMaterial() override = default;

	UberMaterial(const UberMaterial& other) = delete;
	UberMaterial(UberMaterial&& other) noexcept = delete;
	UberMaterial& operator=(const UberMaterial& other) = delete;
	UberMaterial& operator=(UberMaterial&& other) noexcept = delete;

	//SHADER VARIABLES SETTERS

	//diffuse
	void SetDiffuseColor(const XMFLOAT4& color);
	void SetUsingDiffuseMap(bool useDiffMap);
	void SetDiffuseTexture(const std::wstring & path);

	//normal mapping
	void SetFlipGreenChannel(bool flipGreen);
	void SetUseNormalMapping(bool useNormalMap);
	void SetNormalMapStrenght(float strenght);
	void SetNormalMap(const std::wstring& path);

	//specular
	void SetSpecularColor(const XMFLOAT4& color);
	void SetUsingSpecularMap(bool useSpecMap);
	void SetShininess(float shininess);
	void SetSpecularTexture(const std::wstring& path);
	void SetUseBlinn(bool blinn);
	void SetUsePhong(bool phong);
	
	//ambient
	void SetAmbientColor(const XMFLOAT4& color);
	void SetAmbientIntensity(float intensity);


	//environment
	void SetUseEnvironmentMapping(bool useEnvMap);
	void SetReflectionStrength(float reflection);
	void SetRefractionStrength(float refraction);
	void SetRefractionIndex(float refractionIndex);
	void SetEnvironmentCubeMap(const std::wstring& path);


	//fresnel
	void SetUseFresnelFalloff(bool useFresnel);
	void SetFresnelColor(const XMFLOAT4& color);
	void SetFresnelPower(float power);
	void SetFresnelMultiplier(float multiplier);
	void SetFresnelHardness(float hardness);

	//opacity
	void SetOpacityIntensity(float intensity);
	void SetUseOpacityMap(bool useOpacityMap);
	void SetOpacityTexture(const std::wstring& path);


protected:
	void InitializeEffectVariables() override;

private:
	TextureData* m_pDiffuseTexture{};
	TextureData* m_pSpecularTexture{};
	TextureData* m_pOpacityTexture{};
	TextureData* m_pNormalTexture{};
	TextureData* m_pEnvironmentCube{};

};

