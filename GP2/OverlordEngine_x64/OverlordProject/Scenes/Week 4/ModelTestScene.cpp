#include "stdafx.h"
#include "ModelTestScene.h"
#include "Materials/DiffuseMaterial.h"

void ModelTestScene::Initialize()
{
	PxMaterial* pDefaultlMat = PxGetPhysics().createMaterial(0.3f, 0.3f, 0.8f);
	GameSceneExt::CreatePhysXGroundPlane(*this , pDefaultlMat);

	DiffuseMaterial* mat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	mat->SetDiffuseTexture(L"Textures/Chair_Dark.dds");

	GameObject* m_pChair = AddChild(new GameObject());
	RigidBodyComponent* pRigi = m_pChair->AddComponent(new RigidBodyComponent());
	PxConvexMesh* convexMesh = ContentManager::Load<PxConvexMesh>(L"Meshes/Chair.ovpc");
	pRigi->AddCollider(PxConvexMeshGeometry(convexMesh), *pDefaultlMat);
	m_pChair->GetTransform()->Translate(0.f, 5.f, 0.f);

	auto modelComp = m_pChair->AddComponent(new ModelComponent(L"Meshes/Chair.ovm"));
	modelComp->SetMaterial(mat);



}
