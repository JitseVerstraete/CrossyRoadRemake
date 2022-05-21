#include "stdafx.h"
#include "CrossyCharacter.h"

#include <cmath>

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

	//rotation handling on pressing movement keys
	if (sceneContext.pInput->IsActionTriggered(PressForward))
	{
		//++m_PosZ;
		//jumped = true;
		SetTargetRot(180.f);
	}

	if (sceneContext.pInput->IsActionTriggered(PressBackward))
	{
		//if (m_PosZ > 0)
		//{
		//	//--m_PosZ;
		//	jumped = true;
		//}

		SetTargetRot(0.f);

	}
	if (sceneContext.pInput->IsActionTriggered(PressLeft))
	{
		//if (abs(m_PosX - 1) <= m_MaxWidth)
		//{
		//	--m_PosX;
		//	jumped = true;
		//}
		SetTargetRot(90.f);
	}
	if (sceneContext.pInput->IsActionTriggered(PressRight))
	{
		//if (abs(m_PosX + 1) <= m_MaxWidth)
		//{
		//	++m_PosX;
		//	jumped = true;
		//}
		SetTargetRot(270.f);
	}



	if (m_JumpTimer <= 0.f)
	{
		bool jumped = false;

		//handle movement (and rotation) on key release
		if (sceneContext.pInput->IsActionTriggered(ReleaseForward))
		{
			++m_PosZ;
			jumped = true;
			SetTargetRot(180.f);
		}

		if (sceneContext.pInput->IsActionTriggered(ReleaseBackward))
		{
			if (m_PosZ > 0)
			{
				--m_PosZ;
				jumped = true;
			}

			SetTargetRot(0.f);

		}
		if (sceneContext.pInput->IsActionTriggered(ReleaseLeft))
		{
			if (abs(m_PosX - 1) <= m_MaxWidth)
			{
				--m_PosX;
				jumped = true;
			}
			SetTargetRot(90.f);
		}
		if (sceneContext.pInput->IsActionTriggered(ReleaseRight))
		{
			if (abs(m_PosX + 1) <= m_MaxWidth)
			{
				++m_PosX;
				jumped = true;
			}
			SetTargetRot(270.f);
		}



		if (jumped)
		{
			m_JumpTimer = m_JumpTime;
		}
	}

	if (m_JumpTimer >= 0.f) m_JumpTimer -= sceneContext.pGameTime->GetElapsed();

	//lerp transform
	float jumpProgress = 1.f - (m_JumpTimer / m_JumpTime);
	MathHelper::Clamp(jumpProgress, 1.f, 0.f);
	float xPos = std::lerp(GetTransform()->GetPosition().x, static_cast<float>(m_PosX), jumpProgress);
	float zPos = std::lerp(GetTransform()->GetPosition().z, static_cast<float>(m_PosZ), jumpProgress);
	GetTransform()->Translate(xPos, 0.f, zPos);


	//lerp rotate
	m_CurrentRotY = std::lerp(m_CurrentRotY, m_TargetRotY, 0.2f);
	GetTransform()->Rotate(0.f, m_CurrentRotY, 0.f);

}

void CrossyCharacter::SetTargetRot(float rot)
{
	m_TargetRotY = rot;

	if (fmod(m_CurrentRotY, 360.f) < 0.f)
	{
		m_CurrentRotY = fmod(m_CurrentRotY, 360.f) + 360.f;
	}

	float delta = (m_TargetRotY - m_CurrentRotY);

	if (abs(delta) > 180.f)
	{
		if (delta < 0.f)
		{
			m_CurrentRotY -= 360.f;
		}
		else
		{
			m_CurrentRotY += 360.f;
		}
	}
}




