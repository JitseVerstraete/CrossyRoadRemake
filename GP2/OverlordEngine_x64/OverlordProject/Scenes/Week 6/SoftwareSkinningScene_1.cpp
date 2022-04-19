#include "stdafx.h"
#include "SoftwareSkinningScene_1.h"

#include "Materials/ColorMaterial.h"
#include "Prefabs/BoneObject.h"

void SoftwareSkinningScene_1::Initialize()
{
	ColorMaterial* pMat = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	GameObject* pRoot = new GameObject();

	m_pBone0 = new BoneObject(pMat, 15.f);
	pRoot->AddChild(m_pBone0); 
	m_pBone1 = new BoneObject(pMat, 15.f);
	m_pBone0->AddBone(m_pBone1);
	AddChild(pRoot);

}

void SoftwareSkinningScene_1::Update()
{
	const float rotationConstant = 45.f;
	m_BoneRotation += rotationConstant * GetSceneContext().pGameTime->GetElapsed() * m_RotationSign;
	MathHelper::Clamp(m_BoneRotation, rotationConstant, -rotationConstant);

	if (m_BoneRotation  <= -rotationConstant)
	{
		m_RotationSign = 1;
	}
	else if (m_BoneRotation >= rotationConstant)
	{
		m_RotationSign = -1;
	}

	m_pBone0->GetTransform()->Rotate(0.f, 0.f, m_BoneRotation, true);
	m_pBone1->GetTransform()->Rotate(0.f, 0.f, -m_BoneRotation * 2, true);	

}

void SoftwareSkinningScene_1::OnGUI()
{
}
