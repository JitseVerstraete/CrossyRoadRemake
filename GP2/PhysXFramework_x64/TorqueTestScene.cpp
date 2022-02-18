#include "stdafx.h"
#include "TorqueTestScene.h"

#include "CubePosColorNorm.h"

void TorqueTestScene::Initialize()
{
	EnablePhysxDebugRendering(true);

	//Initialize cube
	m_pCube = new CubePosColorNorm(2.f, 2.f, 2.f);
	AddGameObject(m_pCube);
	m_pCube->Translate(0.f, 2.f, 0.f);



	PxMaterial* pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);

	//AddCubeActor
	PxRigidDynamic* pCubeActor = PxGetPhysics().createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pCubeActor, PxBoxGeometry(1.f, 1.f, 1.f), *pDefaultMaterial);

	m_pCube->AttachRigidActor(pCubeActor);

	//Add Ground Plane
	PxRigidStatic* pGroundActor = PxGetPhysics().createRigidStatic(PxTransform{ PxQuat{XM_PIDIV2, PxVec3{0.f, 0.f, 1.f} } });
	PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{}, *pDefaultMaterial);
	GetPhysxScene()->addActor(*pGroundActor);

	//Set Camera
	GetSceneContext().GetCamera()->SetPosition(XMFLOAT3{ 0.f, 30.f, -10.f });
	GetSceneContext().GetCamera()->SetForward(XMFLOAT3{ 0.f, -1.f, 0.3f });

	//Input Actinos
	GetSceneContext().GetInput()->AddInputAction(
		InputAction{ (int)InputIds::MoveLeft, InputTriggerState::down, VK_LEFT, -1, XINPUT_GAMEPAD_DPAD_LEFT }
	);

	GetSceneContext().GetInput()->AddInputAction(
		InputAction{ (int)InputIds::MoveRight, InputTriggerState::down, VK_RIGHT, -1, XINPUT_GAMEPAD_DPAD_RIGHT }
	);

	GetSceneContext().GetInput()->AddInputAction(
		InputAction{ (int)InputIds::MoveForward, InputTriggerState::down, VK_UP, -1, XINPUT_GAMEPAD_DPAD_UP }
	);

	GetSceneContext().GetInput()->AddInputAction(
		InputAction{ (int)InputIds::MoveBack, InputTriggerState::down, VK_DOWN, -1, XINPUT_GAMEPAD_DPAD_DOWN }
	);
}

void TorqueTestScene::Update()
{
	if (GetSceneContext().GetInput()->IsActionTriggered((int)InputIds::MoveLeft))
	{
		m_pCube->GetRigidActor()->is<PxRigidDynamic>()->addTorque(PxVec3(0.f, 0.f, 5.f), PxForceMode::eFORCE);

	}

	if (GetSceneContext().GetInput()->IsActionTriggered((int)InputIds::MoveRight))
	{
		m_pCube->GetRigidActor()->is<PxRigidDynamic>()->addTorque(PxVec3(0.f, 0.f, -5.f), PxForceMode::eFORCE);

	}

	if (GetSceneContext().GetInput()->IsActionTriggered((int)InputIds::MoveForward))
	{
		m_pCube->GetRigidActor()->is<PxRigidDynamic>()->addTorque(PxVec3(5.f, 0.f, 0.f), PxForceMode::eFORCE);

	}

	if (GetSceneContext().GetInput()->IsActionTriggered((int)InputIds::MoveBack))
	{
		m_pCube->GetRigidActor()->is<PxRigidDynamic>()->addTorque(PxVec3(-5.f, 0.f, 0.f), PxForceMode::eFORCE);

	}
}

void TorqueTestScene::Draw() const
{
}

void TorqueTestScene::OnSceneActivated()
{
}

void TorqueTestScene::OnSceneDeactivated()
{
}