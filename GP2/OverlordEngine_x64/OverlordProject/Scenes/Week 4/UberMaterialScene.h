#pragma once
#include "C:\DAE_Local\GraphicsProgramming2\GP2\OverlordEngine_x64\OverlordEngine\Scenegraph\GameScene.h"
class UberMaterial;
class UberMaterialScene : public GameScene
{
public:
	UberMaterialScene() :GameScene(L"UberMaterialScene") {}
	~UberMaterialScene() override = default;

	UberMaterialScene(const UberMaterialScene& other) = delete;
	UberMaterialScene(UberMaterialScene&& other) noexcept = delete;
	UberMaterialScene& operator=(const UberMaterialScene& other) = delete;
	UberMaterialScene& operator=(UberMaterialScene&& other) noexcept = delete;
private:

	void Initialize() override;
	void OnGUI() override;


	UberMaterial* m_pMaterial{};

	//diffuse vars
	float m_diffuseColor[4]{};
	bool m_useDiffuseMap{};

	//normal
	bool m_UseTextureNormal{};
	bool m_FlipGreenChannel{};
	float m_NormalMapStrength{};

	//specular
	bool m_blinn{};
	bool m_phong{};
	float m_specularColor[4]{};
	bool m_useSpecularMap{};
	float m_shininess{};

	//ambient
	float m_ambientColor[4]{};
	float m_ambientStrength{};
		

	//environment
	bool m_useEnvironmentMap{};
	float m_reflectionStr{};
	float m_refractionStr{};
	float m_refractionIndex{};

	//fresnel
	bool m_useFresnel{};
	float m_fresnelColor[4]{};
	float m_fresnelPower{};
	float m_fresnelMult{};
	float m_fresnelHardness{};

	//opacity
	float m_opacity{};
	bool m_useOpacityMap{};
};
