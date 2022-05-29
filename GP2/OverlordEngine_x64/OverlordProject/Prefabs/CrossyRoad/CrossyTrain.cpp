#include "stdafx.h"
#include "CrossyTrain.h"

#include "Materials/DiffuseMaterial.h"


CrossyTrain::CrossyTrain(float speed, int dir, float restX)
	: m_Speed{ speed }
	, m_Direction{ dir }
	, m_RestX{ restX }
{
}

CrossyTrain::~CrossyTrain()
{
	m_pCollider->GetTransform()->Translate(0.f, 10.f, 0.f);
	RemoveChild(m_pCollider, true);
}

void CrossyTrain::Initialize(const SceneContext&)
{
	//initialize "car" model & set scale & rotation
	auto model = AddComponent(new ModelComponent(L"Meshes/Train.ovm"));
	auto mat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	model->SetMaterial(mat);
	mat->SetDiffuseTexture(L"Textures/Train.png");
	GetTransform()->Scale(.09f);
	GetTransform()->Rotate(0.f, 90.f * m_Direction, 0.f, true);



	//collider
	PxMaterial* carPhysMat = PxGetPhysics().createMaterial(0.f, 0.f, 0.f);
	m_pCollider = AddChild(new GameObject());
	m_pCollider->GetTransform()->Translate(0.f, 2.f, 0.f);
	auto rigi = m_pCollider->AddComponent(new RigidBodyComponent(false));
	rigi->SetKinematic(true);
	rigi->AddCollider(PxBoxGeometry(1.5f, 0.4f, 0.4f), *carPhysMat, false);





}

void CrossyTrain::Update(const SceneContext& sceneContext)
{
	if (abs(GetTransform()->GetPosition().x) > 100.f) return;


	if (m_Driving)
	{
		float XMovement = m_Speed * sceneContext.pGameTime->GetElapsed() * m_Direction;
		GetTransform()->Translate(GetTransform()->GetPosition().x + XMovement, 0.f, 0.f);
	}
	else
	{
		GetTransform()->Translate(m_RestX, 0.f, 0.f);
	}

	//align collider with the car
	XMFLOAT3 pos = GetTransform()->GetWorldPosition();
	m_pCollider->GetTransform()->Translate(pos.x, pos.y, pos.z);

}
