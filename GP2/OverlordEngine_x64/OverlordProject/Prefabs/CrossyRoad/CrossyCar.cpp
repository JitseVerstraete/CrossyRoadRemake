#include "stdafx.h"
#include "CrossyCar.h"

#include "Materials/ColorMaterial.h"

CrossyCar::CrossyCar(float speed, int dir)
	: m_Speed{ speed }
	, m_Direction{ dir }
{
}

CrossyCar::~CrossyCar()
{
	m_pCarCollider->GetTransform()->Translate(0.f, 10.f, 0.f);
	RemoveChild(m_pCarCollider, true);
}

void CrossyCar::Initialize(const SceneContext&)
{
	//initialize "car" model & set scale & rotation
	auto model = AddComponent(new ModelComponent(L"Meshes/Chicken.ovm"));
	auto mat = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	model->SetMaterial(mat);
	mat->SetColor(XMFLOAT4{ Colors::Magenta });
	GetTransform()->Scale(0.05f);
	GetTransform()->Rotate(0.f, 90.f * m_Direction, 0.f, true);

	PxMaterial* carMat = PxGetPhysics().createMaterial(0.f, 0.f, 0.f);
	m_pCarCollider = AddChild(new GameObject());
	m_pCarCollider->GetTransform()->Translate(0.f, 100.f, 0.f);
	auto rigi = m_pCarCollider->AddComponent(new RigidBodyComponent(false));
	rigi->SetKinematic(true);
	rigi->AddCollider(PxBoxGeometry(0.4f, 0.4f, 0.4f), *carMat, false);
}

void CrossyCar::Update(const SceneContext& sceneContext)
{
	//update position
	float XMovement = m_Speed * sceneContext.pGameTime->GetElapsed() * m_Direction;
	GetTransform()->Translate(GetTransform()->GetPosition().x + XMovement, 0.f, 0.f);

	//align collider with the car
	XMFLOAT3 pos = GetTransform()->GetWorldPosition();
	m_pCarCollider->GetTransform()->Translate(pos.x, pos.y, pos.z);
}
