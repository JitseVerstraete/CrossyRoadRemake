#include "stdafx.h"
#include "ComponentTestScene.h"

#include "Prefabs/SpherePrefab.h"

void ComponentTestScene::Initialize()
{
	const auto pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.7f);
	
	GameSceneExt::CreatePhysXGroundPlane(*this, pDefaultMaterial);

	//sphere 1
	auto pSphereObject = AddChild(new SpherePrefab(1.f, 10, XMFLOAT4{Colors::Red}));
	auto pSphereActor = pSphereObject->AddComponent(new RigidBodyComponent());
	pSphereActor->AddCollider(PxSphereGeometry(1.f), *pDefaultMaterial);
	pSphereObject->GetTransform()->Translate(0.f, 40.f, 0.f );

	pSphereActor->SetCollisionGroup(CollisionGroup::Group1);


	//sphere 2
	pSphereObject = AddChild(new SpherePrefab(1.f, 10, XMFLOAT4{ Colors::Blue }));
	pSphereActor = pSphereObject->AddComponent(new RigidBodyComponent());
	pSphereActor->AddCollider(PxSphereGeometry(1.f), *pDefaultMaterial);
	pSphereObject->GetTransform()->Translate(0.f, 30.f, 0.f);

	pSphereActor->SetCollisionIgnoreGroups(CollisionGroup::Group1);

	//sphere 3
	pSphereObject = AddChild(new SpherePrefab(1.f, 10, XMFLOAT4{ Colors::Green }));
	pSphereActor = pSphereObject->AddComponent(new RigidBodyComponent());
	pSphereActor->AddCollider(PxSphereGeometry(1.f), *pDefaultMaterial);
	pSphereObject->GetTransform()->Translate(0.f, 20.f, 0.f);
	
}
