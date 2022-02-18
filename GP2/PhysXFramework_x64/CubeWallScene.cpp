#include "stdafx.h"
#include "CubeWallScene.h"

#include "CubePosColorNorm.h"
#include "SpherePosColorNorm.h"

void CubeWallScene::Initialize()
{
	EnablePhysxDebugRendering(true);

	//sphere
	const float sphereRadius{ 2.f };

	//cubes
	const float cubeSize{ 1.f };
	const int cubeWallSize{ 5 };


	//Materials
	PxMaterial* pSphereMaterial = PxGetPhysics().createMaterial(1.f, 1.f, 0.7f);
	PxMaterial* pCubeMaterial = PxGetPhysics().createMaterial(1.f, 1.f, 0.7f);
	PxMaterial* pFloorMaterial = PxGetPhysics().createMaterial(1.f, 1.f, 0.7f);


	//Initialize sphere
	m_pSphere = new SpherePosColorNorm(sphereRadius, 15, 15, XMFLOAT4(Colors::LightYellow));
	AddGameObject(m_pSphere);
	m_pSphere->Translate(0.f, 2.f, 0.f);

	//AddSphereActor
	PxRigidDynamic* pSphereActor = PxGetPhysics().createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pSphereActor, PxSphereGeometry(sphereRadius), *pSphereMaterial);
	m_pSphere->AttachRigidActor(pSphereActor);


	for (int i{}; i < cubeWallSize; i++)
	{
		for (int j{}; j < cubeWallSize; j++)
		{
			//itnitialize cube
			GameObject* temp = new CubePosColorNorm(cubeSize, cubeSize, cubeSize);
			AddGameObject(temp);
			m_pCubes.push_back(temp);
			

			

			PxRigidDynamic* pCubeActor = PxGetPhysics().createRigidDynamic(PxTransform{ PxIdentity });
			PxRigidActorExt::createExclusiveShape(*pCubeActor, PxBoxGeometry(cubeSize /2, cubeSize / 2, cubeSize /2), *pCubeMaterial);
			temp->AttachRigidActor(pCubeActor);
		}
	}




	//Add Ground Plane
	PxRigidStatic* pGroundActor = PxGetPhysics().createRigidStatic(PxTransform{ PxQuat{XM_PIDIV2, PxVec3{0.f, 0.f, 1.f} } });
	PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{}, *pSphereMaterial);
	GetPhysxScene()->addActor(*pGroundActor);

	//Set Camera
	GetSceneContext().GetCamera()->SetPosition(XMFLOAT3{ 0.f, 10.f, -30.f });
	GetSceneContext().GetCamera()->SetForward(XMFLOAT3{ 0.f, -.1f, 1.f });

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

	GetSceneContext().GetInput()->AddInputAction(
		InputAction{ (int)InputIds::Jump, InputTriggerState::pressed, VK_SPACE, -1, XINPUT_GAMEPAD_A }
	);


}

void CubeWallScene::Update()
{

	const float sphereMovementForce{ 10.f };
	const float jumpForce{ 12.f };

	if (GetSceneContext().GetInput()->IsActionTriggered((int)InputIds::MoveLeft))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3(-sphereMovementForce, 0.f, 0.f), PxForceMode::eFORCE);

	}

	if (GetSceneContext().GetInput()->IsActionTriggered((int)InputIds::MoveRight))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3(sphereMovementForce, 0.f, 0.f), PxForceMode::eFORCE);

	}

	if (GetSceneContext().GetInput()->IsActionTriggered((int)InputIds::MoveForward))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3(0.f, 0.f, sphereMovementForce), PxForceMode::eFORCE);

	}

	if (GetSceneContext().GetInput()->IsActionTriggered((int)InputIds::MoveBack))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3(0.f, 0.f, -sphereMovementForce), PxForceMode::eFORCE);

	}


	if (GetSceneContext().GetInput()->IsActionTriggered((int)InputIds::Jump))
	{
		m_pSphere->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3(0.f, jumpForce, 0.f), PxForceMode::eIMPULSE);

	}

}

void CubeWallScene::Draw() const
{
}

void CubeWallScene::OnSceneActivated()
{
}

void CubeWallScene::OnSceneDeactivated()
{
}
