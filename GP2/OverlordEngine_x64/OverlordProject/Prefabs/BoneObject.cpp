#include "stdafx.h"
#include "BoneObject.h"

BoneObject::BoneObject(BaseMaterial* pMaterial, float length)
	: m_pMaterial{pMaterial}
	, m_Length{length}
{
}

void BoneObject::AddBone(BoneObject* pBone)
{
	pBone->GetTransform()->Translate(m_Length, 0.f, 0.f);
	AddChild(pBone);
}

void BoneObject::CalculateBindPose()
{
	XMFLOAT4X4 world = GetTransform()->GetWorld();
	XMMATRIX worldMatrix = XMLoadFloat4x4(&world);
	XMMATRIX inverseWorldMatrix =  XMMatrixInverse(nullptr, worldMatrix);
	XMStoreFloat4x4(&m_BindPose, inverseWorldMatrix);

	for (auto& child : GetChildren<BoneObject>())
	{
		child->CalculateBindPose();
	}
}

void BoneObject::Initialize(const SceneContext&)
{
	GetScene()->GetSceneSettings().enableOnGUI = true;

	GameObject* pEmpty = new GameObject();
	AddChild(pEmpty);
	auto modelComp = pEmpty->AddComponent<ModelComponent>(new ModelComponent(L"Meshes/Bone.ovm"));
	modelComp->SetMaterial(m_pMaterial);
	pEmpty->GetTransform()->Rotate(0.f, -90.f, 0.f, true);
	pEmpty->GetTransform()->Scale(m_Length);
}
