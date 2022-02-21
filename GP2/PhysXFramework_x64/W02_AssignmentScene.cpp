#include "stdafx.h"
#include "W02_AssignmentScene.h"

#include "ContentManager.h"

#include "MeshObject.h"
#include "SpherePosColorNorm.h"

void W02_AssignmentScene::Initialize()
{
	EnablePhysxDebugRendering(true);
	auto& physx = PxGetPhysics();
	PxMaterial* pDefaultMaterial = physx.createMaterial(0.5f, 0.5f, 0.05f);


#pragma region GROUND PLANE
	//Add Ground Plane
	PxRigidStatic* pGroundActor = PxGetPhysics().createRigidStatic(PxTransform{ PxQuat{XM_PIDIV2, PxVec3{0.f, 0.f, 1.f} } });
	PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{}, *pDefaultMaterial);
	GetPhysxScene()->addActor(*pGroundActor);
#pragma endregion GROUND PLANE

#pragma region STATIC LEVEL
	//Static level
	m_pStaticLevel = new MeshObject(L"Resources/Meshes/Level.ovm");
	AddGameObject(m_pStaticLevel);

	PxTriangleMesh* pLevelMesh = ContentManager::GetInstance()->Load<PxTriangleMesh>(L"Resources/Meshes/Level.ovpt");
	PxRigidStatic* pLevelActor = physx.createRigidStatic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pLevelActor, PxTriangleMeshGeometry{ pLevelMesh }, *pDefaultMaterial);

	m_pStaticLevel->AttachRigidActor(pLevelActor);
#pragma endregion STATIC LEVEL

#pragma region PLAYER SPHERE

	m_pPlayerSphere = new SpherePosColorNorm(1.f, 10, 10, XMFLOAT4{ Colors::Gray });
	AddGameObject(m_pPlayerSphere);

	PxRigidDynamic* pPlayerSphereActor = physx.createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pPlayerSphereActor, PxSphereGeometry{ 1.f }, *pDefaultMaterial);
	m_pPlayerSphere->AttachRigidActor(pPlayerSphereActor);

	m_pPlayerSphere->Translate(0.f, 5.f, 0.f);

#pragma endregion PLAYER SPHERE
}

void W02_AssignmentScene::Update()
{
}

void W02_AssignmentScene::Draw() const
{
}
