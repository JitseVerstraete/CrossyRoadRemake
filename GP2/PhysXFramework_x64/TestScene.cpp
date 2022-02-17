#include "stdafx.h"
#include "TestScene.h"

#include "CubePosColorNorm.h"
#include "SpherePosColorNorm.h"
#include "Logger.h"

void TestScene::Initialize()
{
	EnablePhysxDebugRendering(true);

	//Initialize cube
	pCube = new CubePosColorNorm(2.f, 2.f, 2.f);
	AddGameObject(pCube);

	pCube->RotateDegrees(30.f, 45.f, 0.f);
	pCube->Translate(0.f, 10.f, 0.f);

	//PhysX

	PxMaterial* pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.7f);

	//AddCubeActor
	PxRigidDynamic* pCubeActor = PxGetPhysics().createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pCubeActor, PxBoxGeometry(1.f, 1.f, 1.f), *pDefaultMaterial);

	pCube->AttachRigidActor(pCubeActor);

	//Add Ground Plane
	PxRigidStatic* pGroundActor = PxGetPhysics().createRigidStatic(PxTransform{ PxQuat{XM_PIDIV2, PxVec3{0.f, 0.f, 1.f} } });
	PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{}, *pDefaultMaterial);
	GetPhysxScene()->addActor(*pGroundActor);




	//Sphere
	auto pSphere = new SpherePosColorNorm(1.f, 15.f, 15.f, XMFLOAT4{ Colors::Orange });
	AddGameObject(pSphere);
	pSphere->Translate(0.f, 13.f, 0.f);


	//Add Sphere actor
	auto pSphereActor = PxGetPhysics().createRigidDynamic(PxTransform{ PxIdentity });
	PxRigidActorExt::createExclusiveShape(*pSphereActor, PxSphereGeometry{ 1.f }, *pDefaultMaterial);
	pSphere->AttachRigidActor(pSphereActor);


	//Set Camera
	GetSceneContext().GetCamera()->SetPosition(XMFLOAT3{ 0.f, 10.f, -25.f });
	GetSceneContext().GetCamera()->SetForward(XMFLOAT3{ 0.f, -0.3f, 1.f });

	//Input Actinos
	InputAction actionLeft{ (int)InputIds::MoveLeft, InputTriggerState::released, VK_LEFT, -1, XINPUT_GAMEPAD_DPAD_LEFT };
	GetSceneContext().GetInput()->AddInputAction(actionLeft);

	GetSceneContext().GetInput()->AddInputAction(
		InputAction{ (int)InputIds::MoveRight, InputTriggerState::released, VK_RIGHT, -1, XINPUT_GAMEPAD_DPAD_RIGHT }
	);
}

void TestScene::Update()
{
	float yRotation{ 90.f * GetSceneContext().GetGameTime()->GetTotal() };
	//pCube->RotateDegrees(0.f, yRotation, 0.f);

	if (GetSceneContext().GetInput()->IsActionTriggered((int)InputIds::MoveLeft))
	{
		pCube->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3(-5.f, 0.f, 0.f), PxForceMode::eIMPULSE);

		/*
		XMFLOAT3 currPos = pCube->GetPosition();
		currPos.x -= 2.f * GetSceneContext().GetGameTime()->GetElapsed();
		pCube->Translate(currPos.x, currPos.y, currPos.z);
		*/
	}

	if (GetSceneContext().GetInput()->IsActionTriggered((int)InputIds::MoveRight))
	{
		pCube->GetRigidActor()->is<PxRigidDynamic>()->addForce(PxVec3(5.f, 0.f, 0.f), PxForceMode::eIMPULSE);
		/*
		XMFLOAT3 currPos = pCube->GetPosition();
		currPos.x += 2.f * GetSceneContext().GetGameTime()->GetElapsed();
		pCube->Translate(currPos.x, currPos.y, currPos.z);
		*/
	}

	//addtorque is also a thing next to addforce
}

void TestScene::Draw() const
{

}

void TestScene::OnSceneActivated()
{
	Logger::GetInstance()->LogFormat(LogLevel::Info, L"Scene Activated > \"%ls\"", GetName().c_str());
}

void TestScene::OnSceneDeactivated()
{
}
