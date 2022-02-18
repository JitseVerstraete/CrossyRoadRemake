#include "stdafx.h"
#include "BouncingBallsScene.h"

#include "SpherePosColorNorm.h"
#include "Logger.h"

void BouncingBallsScene::Initialize()
{
	EnablePhysxDebugRendering(true);

	//PX MATERIALS
	PxMaterial* pBouncyMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 1.f);
	PxMaterial* pHalfBouncyMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, .5f);
	PxMaterial* pNoBouncyMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.f);
	PxMaterial* pGroundPlaneMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.8f);


	//initialize Ball1
	m_pBall1 = new SpherePosColorNorm(1.f, 15, 15, XMFLOAT4(Colors::CadetBlue));
	AddGameObject(m_pBall1);
	m_pBall1->Translate(-5.f, 10.f, 0.f);

	PxRigidDynamic* pBall1Actor = PxGetPhysics().createRigidDynamic(PxTransform(PxIdentity));
	PxRigidActorExt::createExclusiveShape(*pBall1Actor, PxSphereGeometry{ 1.f }, *pBouncyMaterial);
	m_pBall1->AttachRigidActor(pBall1Actor);


	//initialize Ball2
	m_pBall2 = new SpherePosColorNorm(1.f, 15, 15, XMFLOAT4(Colors::CadetBlue));
	AddGameObject(m_pBall2);
	m_pBall2->Translate(0.f, 10.f, 0.f);

	PxRigidDynamic* pBall2Actor = PxGetPhysics().createRigidDynamic(PxTransform(PxIdentity));
	PxRigidActorExt::createExclusiveShape(*pBall2Actor, PxSphereGeometry{ 1.f }, *pHalfBouncyMaterial);
	m_pBall2->AttachRigidActor(pBall2Actor);



	//initialize Ball3
	m_pBall3 = new SpherePosColorNorm(1.f, 15, 15, XMFLOAT4(Colors::CadetBlue));
	AddGameObject(m_pBall3);
	m_pBall3->Translate(5.f, 10.f, 0.f);

	PxRigidDynamic* pBall3Actor = PxGetPhysics().createRigidDynamic(PxTransform(PxIdentity));
	PxRigidActorExt::createExclusiveShape(*pBall3Actor, PxSphereGeometry{ 1.f }, *pNoBouncyMaterial);
	m_pBall3->AttachRigidActor(pBall3Actor);


	//Set Camera
	GetSceneContext().GetCamera()->SetPosition(XMFLOAT3{ 0.f, 10.f, -25.f });
	GetSceneContext().GetCamera()->SetForward(XMFLOAT3{ 0.f, -0.3f, 1.f });
	

	//GroundPlane
	PxRigidStatic* pGroundActor = PxGetPhysics().createRigidStatic(PxTransform{ PxQuat{XM_PIDIV2, PxVec3{0.f, 0.f, 1.f} } });
	PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{}, *pGroundPlaneMaterial);
	GetPhysxScene()->addActor(*pGroundActor);

}

void BouncingBallsScene::Update()
{
}

void BouncingBallsScene::Draw() const
{
}

void BouncingBallsScene::OnSceneActivated()
{
	Logger::GetInstance()->LogFormat(LogLevel::Info, L"Scene Activated > \"%ls\"", GetName().c_str());
}

void BouncingBallsScene::OnSceneDeactivated()
{
}
