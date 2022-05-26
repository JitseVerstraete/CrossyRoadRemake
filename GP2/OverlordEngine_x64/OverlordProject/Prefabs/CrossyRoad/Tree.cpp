#include "stdafx.h"
#include "Tree.h"

#include "Materials/DiffuseMaterial.h"

void Tree::Initialize(const SceneContext&)
{
	ModelComponent* pModel = AddComponent(new ModelComponent(L"Meshes/Tree.ovm"));
	DiffuseMaterial* pMat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	pMat->SetDiffuseTexture(L"Textures/Tree.png");
	pModel->SetMaterial(pMat);

	GetTransform()->Scale(0.08f);
}
