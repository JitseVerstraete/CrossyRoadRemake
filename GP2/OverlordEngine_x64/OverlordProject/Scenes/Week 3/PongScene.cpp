#include "stdafx.h"
#include "PongScene.h"

#include "Prefabs/SpherePrefab.h"
#include "Prefabs/CubePrefab.h"

void PongScene::Initialize()
{
	GetSceneSettings().clearColor = XMFLOAT4(0.f, 0.f, 0.f, 1.f);
	GetSceneContext().pCamera->GetTransform()->Translate(XMFLOAT3(0.f, 50.f, 0.f));
	static_cast<FreeCamera*>(GetActiveCamera()->GetGameObject())->SetRotation(90.f, 0.f);

	PxMaterial* pFloorMaterial = PxGetPhysics().createMaterial(0.f, 0.f, 0.f);
	PxMaterial* pDefaultMaterial = PxGetPhysics().createMaterial(0.f, 0.f, 1.f);

	GameSceneExt::CreatePhysXGroundPlane(*this, pFloorMaterial);
	
	auto ballObject = AddChild(new SpherePrefab());
	auto ballActor = ballObject->AddComponent(new RigidBodyComponent());
	ballActor->AddCollider(PxSphereGeometry(1.f), *pDefaultMaterial);
	


	auto pallet1Object = AddChild(new CubePrefab(XMFLOAT3{1.f, 2.f, 5.f}));
	auto pallet1Actor = pallet1Object->AddComponent(new RigidBodyComponent());
	pallet1Actor->AddCollider(PxBoxGeometry(0.5f, 1.f, 2.5f), *pDefaultMaterial);
	pallet1Actor->SetKinematic(true);
	pallet1Object->GetTransform()->Translate(-10.f, 1.f, 0.f);

	




}
