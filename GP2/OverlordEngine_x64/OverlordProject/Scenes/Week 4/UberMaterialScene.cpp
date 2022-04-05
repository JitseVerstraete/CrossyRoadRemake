#include "stdafx.h"
#include "UberMaterialScene.h"
#include "Materials/UberMaterial.h"

void UberMaterialScene::Initialize()
{
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.enableOnGUI = true;

	m_pMaterial = MaterialManager::Get()->CreateMaterial<UberMaterial>();
	//mat->SetDiffuseTexture(L"Textures/Chair_Dark.dds");

	GameObject* m_pChair = AddChild(new GameObject());
	m_pChair->GetTransform()->Scale(10.f);
	auto modelComp = m_pChair->AddComponent(new ModelComponent(L"Meshes/Sphere.ovm"));
	modelComp->SetMaterial(m_pMaterial);


	m_pMaterial->SetDiffuseTexture(L"Textures/Skulls_Diffusemap.tga");
	m_pMaterial->SetUsingDiffuseMap(true);

	m_pMaterial->SetUseBlinn(true);

	m_pMaterial->SetUsingSpecularMap(true);
	m_pMaterial->SetSpecularTexture(L"Textures/Skulls_Heightmap.tga");

	m_pMaterial->SetUseNormalMapping(true);
	m_pMaterial->SetNormalMap(L"Textures/Skulls_Normalmap.tga");

	m_pMaterial->SetUseEnvironmentMapping(false);
	m_pMaterial->SetEnvironmentCubeMap(L"Textures/Sunol_Cubemap.dds");

	m_pMaterial->SetUseOpacityMap(false);
	m_pMaterial->SetOpacityTexture(L"Textures/Specular_Level.tga");



	//SET STARTING IMGUI VARIABLES VALUES

	m_pMaterial->GetVariable(L"gUseTextureDiffuse")->AsScalar()->GetBool(&m_useDiffuseMap);
	m_pMaterial->GetVariable(L"gColorDiffuse")->AsVector()->GetFloatVector(m_diffuseColor);


	m_pMaterial->GetVariable(L"gUseTextureNormal")->AsScalar()->GetBool(&m_UseTextureNormal);
	m_pMaterial->GetVariable(L"gFlipGreenChannel")->AsScalar()->GetBool(&m_FlipGreenChannel);
	m_pMaterial->GetVariable(L"gNormalMapStrength")->AsScalar()->GetFloat(&m_NormalMapStrength);

	m_pMaterial->GetVariable(L"gUseSpecularBlinn")->AsScalar()->GetBool(&m_blinn);
	m_pMaterial->GetVariable(L"gUseSpecularPhong")->AsScalar()->GetBool(&m_phong);
	m_pMaterial->GetVariable(L"gColorSpecular")->AsVector()->GetFloatVector(m_specularColor);
	m_pMaterial->GetVariable(L"gUseTextureNormal")->AsScalar()->GetBool(&m_useSpecularMap);
	m_pMaterial->GetVariable(L"gShininess")->AsScalar()->GetFloat(&m_NormalMapStrength);

	m_pMaterial->GetVariable(L"gColorAmbient")->AsVector()->GetFloatVector(m_ambientColor);
	m_pMaterial->GetVariable(L"gAmbientIntensity")->AsScalar()->GetFloat(&m_ambientStrength);

	m_pMaterial->GetVariable(L"gUseEnvironmentMapping")->AsScalar()->GetBool(&m_useEnvironmentMap);
	m_pMaterial->GetVariable(L"gReflectionStrength")->AsScalar()->GetFloat(&m_reflectionStr);
	m_pMaterial->GetVariable(L"gRefractionStrength")->AsScalar()->GetFloat(&m_refractionStr);
	m_pMaterial->GetVariable(L"gRefractionIndex")->AsScalar()->GetFloat(&m_refractionIndex);

	m_pMaterial->GetVariable(L"gUseFresnelFalloff")->AsScalar()->GetBool(&m_useFresnel);
	m_pMaterial->GetVariable(L"gColorFresnel")->AsVector()->GetFloatVector(m_fresnelColor);
	m_pMaterial->GetVariable(L"gFresnelPower")->AsScalar()->GetFloat(&m_fresnelPower);
	m_pMaterial->GetVariable(L"gFresnelMultiplier")->AsScalar()->GetFloat(&m_fresnelMult);
	m_pMaterial->GetVariable(L"gFresnelHardness")->AsScalar()->GetFloat(&m_fresnelHardness);

	m_pMaterial->GetVariable(L"gOpacityIntensity")->AsScalar()->GetFloat(&m_opacity);
	m_pMaterial->GetVariable(L"gTextureOpacityIntensity")->AsScalar()->GetBool(&m_useOpacityMap);







}

