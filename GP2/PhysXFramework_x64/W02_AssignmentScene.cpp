#include "stdafx.h"
#include "W02_AssignmentScene.h"

#include "ContentManager.h"
#include "SoundManager.h"

#include "MeshObject.h"
#include "SpherePosColorNorm.h"
#include "CubePosColorNorm.h"

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
	pPlayerSphereActor->setMass(20.f);

	m_pPlayerSphere->Translate(0.f, 5.f, 0.f);

#pragma endregion PLAYER SPHERE

#pragma region HATCHES
	m_pBlueHatch = new CubePosColorNorm(2.f, 0.1f, 4.f, XMFLOAT4{ Colors::Blue });
	AddGameObject(m_pBlueHatch);

	PxRigidDynamic* pBlueHatchActor = physx.createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pBlueHatchActor, PxBoxGeometry{ 1.f, 0.05f, 2.f }, *pDefaultMaterial);
	m_pBlueHatch->AttachRigidActor(pBlueHatchActor);
	pBlueHatchActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);

	m_pBlueHatch->Translate(-9.f, 17.f, 0.f);



	m_pRedHatch = new CubePosColorNorm(2.f, 0.1f, 4.f, XMFLOAT4{ Colors::Red });
	AddGameObject(m_pRedHatch);

	PxRigidDynamic* pRedHatchActor = physx.createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pRedHatchActor, PxBoxGeometry{ 1.f, 0.05f, 2.f }, *pDefaultMaterial);
	m_pRedHatch->AttachRigidActor(pRedHatchActor);
	pRedHatchActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);


	m_pRedHatch->Translate(9.f, 17.f, 0.f);

#pragma endregion HATCHES

#pragma region SPHERES
	m_pBlueSphere = new SpherePosColorNorm(1.f, 10, 10, XMFLOAT4{ Colors::Blue });
	AddGameObject(m_pBlueSphere);

	PxRigidDynamic* pBlueSphereActor = physx.createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pBlueSphereActor, PxSphereGeometry{ 1.f }, *pDefaultMaterial);
	m_pBlueSphere->AttachRigidActor(pBlueSphereActor);

	m_pBlueSphere->Translate(-5.f, 20.f, 0.f);


	m_pRedSphere = new SpherePosColorNorm(1.f, 10, 10, XMFLOAT4{ Colors::Red });
	AddGameObject(m_pRedSphere);

	PxRigidDynamic* pRedSphereActor = physx.createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pRedSphereActor, PxSphereGeometry{ 1.f }, *pDefaultMaterial);
	m_pRedSphere->AttachRigidActor(pRedSphereActor);

	m_pRedSphere->Translate(5.f, 20.f, 0.f);

#pragma endregion SPHERES

#pragma region BOX
	m_pBlueBox = new CubePosColorNorm(1.5f, 1.5f, 1.5f, XMFLOAT4{ Colors::Blue });
	AddGameObject(m_pBlueBox);

	PxRigidDynamic* pBlueBox = physx.createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pBlueBox, PxBoxGeometry{ 0.75f, 0.75f, 0.75f }, *pDefaultMaterial);
	m_pBlueBox->AttachRigidActor(pBlueBox);
	pBlueBox->setMass(0.5f);

	m_pBlueBox->Translate(-3.f, 5.f, 0.f);



	m_pRedBox = new CubePosColorNorm(1.5f, 1.5f, 1.5f, XMFLOAT4{ Colors::Red });
	AddGameObject(m_pRedBox);

	PxRigidDynamic* pRedBox = physx.createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pRedBox, PxBoxGeometry{ 0.75f, 0.75f, 0.75f }, *pDefaultMaterial);
	m_pRedBox->AttachRigidActor(pRedBox);
	pRedBox->setMass(0.5f);

	m_pRedBox->Translate(3.f, 5.f, 0.f);

#pragma endregion BOX

#pragma region TRIGGERS

	const auto pBlueTriggerActor = physx.createRigidStatic(PxTransform{ PxVec3{-7.5f, 2.f, 0.f} });
	m_pBlueTrigger = PxRigidActorExt::createExclusiveShape(*pBlueTriggerActor, PxBoxGeometry{ 1.f, .4f, 2.5f }, *pDefaultMaterial);

	m_pBlueTrigger->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	m_pBlueTrigger->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

	GetPhysxScene()->addActor(*pBlueTriggerActor);



	const auto pRedTriggerActor = physx.createRigidStatic(PxTransform{ PxVec3{6.5f, 2.f, 0.f} });
	m_pRedTrigger = PxRigidActorExt::createExclusiveShape(*pRedTriggerActor, PxBoxGeometry{ 1.f, .4f, 2.5f }, *pDefaultMaterial);

	m_pRedTrigger->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	m_pRedTrigger->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

	GetPhysxScene()->addActor(*pRedTriggerActor);


#pragma endregion TRIGGERS


#pragma region SOUNDS

	FMOD_RESULT fmodRes{};
	FMOD::System* pFmodSys = SoundManager::GetInstance()->GetSystem();
	fmodRes = pFmodSys->createStream("Resources/Sounds/bell.mp3", FMOD_DEFAULT, nullptr, &m_pBellSound);
	SoundManager::GetInstance()->ErrorCheck(fmodRes);


#pragma endregion SOUNDS
}

void W02_AssignmentScene::Update()
{
	if (GetSceneContext().GetInput()->IsKeyboardKey(InputTriggerState::down, VK_RIGHT))
	{
		m_pPlayerSphere->GetRigidActor()->is<PxRigidDynamic>()->addForce({ 50.f, 0.f, 0.f });
	}

	if (GetSceneContext().GetInput()->IsKeyboardKey(InputTriggerState::down, VK_LEFT))
	{
		m_pPlayerSphere->GetRigidActor()->is<PxRigidDynamic>()->addForce({ -50.f, 0.f, 0.f });
	}

}

void W02_AssignmentScene::Draw() const
{
}

void W02_AssignmentScene::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	for (PxU32 i{}; i < count; i++)
	{
		if (pairs[i].flags & (PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER || PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
			continue;


		const auto& triggerPair = pairs[i];

		PxShape* trigger = static_cast<PxShape*>(triggerPair.triggerShape);
		GameObject* other = static_cast<GameObject*>(triggerPair.otherActor->userData);

		if (triggerPair.status == PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{


			if (trigger == m_pBlueTrigger && other == m_pBlueBox)
			{
				auto pos = m_pBlueHatch->GetPosition();
				m_pBlueHatch->Translate(pos.x - 2.f, pos.y, pos.z);
				SoundManager::GetInstance()->GetSystem()->playSound(m_pBellSound, nullptr, false, nullptr);
			}


			if (trigger == m_pRedTrigger && other == m_pRedBox)
			{
				auto pos = m_pRedHatch->GetPosition();
				m_pRedHatch->Translate(pos.x + 2.f, pos.y, pos.z);
				SoundManager::GetInstance()->GetSystem()->playSound(m_pBellSound, nullptr, false, nullptr);

			}


		}


	}




}
