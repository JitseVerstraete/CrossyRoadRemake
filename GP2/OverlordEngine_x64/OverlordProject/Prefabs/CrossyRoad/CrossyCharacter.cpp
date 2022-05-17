#include "stdafx.h"
#include "CrossyCharacter.h"

#include "Materials/DiffuseMaterial.h"

void CrossyCharacter::Initialize(const SceneContext& )
{
	//spawn the character, visuals... and attach a child with cameraComponent to it
	GameObject* pModelChild = AddChild(new GameObject());


	ModelComponent* modComp = pModelChild->AddComponent(new ModelComponent(L"Meshes/PeasantGirl.ovm"));
	DiffuseMaterial* mat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	mat->SetDiffuseTexture(L"Textures/PeasantGirl_Diffuse.png");
	modComp->SetMaterial(mat);
	pModelChild->GetTransform()->Scale(0.005f);





	/*
	GameObject* pCameraChild = AddChild(new GameObject());
	CameraComponent* camComp = pCameraChild->AddComponent(new CameraComponent());

	camComp->SetFieldOfView(XMConvertToRadians(20.f));
	camComp->SetActive(true);
	const float camDistance{ 20.f };

	XMFLOAT3 eulerRot(50.f, -10.f, 0.f);
	pCameraChild->GetTransform()->Rotate(eulerRot.x, eulerRot.y, eulerRot.z);

	//x = cos(yaw)*cos(pitch)
	//y = sin(yaw)*cos(pitch)
	//z = sin(pitch)
	XMFLOAT3 forward{	sin(XMConvertToRadians(eulerRot.y)) * cos(XMConvertToRadians(eulerRot.x)) ,
						sin(XMConvertToRadians(-eulerRot.x)),
						cos(XMConvertToRadians(eulerRot.y)) * cos(XMConvertToRadians(eulerRot.x))
	};



	pCameraChild->GetTransform()->Translate(-forward.x * camDistance, -forward.y * camDistance, -forward.z * camDistance);

	*/



}

void CrossyCharacter::Update(const SceneContext& sceneContext)
{
	//handle movement using registered keybinds
	if (sceneContext.pInput->IsActionTriggered(MoveForward))
	{
		++m_PosZ;
	}

	if (sceneContext.pInput->IsActionTriggered(MoveBackward))
	{
		--m_PosZ;
	}
	if (sceneContext.pInput->IsActionTriggered(MoveLeft))
	{
		--m_PosX;
	}
	if (sceneContext.pInput->IsActionTriggered(MoveRight))
	{
		++m_PosX;
	}

	GetTransform()->Translate(static_cast<float>(m_PosX), 0.f, static_cast<float>(m_PosZ));
}
