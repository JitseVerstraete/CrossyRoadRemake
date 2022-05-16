#include "stdafx.h"
#include "CrossyCharacter.h"

#include "Materials/DiffuseMaterial.h"

void CrossyCharacter::Initialize(const SceneContext&)
{
	//spawn the character, visuals... and attach a child with cameraComponent to it
	GameObject* pModelChild = AddChild(new GameObject());


	ModelComponent* modComp = pModelChild->AddComponent(new ModelComponent(L"Meshes/PeasantGirl.ovm"));
	DiffuseMaterial* mat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	mat->SetDiffuseTexture(L"Textures/PeasantGirl_Diffuse.png");
	modComp->SetMaterial(mat);
	pModelChild->GetTransform()->Scale(0.003f);


	const float camDistance{ 200.f };




	GameObject* pCameraChild = AddChild(new GameObject());
	CameraComponent* camComp = pCameraChild->AddComponent(new CameraComponent());
	camComp->SetActive(true);

	XMFLOAT3 eulerRot(60.f, -20.f, 0.f);
	pCameraChild->GetTransform()->Rotate(eulerRot.x, eulerRot.y, eulerRot.z);

	//x = cos(yaw)*cos(pitch)
	//y = sin(yaw)*cos(pitch)
	//z = sin(pitch)
	XMFLOAT3 forward{	sin(XMConvertToRadians(eulerRot.y)) * cos(XMConvertToRadians(eulerRot.x)) ,
						sin(XMConvertToRadians(-eulerRot.x)),
						cos(XMConvertToRadians(eulerRot.y)) * cos(XMConvertToRadians(eulerRot.x))
	};



	pCameraChild->GetTransform()->Translate(-forward.x * camDistance, -forward.y * camDistance, -forward.z * camDistance);




}

void CrossyCharacter::Update(const SceneContext&)
{
	//handle movement using registered keybinds
}
