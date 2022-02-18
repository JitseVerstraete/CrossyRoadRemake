#include "stdafx.h"
#include "FrictionTestScene.h"

#include "CubePosColorNorm.h"
#include "Logger.h"

void FrictionTestScene::Initialize()
{
	EnablePhysxDebugRendering(true);

	//PX MATERIALS
	PxMaterial* pNoFrictionMaterial = PxGetPhysics().createMaterial(0.f, 0.f, 0.f);
	PxMaterial* pHalfFrictionMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.f);
	PxMaterial* pFullFrictionMaterial = PxGetPhysics().createMaterial(1.f, 1.f, 0.f);



	//initialize Cube1
	m_pCube1 = new CubePosColorNorm(1.f, 1.f, 1.f);
	AddGameObject(m_pCube1);
	m_pCube1->Translate(-10.f, 6.f, 0.f);
	m_pCube1->RotateDegrees(0.f, 0.f, -30.f);

	PxRigidDynamic* pCube1Actor = PxGetPhysics().createRigidDynamic(PxTransform(PxIdentity));
	PxRigidActorExt::createExclusiveShape(*pCube1Actor, PxBoxGeometry{0.5f, 0.5f, 0.5f }, * pNoFrictionMaterial);
	m_pCube1->AttachRigidActor(pCube1Actor);


	//initialize Cube1
	m_pCube2 = new CubePosColorNorm(1.f, 1.f, 1.f);
	AddGameObject(m_pCube2);
	m_pCube2->Translate(0.f, 6.f, 0.f);
	m_pCube2->RotateDegrees(0.f, 0.f, -30.f);

	PxRigidDynamic* pCube2Actor = PxGetPhysics().createRigidDynamic(PxTransform(PxIdentity));
	PxRigidActorExt::createExclusiveShape(*pCube2Actor, PxBoxGeometry{ 0.5f, 0.5f, 0.5f }, *pHalfFrictionMaterial);
	m_pCube2->AttachRigidActor(pCube2Actor);



	//initialize Cube3
	m_pCube3 = new CubePosColorNorm(1.f, 1.f, 1.f);
	AddGameObject(m_pCube3);
	m_pCube3->Translate(10.f, 6.f, 0.f);
	m_pCube3->RotateDegrees(0.f, 0.f, -30.f);

	PxRigidDynamic* pCube3Actor = PxGetPhysics().createRigidDynamic(PxTransform(PxIdentity));
	PxRigidActorExt::createExclusiveShape(*pCube3Actor, PxBoxGeometry{ 0.5f, 0.5f, 0.5f }, *pFullFrictionMaterial);
	m_pCube3->AttachRigidActor(pCube3Actor);


	//initialize Floor1
	m_pFloor1 = new CubePosColorNorm(3.f, 1.f, 2.f);
	AddGameObject(m_pFloor1);
	m_pFloor1->Translate(-10.f, 4.f, 0.f);
	m_pFloor1->RotateDegrees(0.f, 0.f, -30.f);

	PxRigidStatic* pFloor1Actor = PxGetPhysics().createRigidStatic(PxTransform(PxIdentity));
	PxRigidActorExt::createExclusiveShape(*pFloor1Actor, PxBoxGeometry{ 1.5f, 0.5f, 1.f }, *pNoFrictionMaterial);
	m_pFloor1->AttachRigidActor(pFloor1Actor);


	//initialize Floor2
	m_pFloor2 = new CubePosColorNorm(3.f, 1.f, 2.f);
	AddGameObject(m_pFloor2);
	m_pFloor2->Translate(0.f, 4.f, 0.f);
	m_pFloor2->RotateDegrees(0.f, 0.f, -30.f);

	PxRigidStatic* pFloor2Actor = PxGetPhysics().createRigidStatic(PxTransform(PxIdentity));
	PxRigidActorExt::createExclusiveShape(*pFloor2Actor, PxBoxGeometry{ 1.5f, 0.5f, 1.f }, *pNoFrictionMaterial);
	m_pFloor2->AttachRigidActor(pFloor2Actor);


	//initialize Floor3
	m_pFloor3 = new CubePosColorNorm(3.f, 1.f, 2.f);
	AddGameObject(m_pFloor3);
	m_pFloor3->Translate(10.f, 4.f, 0.f);
	m_pFloor3->RotateDegrees(0.f, 0.f, -30.f);

	PxRigidStatic* pFloor3Actor = PxGetPhysics().createRigidStatic(PxTransform(PxIdentity));
	PxRigidActorExt::createExclusiveShape(*pFloor3Actor, PxBoxGeometry{ 1.5f, 0.5f, 1.f }, *pNoFrictionMaterial);
	m_pFloor3->AttachRigidActor(pFloor3Actor);


	//Set Camera
	GetSceneContext().GetCamera()->SetPosition(XMFLOAT3{ 0.f, 10.f, -25.f });
	GetSceneContext().GetCamera()->SetForward(XMFLOAT3{ 0.f, -0.3f, 1.f });
	

	//GroundPlane
	PxRigidStatic* pGroundActor = PxGetPhysics().createRigidStatic(PxTransform{ PxQuat{XM_PIDIV2, PxVec3{0.f, 0.f, 1.f} } });
	PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{}, *pNoFrictionMaterial);
	GetPhysxScene()->addActor(*pGroundActor);

}

void FrictionTestScene::Update()
{
}

void FrictionTestScene::Draw() const
{
}

void FrictionTestScene::OnSceneActivated()
{
	Logger::GetInstance()->LogFormat(LogLevel::Info, L"Scene Activated > \"%ls\"", GetName().c_str());
}

void FrictionTestScene::OnSceneDeactivated()
{
}
