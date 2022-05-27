#include "stdafx.h"
#include "CrossyCar.h"

#include "Materials/CrossyRoad/CrossyCarMaterial.h"


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
	auto model = AddComponent(new ModelComponent(L"Meshes/Car.ovm"));
	auto mat = MaterialManager::Get()->CreateMaterial<CrossyCarMaterial>();
	model->SetMaterial(mat);
	mat->SetDiffuseTexture(L"Textures/Car.jpg");
	mat->SetChassisMap(L"Textures/CarChassis.jpg");
	mat->SetCustomColor(MathHelper::HSLtoRGB(MathHelper::randF(0.f, 1.f), 0.4f, 0.6f, 1.f));
	GetTransform()->Scale(0.02f);
	GetTransform()->Rotate(0.f, 90.f * -m_Direction, 0.f, true);

	//collider
	PxMaterial* carPhysMat = PxGetPhysics().createMaterial(0.f, 0.f, 0.f);
	m_pCarCollider = AddChild(new GameObject());
	m_pCarCollider->GetTransform()->Translate(0.f, 100.f, 0.f);
	auto rigi = m_pCarCollider->AddComponent(new RigidBodyComponent(false));
	rigi->SetKinematic(true);
	rigi->AddCollider(PxBoxGeometry(0.4f, 0.4f, 0.5f), *carPhysMat, false);
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
