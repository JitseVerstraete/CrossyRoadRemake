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

	m_pLeftPallet = AddChild(new CubePrefab(XMFLOAT3{ 1.f, 2.f, 5.f }));
	auto palletLeftActor = m_pLeftPallet->AddComponent(new RigidBodyComponent());
	palletLeftActor->AddCollider(PxBoxGeometry(0.5f, 1.f, 2.5f), *pDefaultMaterial);
	palletLeftActor->SetKinematic(true);
	m_pLeftPallet->GetTransform()->Translate(-30.f, 1.f, 0.f);

	m_pRightPallet = AddChild(new CubePrefab(XMFLOAT3{ 1.f, 2.f, 5.f }));
	auto palletRightActor = m_pRightPallet->AddComponent(new RigidBodyComponent());
	palletRightActor->AddCollider(PxBoxGeometry(0.5f, 1.f, 2.5f), *pDefaultMaterial);
	palletRightActor->SetKinematic(true);
	m_pRightPallet->GetTransform()->Translate(30.f, 1.f, 0.f);

	auto topWall = AddChild(new CubePrefab(XMFLOAT3{ 100.f, 4.f, 2.f }));
	topWall->GetTransform()->Translate(0.f, 0.f, 20.f);
	auto topWallActor = topWall->AddComponent(new RigidBodyComponent(true));
	topWallActor->AddCollider(PxBoxGeometry(50.f, 2.f, 1.f), *pDefaultMaterial);
	topWallActor->IsStatic();

	auto bottomWall = AddChild(new CubePrefab(XMFLOAT3{ 100.f, 4.f, 2.f }));
	bottomWall->GetTransform()->Translate(0.f, 0.f, -20.f);
	auto bottomWallActor = bottomWall->AddComponent(new RigidBodyComponent(true));
	bottomWallActor->AddCollider(PxBoxGeometry(50.f, 2.f, 1.f), *pDefaultMaterial);
	bottomWallActor->IsStatic();

	auto triggerObjectLeft = AddChild(new GameObject());
	triggerObjectLeft->GetTransform()->Translate(-35.f, 0.f, 0.f);
	auto triggerActorLeft = triggerObjectLeft->AddComponent(new RigidBodyComponent(true));
	triggerActorLeft->AddCollider(PxBoxGeometry(1.f, 5.f, 50.f), *pDefaultMaterial, true);

	auto triggerObjectRight = AddChild(new GameObject());
	triggerObjectRight->GetTransform()->Translate(35.f, 0.f, 0.f);
	auto triggerActorRight = triggerObjectRight->AddComponent(new RigidBodyComponent(true));
	triggerActorRight->AddCollider(PxBoxGeometry(1.f, 5.f, 50.f), *pDefaultMaterial, true);


	triggerObjectLeft->SetOnTriggerCallBack([=](GameObject* /*pTrigger*/, GameObject* /*pOther*/, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER)
			{
				std::cout << "Right Player scored!\n";
				m_DoReset = true;
			}
		});

	triggerObjectRight->SetOnTriggerCallBack([=](GameObject* /*pTrigger*/, GameObject* /*pOther*/, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER)
			{
				std::cout << "Left Player scored!\n";
				m_DoReset = true;
			}
		});


	XMFLOAT3 ballDir = CalulateBallVelocity(m_ballVelocity);
	m_pBall->GetComponent<RigidBodyComponent>()->AddForce(ballDir, PxForceMode::eVELOCITY_CHANGE);

}

void PongScene::Update()
{
	XMFLOAT3 LeftPalletPos = m_pLeftPallet->GetTransform()->GetPosition();
	XMFLOAT3 RightPalletPos = m_pRightPallet->GetTransform()->GetPosition();

	const float palletSpeed = 10.f;
	const float clampDistance = 17.f;

	float newLeftPalletPos{LeftPalletPos.z};
	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, VK_UP))
	{
		newLeftPalletPos = LeftPalletPos.z + palletSpeed * GetSceneContext().pGameTime->GetElapsed();
	}

	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, VK_DOWN))
	{
		newLeftPalletPos = LeftPalletPos.z -  palletSpeed * GetSceneContext().pGameTime->GetElapsed();
	}

	//clamp left pallet
	if (newLeftPalletPos < -clampDistance)
	{
		newLeftPalletPos = -clampDistance;
	}
	else if (newLeftPalletPos > clampDistance)
	{
		newLeftPalletPos = clampDistance;
	}

	m_pLeftPallet->GetTransform()->Translate(XMFLOAT3{ LeftPalletPos.x , LeftPalletPos.y , newLeftPalletPos});



	float newRightPalletPos{ RightPalletPos.z };
	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, VK_NUMPAD8))
	{
		newRightPalletPos = RightPalletPos.z + palletSpeed * GetSceneContext().pGameTime->GetElapsed();
	}

	if (GetSceneContext().pInput->IsKeyboardKey(InputState::down, VK_NUMPAD5))
	{
		newRightPalletPos = RightPalletPos.z - palletSpeed * GetSceneContext().pGameTime->GetElapsed();
	}

	//clamp left pallet
	if (newRightPalletPos < -clampDistance)
	{
		newRightPalletPos = -clampDistance;
	}
	else if (newRightPalletPos > clampDistance)
	{
		newRightPalletPos = clampDistance;
	}

	m_pRightPallet->GetTransform()->Translate(XMFLOAT3{ RightPalletPos.x , RightPalletPos.y , newRightPalletPos });


	if (m_DoReset)
	{
		m_pBall->GetTransform()->Translate(0.f, 2.1f, 0.f);
		m_pBall->GetComponent<RigidBodyComponent>()->AddForce(CalulateBallVelocity(m_ballVelocity), PxForceMode::eVELOCITY_CHANGE);
		m_DoReset = false;
	}

}

void PongScene::Reset()
{
	m_DoReset = true;
}

XMFLOAT3 PongScene::CalulateBallVelocity(float velocity)
{
	srand(unsigned int(time(NULL)));

	XMFLOAT3 ballDir = { 0.f, 0.f , 0.f };
	ballDir.x = rand() % 2 == 0 ? float((rand() % 90 + 10) / 100.f) : -float((rand() % 90 + 10) / 100.f);
	ballDir.z = rand() % 2 == 0 ? float((rand() % 90 + 10) / 100.f) : -float((rand() % 90 + 10) / 100.f);


	XMVECTOR temp = XMLoadFloat3(&ballDir);
	temp = XMVector3Normalize(temp);
	temp *= velocity;
	XMStoreFloat3(&ballDir, temp);

	return ballDir;

}



