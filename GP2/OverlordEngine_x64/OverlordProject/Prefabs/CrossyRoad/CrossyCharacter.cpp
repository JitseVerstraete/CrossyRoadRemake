#include "stdafx.h"
#include "CrossyCharacter.h"

#include <cmath>

#include "Materials/DiffuseMaterial.h"
#include "Materials/DiffuseMaterial_Skinned.h"

#include "Terrain.h"


void CrossyCharacter::SetTerrain(Terrain* pTer)
{
	m_pTerrain = pTer;
}

void CrossyCharacter::Resapwn()
{
	m_IsDead = false;
	GetTransform()->Translate(0.f, 0.f, 0.f);
	GetTransform()->Rotate(0.f, 0.f, 0.f);
	m_TargetPosX = m_TargetPosZ = m_CurrentX = m_CurrentZ = 0;
	m_SquishFactor = 0.f;
	m_KeyPressed = false;
}

void CrossyCharacter::Initialize(const SceneContext&)
{
	//spawn the character, visuals... and attach a child with cameraComponent to it

	m_ModelChild = AddChild(new GameObject());

	auto pModComp = m_ModelChild->AddComponent(new ModelComponent(L"Meshes/Chicken2.ovm"));
	DiffuseMaterial_Skinned* mat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	mat->SetDiffuseTexture(L"Textures/Chicken2.png");
	pModComp->SetMaterial(mat);

	m_ModelChild->GetTransform()->Scale(0.02f);
	pModComp->GetAnimator()->SetAnimation(L"idle");
	pModComp->GetAnimator()->Play();


	PxMaterial* carMat = PxGetPhysics().createMaterial(0.f, 0.f, 0.f);

	auto rigi = AddComponent(new RigidBodyComponent(false));
	rigi->SetKinematic(true);
	rigi->AddCollider(PxSphereGeometry(0.3f), *carMat, true);

	SetOnTriggerCallBack([=](GameObject* /*pTrigger*/, GameObject* /*pOther*/, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER)
			{
				m_IsDead = true;
			}
		});

}

void CrossyCharacter::Update(const SceneContext& sceneContext)
{

	RiverSlice* pRiver{};
	if (m_pTerrain)
	{
		pRiver = dynamic_cast<RiverSlice*>(m_pTerrain->GetSlice(m_CurrentZ));
	}

	if (pRiver)
	{
		if (!pRiver->HasLily(m_CurrentX))
		{
			m_IsDead = true;
		}
	}

	//rotation handling on pressing movement keys
	if (sceneContext.pInput->IsActionTriggered(PressForward))
	{
		SetTargetRot(180.f);
		m_KeyPressed = true;
	}
	else if (sceneContext.pInput->IsActionTriggered(PressBackward))
	{
		SetTargetRot(0.f);
		m_KeyPressed = true;
	}
	else if (sceneContext.pInput->IsActionTriggered(PressLeft))
	{
		SetTargetRot(90.f);
		m_KeyPressed = true;
	}
	else if (sceneContext.pInput->IsActionTriggered(PressRight))
	{
		SetTargetRot(270.f);
		m_KeyPressed = true;
	}



	if (m_JumpTimer <= 0.f)
	{
		m_CurrentX = m_TargetPosX;
		m_CurrentZ = m_TargetPosZ;

		bool jumped = false;

		//handle movement (and rotation) on key release
		if (sceneContext.pInput->IsActionTriggered(ReleaseForward))
		{
			m_KeyPressed = false;
			if (m_pTerrain->TilePassable(m_TargetPosX, m_TargetPosZ + 1))
			{
				++m_TargetPosZ;
				jumped = true;
			}
			SetTargetRot(180.f);
		}
		else if (sceneContext.pInput->IsActionTriggered(ReleaseBackward))
		{
			m_KeyPressed = false;
			if (m_pTerrain->TilePassable(m_TargetPosX, m_TargetPosZ - 1))
			{
				--m_TargetPosZ;
				jumped = true;
			}
			SetTargetRot(0.f);

		}
		else if (sceneContext.pInput->IsActionTriggered(ReleaseLeft))
		{
			m_KeyPressed = false;
			if (abs(m_TargetPosX - 1) <= m_MaxWidth && m_pTerrain->TilePassable(m_TargetPosX - 1, m_TargetPosZ))
			{
				--m_TargetPosX;
				jumped = true;
			}
			SetTargetRot(90.f);
		}
		else if (sceneContext.pInput->IsActionTriggered(ReleaseRight))
		{
			m_KeyPressed = false;
			if (abs(m_TargetPosX + 1) <= m_MaxWidth && m_pTerrain->TilePassable(m_TargetPosX + 1, m_TargetPosZ))
			{
				++m_TargetPosX;
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

	if (m_KeyPressed)
	{
		m_SquishFactor = std::lerp(m_SquishFactor, 1.f, 0.2f);
	}
	else
	{
		m_SquishFactor = std::lerp(m_SquishFactor, 0.f, 0.2f);
	}

	//lerp transform
	float jumpProgress = 1.f - (m_JumpTimer / m_JumpTime);
	MathHelper::Clamp(jumpProgress, 1.f, 0.f);
	float xPos = std::lerp(GetTransform()->GetPosition().x, static_cast<float>(m_TargetPosX), jumpProgress);
	float zPos = std::lerp(GetTransform()->GetPosition().z, static_cast<float>(m_TargetPosZ), jumpProgress);
	GetTransform()->Translate(xPos, 0.f, zPos);


	//lerp rotate
	m_CurrentRotY = std::lerp(m_CurrentRotY, m_TargetRotY, 0.2f);
	GetTransform()->Rotate(0.f, m_CurrentRotY, 0.f);

	//lerp squish
	GetTransform()->Scale(1.f, std::lerp(1.f, m_MaxSquishScale, m_SquishFactor), 1.f);

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




