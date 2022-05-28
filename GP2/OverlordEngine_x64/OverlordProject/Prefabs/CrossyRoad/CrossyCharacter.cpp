#include "stdafx.h"
#include "CrossyCharacter.h"

#include <cmath>

#include "Materials/DiffuseMaterial.h"


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
	m_TargetPosX = m_TargetPosZ = m_PrevX = m_PrevZ = 0;
	m_SquishFactor = 0.f;
	m_KeyPressed = false;
}

void CrossyCharacter::Initialize(const SceneContext& sceneContext)
{
	//spawn the character, visuals... and attach a child with cameraComponent to it

	m_ModelChild = AddChild(new GameObject());

	auto pModComp = m_ModelChild->AddComponent(new ModelComponent(L"Meshes/Duck.ovm"));
	DiffuseMaterial* mat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	mat->SetDiffuseTexture(L"Textures/Duck.png");
	mat->SetVariable_Vector(L"gLightDirection", sceneContext.pLights->GetDirectionalLight().direction);

	pModComp->SetMaterial(mat);

	m_ModelChild->GetTransform()->Scale(0.35f);
	//pModComp->GetAnimator()->SetAnimation(L"idle");
	//pModComp->GetAnimator()->Play();


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
		pRiver = dynamic_cast<RiverSlice*>(m_pTerrain->GetSlice(m_PrevZ));
	}

	if (pRiver)
	{
		if (!pRiver->HasLily(m_PrevX))
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
		m_PrevX = m_TargetPosX;
		m_PrevZ = m_TargetPosZ;

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

	if (m_JumpTimer >= 0.f)
	{
		m_JumpTimer -= sceneContext.pGameTime->GetElapsed();
		MathHelper::Clamp(m_JumpTimer, m_JumpTime, 0.f);
	}
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
	if (jumpProgress < 0.5f)
	{
		//raise
		m_CurrentHeight = std::lerp(0.f, m_JumpHeight, jumpProgress * 2);
	}
	else
	{
		float targetHeight = 0.f;
		pRiver = dynamic_cast<RiverSlice*>(m_pTerrain->GetSlice(m_TargetPosZ));
		if (pRiver && !pRiver->HasLily(m_TargetPosX))
		{
			targetHeight = -0.4f;
		}
		m_CurrentHeight = std::lerp(m_JumpHeight, targetHeight, (jumpProgress - 0.5f) * 2);
	}
	MathHelper::Clamp(jumpProgress, 1.f, 0.f);
	float xPos = std::lerp(static_cast<float>(m_PrevX), static_cast<float>(m_TargetPosX), jumpProgress);
	float zPos = std::lerp(static_cast<float>(m_PrevZ), static_cast<float>(m_TargetPosZ), jumpProgress);
	GetTransform()->Translate(xPos, m_CurrentHeight, zPos);


	//lerp rotate
	m_RotTimer -= sceneContext.pGameTime->GetElapsed();
	float rotLerp{ 1 - (m_RotTimer / m_RotTime) };
	MathHelper::Clamp(rotLerp, 1.f, 0.f);

	float currentRotation = std::lerp(m_PrevRotY, m_TargetRotY, rotLerp);
	GetTransform()->Rotate(0.f, currentRotation, 0.f);

	//lerp squish
	GetTransform()->Scale(1.f, std::lerp(1.f, m_MaxSquishScale, m_SquishFactor), 1.f);

}

void CrossyCharacter::SetTargetRot(float rot)
{
	m_PrevRotY = m_TargetRotY;
	m_TargetRotY = rot;

	if (fmod(m_PrevRotY, 360.f) < 0.f)
	{
		m_PrevRotY = fmod(m_PrevRotY, 360.f) + 360.f;
	}

	float delta = (m_TargetRotY - m_PrevRotY);

	if (abs(delta) > 180.f)
	{
		if (delta < 0.f)
		{
			m_PrevRotY -= 360.f;
		}
		else
		{
			m_PrevRotY += 360.f;
		}
	}

	m_RotTimer = m_RotTime;
}




