#include "stdafx.h"
#include "CrossyCharacter.h"

#include "Materials/DiffuseMaterial.h"
#include "Materials/DiffuseMaterial_Skinned.h"

void CrossyCharacter::Initialize(const SceneContext&)
{
	//spawn the character, visuals... and attach a child with cameraComponent to it
	GameObject* pModelChild = AddChild(new GameObject());


	m_ModelComp = pModelChild->AddComponent(new ModelComponent(L"Meshes/Chicken2.ovm"));
	DiffuseMaterial_Skinned* mat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	mat->SetDiffuseTexture(L"Textures/Chicken2.png");
	m_ModelComp->SetMaterial(mat);

	pModelChild->GetTransform()->Scale(0.02f);
	m_ModelComp->GetAnimator()->SetAnimation(L"idle");
	m_ModelComp->GetAnimator()->Play();
}

void CrossyCharacter::Update(const SceneContext& sceneContext)
{
	if (m_JumpTimer <= 0.f)
	{
		bool jumped = false;

		//handle movement using registered keybinds
		if (sceneContext.pInput->IsActionTriggered(MoveForward))
		{
			++m_PosZ;
			m_TargetRot = { 0.f, 180.f, 0.f };
			jumped = true;
		}

		if (sceneContext.pInput->IsActionTriggered(MoveBackward))
		{
			if (m_PosZ > 0)
			{
				--m_PosZ;
				jumped = true;
			}

			m_TargetRot = { 0.f, 0.f, 0.f };

		}
		if (sceneContext.pInput->IsActionTriggered(MoveLeft))
		{
			if (abs(m_PosX - 1) <= m_MaxWidth)
			{
				--m_PosX;
				jumped = true;
			}
			m_TargetRot = { 0.f, 90.f, 0.f };
		}
		if (sceneContext.pInput->IsActionTriggered(MoveRight))
		{
			if (abs(m_PosX + 1) <= m_MaxWidth)
			{
				++m_PosX;
				jumped = true;
			}
			m_TargetRot = { 0.f, 270.f, 0.f };
		}


		if (jumped)
		{
			m_JumpTimer = m_JumpTime;
			m_ModelComp->GetAnimator()->SetAnimation(L"jump");
			m_ModelComp->GetAnimator()->SetAnimationSpeed(2.f);
			m_ModelComp->GetAnimator()->Play();
		}
	}

	if (m_JumpTimer > 0.f)
	{
		//go to the target position
		GetTransform()->Translate(static_cast<float>(m_PosX), 0.f, static_cast<float>(m_PosZ));
		GetTransform()->Rotate(m_TargetRot.x, m_TargetRot.y, m_TargetRot.z);

		m_JumpTimer -= sceneContext.pGameTime->GetElapsed();
		if (m_JumpTimer < 0.f)	m_ModelComp->GetAnimator()->SetAnimation(L"idle");
		

	}
	else
	{
		m_ModelComp->GetAnimator()->Play();
	}

}
