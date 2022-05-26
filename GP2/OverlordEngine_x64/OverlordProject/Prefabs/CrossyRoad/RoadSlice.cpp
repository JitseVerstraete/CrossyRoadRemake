#include "stdafx.h"
#include "RoadSlice.h" 

#include "Materials/Shadow/DiffuseMaterial_Shadow.h"
#include "CrossyCar.h"

RoadSlice::RoadSlice(int width, CarDir dir, float carSpeed, float spawnInterval)
	: m_Width{ width }
	, m_CarDir{ static_cast<int>(dir) }
	, m_CarSpeed{ carSpeed }
	, m_SpawnInterval{ spawnInterval }
	, m_SpawnTimer{ 0.f }
{

	m_SpawnTimer = MathHelper::randF(0.f, spawnInterval);;
}

void RoadSlice::Initialize(const SceneContext&)
{

	ModelComponent* mc = AddComponent(new ModelComponent(L"Meshes/Slice.ovm", false));
	DiffuseMaterial_Shadow* mat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();

	mat->SetDiffuseTexture(L"Textures/Road.jpg");

	mc->SetMaterial(mat);
}

void RoadSlice::Update(const SceneContext& sceneContext)
{

	
	m_SpawnTimer += sceneContext.pGameTime->GetElapsed();


	//spawn car if the interval has passed
	if (m_SpawnTimer >= m_SpawnInterval)
	{
		m_SpawnTimer = 0.f;
		CrossyCar* pCar = new CrossyCar(m_CarSpeed, m_CarDir);
		m_pCars.emplace_back(pCar);
		float startX = m_Width * -2.f * m_CarDir;
		pCar->GetTransform()->Translate(startX, 0.f, 0.f);
		AddChild(pCar);
	}


	//despawn the cars that crossed the playfield
	auto it = m_pCars.begin();
	while (it != m_pCars.end())
	{
		if (((*it)->GetTransform()->GetPosition().x * m_CarDir) > (m_Width * 2.f))
		{
			//delte Car
			RemoveChild((*it), true);
			m_pCars.erase(std::remove(m_pCars.begin(), m_pCars.end(), *it));
			continue;
		}

		++it;
	}
}
