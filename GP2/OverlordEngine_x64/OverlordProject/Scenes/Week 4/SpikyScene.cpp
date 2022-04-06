#include "stdafx.h"
#include "SpikyScene.h"
#include "Materials/SpikyMaterial.h"

void SpikyScene::Initialize()
{
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.enableOnGUI = true;

	m_pMat = MaterialManager::Get()->CreateMaterial<SpikyMaterial>();
	GameObject* pObject = AddChild(new GameObject());
	pObject->GetTransform()->Scale(20.f);
	ModelComponent* pModel = pObject->AddComponent(new ModelComponent(L"Meshes/OctaSphere.ovm"));
	pModel->SetMaterial(m_pMat);

	m_pMat->GetVariable(L"gColorDiffuse")->AsVector()->GetFloatVector(m_DiffuseColor);
	m_pMat->GetVariable(L"gSpikeLength")->AsScalar()->GetFloat(&m_SpikeStrength);

}

void SpikyScene::OnGUI()
{
	ImGui::Begin("Spiky Material Settings"	);

	if (ImGui::ColorPicker4("Diffuse Color", m_DiffuseColor))
	{
		m_pMat->SetDiffuseColor(XMFLOAT4(m_DiffuseColor));
	}

	if (ImGui::SliderFloat("Spike Length", &m_SpikeStrength, 0.f, 3.f, "%.1f"))
	{
		m_pMat->SetSpikeLength(m_SpikeStrength);
	}


	ImGui::End();
}
