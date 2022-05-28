#include "stdafx.h"
#include "Tree.h"

#include "Materials/Shadow/DiffuseMaterial_Shadow.h"

void Tree::Initialize(const SceneContext&)
{
	enum class TreeSize
	{
		Small,
		Medium,
		Big
	};

	TreeSize random = static_cast<TreeSize>(rand() % 3);

	ModelComponent* pModel{  };

	switch (random)
	{
	case TreeSize::Small:
		pModel = new ModelComponent(L"Meshes/TreeSmall.ovm");
		break;
	case TreeSize::Medium:
		pModel = new ModelComponent(L"Meshes/TreeMedium.ovm");
		break;
	case TreeSize::Big:
		pModel = new ModelComponent(L"Meshes/TreeBig.ovm");
		break;
	default:
		break;
	}

	AddComponent(pModel);
	DiffuseMaterial_Shadow* pMat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pMat->SetDiffuseTexture(L"Textures/Tree.png");
	pModel->SetMaterial(pMat);

	GetTransform()->Scale(0.2f);
}