void UberMaterialScene::OnGUI()
{
	ImGui::Begin("Uber shader parameters");

	ImGui::Text("Diffuse");

	if (ImGui::ColorPicker4("Diffuse Color", m_diffuseColor))
		m_pMaterial->SetDiffuseColor(XMFLOAT4(m_diffuseColor));
	if (ImGui::Checkbox("Use Diffuse Map", &m_useDiffuseMap))
		m_pMaterial->SetUsingDiffuseMap(m_useDiffuseMap);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::Text("Normal");
	if (ImGui::Checkbox("Use Normal Map", &m_UseTextureNormal))
		m_pMaterial->SetUseNormalMapping(m_UseTextureNormal);
	if (ImGui::Checkbox("Flip Green Channel", &m_FlipGreenChannel))
		m_pMaterial->SetFlipGreenChannel(m_FlipGreenChannel);
	if (ImGui::SliderFloat("Normal Strenght", &m_NormalMapStrength, 0.f, 1.f, "%0.1f"))
		m_pMaterial->SetNormalMapStrenght(m_NormalMapStrength);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Text("Specular");
	if (ImGui::Checkbox("Specular Blinn", &m_blinn))
		m_pMaterial->SetUseBlinn(m_blinn);
	if (ImGui::Checkbox("Specular Phong", &m_phong))
		m_pMaterial->SetUsePhong(m_phong);
	if (ImGui::ColorPicker4("Specular Color", m_specularColor))
		m_pMaterial->SetSpecularColor(XMFLOAT4(m_specularColor));
	if (ImGui::Checkbox("Use Specular Map", &m_useSpecularMap))
		m_pMaterial->SetUsingSpecularMap(m_useSpecularMap);
	if (ImGui::SliderFloat("Shininess", &m_shininess, 10.f, 100.f, "%1.f"))
		m_pMaterial->SetShininess(m_shininess);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Text("Ambient");
	if (ImGui::ColorPicker4("Ambient Color", m_ambientColor))
		m_pMaterial->SetAmbientColor(XMFLOAT4(m_ambientColor));
	if (ImGui::SliderFloat("Ambient Strength", &m_ambientStrength, 0.f, 1.f, "%.01f"))
		m_pMaterial->SetAmbientIntensity(m_ambientStrength);

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Text("Fresnel");
	if (ImGui::Checkbox("Use Fresnel Falloff", &m_useFresnel))
		m_pMaterial->SetUseFresnelFalloff(m_useFresnel);
	if (ImGui::ColorPicker4("Fresnel Color", m_fresnelColor))
		m_pMaterial->SetFresnelColor(XMFLOAT4(m_fresnelColor));
	if (ImGui::SliderFloat("Fresnel Power", &m_fresnelPower, .5f, 5.f, "%.1f"))
		m_pMaterial->SetFresnelPower(m_fresnelPower);
	if (ImGui::SliderFloat("Fresnel Multiplier", &m_fresnelMult, 0.1f, 2.f, "%.1f"))
		m_pMaterial->SetFresnelMultiplier(m_fresnelMult);
	if (ImGui::SliderFloat("Fresnel Hardness", &m_fresnelHardness, 0.f, 2.f, "%.1f"))
		m_pMaterial->SetFresnelHardness(m_fresnelHardness);




	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Text("Environment");
	if (ImGui::Checkbox("Use Environment Mapping", &m_useEnvironmentMap))
		m_pMaterial->SetUseEnvironmentMapping(m_useEnvironmentMap);
	if (ImGui::SliderFloat("Reflection Strength", &m_reflectionStr, 0.f, 1.f, "%.1f"))
		m_pMaterial->SetReflectionStrength(m_reflectionStr);
	if (ImGui::SliderFloat("Refraction Strength", &m_refractionStr, 0.f, 1.f, "%.1f"))
		m_pMaterial->SetRefractionStrength(m_refractionStr);
	if (ImGui::SliderFloat("Refraction Index", &m_refractionIndex, 0.f, 1.f, "%.1f"))
		m_pMaterial->SetRefractionIndex(m_refractionIndex);


	
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Text("Opacity");
	if (ImGui::SliderFloat("Opacity Amount", &m_opacity, 0.f, 1.f, "%.1f"))
		m_pMaterial->SetOpacityIntensity(m_opacity);
	if (ImGui::Checkbox("Use Opacity Mapping", &m_useOpacityMap))
		m_pMaterial->SetUseOpacityMap(m_useOpacityMap);








		ImGui::End();
}
