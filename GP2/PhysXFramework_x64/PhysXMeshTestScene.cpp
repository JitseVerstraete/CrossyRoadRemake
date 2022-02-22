#include "stdafx.h"
#include "PhysXMeshTestScene.h"

#include "MeshObject.h"
#include "MeshObjectTex.h"
#include "ContentManager.h"
#include "SpherePosColorNorm.h"



void PhysXMeshTestScene::Initialize()
{
	EnablePhysxDebugRendering(true);

	auto& physx = PxGetPhysics();
	PxMaterial* pDefaultMaterial = physx.createMaterial(0.5f, 0.5f, 0.5f);

	//Add Ground Plane
	PxRigidStatic* pGroundActor = PxGetPhysics().createRigidStatic(PxTransform{ PxQuat{XM_PIDIV2, PxVec3{0.f, 0.f, 1.f} } });
	PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{}, *pDefaultMaterial);
	GetPhysxScene()->addActor(*pGroundActor);



	/*

	//convex mesh
	m_pChairConvex = new MeshObjectTex(L"Resources/Meshes/Chair.ovm", L"Resources/Textures/Chair_Dark.dds");
	AddGameObject(m_pChairConvex);

	PxConvexMesh* pConvexMesh = ContentManager::GetInstance()->Load<PxConvexMesh>(L"Resources/Meshes/Chair.ovpc");
	const auto pConvexActor = physx.createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pConvexActor, PxConvexMeshGeometry{ pConvexMesh }, *pDefaultMaterial);
	m_pChairConvex->AttachRigidActor(pConvexActor);
	m_pChairConvex->Translate(0.f, 10.f, 0.f);

	PxRigidBodyExt::setMassAndUpdateInertia(*pConvexActor, 0.5f);


	//triangle mesh
	m_pChairTriangle = new MeshObjectTex(L"Resources/Meshes/Chair.ovm", L"Resources/Textures/Chair_Dark.dds");
	AddGameObject(m_pChairTriangle);
	PxTriangleMesh* pTriangleMesh = ContentManager::GetInstance()->Load<PxTriangleMesh>(L"Resources/Meshes/Chair.ovpt");

	const auto pTriangleActor = physx.createRigidDynamic(PxTransform{ PxIdentity });
	pTriangleActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);


	PxRigidActorExt::createExclusiveShape(*pTriangleActor, PxTriangleMeshGeometry{ pTriangleMesh }, *pDefaultMaterial);
	m_pChairTriangle->AttachRigidActor(pTriangleActor);
	m_pChairTriangle->Translate(0.f, 0.f, 0.f);
	*/

	m_pSphere = new SpherePosColorNorm(1.f, 10, 10, XMFLOAT4{ Colors::Blue });
	auto pSphereActor = physx.createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pSphereActor, PxSphereGeometry{ 1.f }, *pDefaultMaterial);

	m_pSphere->AttachRigidActor(pSphereActor);
	AddGameObject(m_pSphere);

	m_pSphere->Translate(0.f, 1.f, 0.f);


	//TRIGGER	
	const auto pTriggerActor = physx.createRigidStatic(PxTransform{ PxVec3{-4.f, 1.f, 0.f} });
	PxShape* pTriggerShape = PxRigidActorExt::createExclusiveShape(*pTriggerActor, PxBoxGeometry{ 1.f, 1.f, 1.f }, *pDefaultMaterial);

	pTriggerShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	pTriggerShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

	GetPhysxScene()->addActor(*pTriggerActor);

}

void PhysXMeshTestScene::Update()
{
	/*
	auto currPos = m_pChairTriangle->GetPosition();
	if (m_SceneContext.GetInput()->IsKeyboardKey(InputTriggerState::down, VK_DOWN))
		currPos.z -= 5.f * m_SceneContext.GetGameTime()->GetElapsed();

	if (m_SceneContext.GetInput()->IsKeyboardKey(InputTriggerState::down, VK_UP))
		currPos.z += 5.f * m_SceneContext.GetGameTime()->GetElapsed();

	if (m_SceneContext.GetInput()->IsKeyboardKey(InputTriggerState::down, VK_RIGHT))
		currPos.x += 5.f * m_SceneContext.GetGameTime()->GetElapsed();

	if (m_SceneContext.GetInput()->IsKeyboardKey(InputTriggerState::down, VK_LEFT))
		currPos.x -= 5.f * m_SceneContext.GetGameTime()->GetElapsed();

	m_pChairTriangle->Translate(currPos.x, currPos.y, currPos.z);
	*/

	if (m_SceneContext.GetInput()->IsKeyboardKey(InputTriggerState::down, VK_DOWN))
	{

	}

	if (m_SceneContext.GetInput()->IsKeyboardKey(InputTriggerState::down, VK_UP))

	{

	}

	if (m_SceneContext.GetInput()->IsKeyboardKey(InputTriggerState::down, VK_LEFT))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addTorque(PxVec3{ 0.f, 0.f, 10.f });

	}

	if (m_SceneContext.GetInput()->IsKeyboardKey(InputTriggerState::down, VK_RIGHT))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addTorque(PxVec3{ 0.f, 0.f, -10.f });

	}

}

void PhysXMeshTestScene::Draw() const
{
}

void PhysXMeshTestScene::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	for (PxU32 i{}; i < count; i++)
	{
		//ignore removed shapes
		if (pairs[i].flags & (PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER || PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
			continue;


		//process the trigger pair
		const auto& triggerPair = pairs[i];

		//get data about what actor entered the trigger
		auto pUserData = static_cast<GameObject*>(triggerPair.otherActor->userData);

		

		if (triggerPair.status == PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			Logger::GetInstance()->LogInfo(L"Something entered a trigger");
		}
		else if (triggerPair.status == PxPairFlag::eNOTIFY_TOUCH_LOST)
		{
			Logger::GetInstance()->LogInfo(L"Something left a trigger");
		}
	}
}

