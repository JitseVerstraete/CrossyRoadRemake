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
	
	m_pBall = AddChild(new SpherePrefab());
	auto ballActor = m_pBall->AddComponent(new RigidBodyComponent());
	ballActor->AddCollider(PxSphereGeometry(1.f), *pDefaultMaterial);
	m_pBall->GetTransform()->Translate(0.f, 2.1f, 0.f);

	m_pLeftPallet = AddChild(new CubePrefab(XMFLOAT3{1.f, 2.f, 5.f}));
	auto palletLeftActor = m_pLeftPallet->AddComponent(new RigidBodyComponent());
	palletLeftActor->AddCollider(PxBoxGeometry(0.5f, 1.f, 2.5f), *pDefaultMaterial);
	palletLeftActor->SetKinematic(true);
	m_pLeftPallet->GetTransform()->Translate(-30.f, 1.f, 0.f);

	m_pRightPallet = AddChild(new CubePrefab(XMFLOAT3{ 1.f, 2.f, 5.f }));
	auto palletRightActor = m_pRightPallet->AddComponent(new RigidBodyComponent());
	palletRightActor->AddCollider(PxBoxGeometry(0.5f, 1.f, 2.5f), *pDefaultMaterial);
	palletRightActor->SetKinematic(true);
	m_pRightPallet->GetTransform()->Translate(30.f, 1.f, 0.f);

	




}

void PongScene::Update()
{
	XMFLOAT3 LeftPalletPos = m_pLeftPallet->GetTransform()->GetPosition();
	XMFLOAT3 RightPalletPos = m_pRightPallet->GetTransform()->GetPosition();

	const float palletSpeed = 10.f;

	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, VK_UP))
	{
		m_pLeftPallet->GetTransform()->Translate(XMFLOAT3{ LeftPalletPos.x , LeftPalletPos.y , LeftPalletPos.z + palletSpeed * GetSceneContext().pGameTime->GetElapsed() });
	}

	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, VK_DOWN))
	{
		m_pLeftPallet->GetTransform()->Translate(XMFLOAT3{ LeftPalletPos.x , LeftPalletPos.y , LeftPalletPos.z - palletSpeed * GetSceneContext().pGameTime->GetElapsed() });
	}


	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, VK_NUMPAD8))
	{
		m_pRightPallet->GetTransform()->Translate(XMFLOAT3{ RightPalletPos.x, RightPalletPos.y , RightPalletPos.z + palletSpeed * GetSceneContext().pGameTime->GetElapsed() });
	}

	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, VK_NUMPAD5))
	{
		m_pRightPallet->GetTransform()->Translate(XMFLOAT3{ RightPalletPos.x, RightPalletPos.y , RightPalletPos.z - palletSpeed * GetSceneContext().pGameTime->GetElapsed() });
	}

}
