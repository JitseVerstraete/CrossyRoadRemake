#include "stdafx.h"
#include "Lily.h"

#include "Materials/Shadow/DiffuseMaterial_Shadow.h"

Lily::Lily()
{
	m_Rotation = MathHelper::randF(0.f, 360.f);
	m_RotationDirection = (rand() % 2 == 0) ? 1 : -1;
}

void Lily::Initialize(const SceneContext&)
{
	ModelComponent* pModel = AddComponent(new ModelComponent(L"Meshes/Lily.ovm", false));
	DiffuseMaterial_Shadow* pMat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pMat->SetDiffuseTexture(L"Textures/Lily.png");
	pModel->SetMaterial(pMat);

	GetTransform()->Scale(0.6f);
}

void Lily::Update(const SceneContext& sceneContext)
{
	m_Rotation += sceneContext.pGameTime->GetElapsed() * m_RotationSpeed * m_RotationDirection;

	GetTransform()->Rotate(0.f, m_Rotation, 0.f);
}
