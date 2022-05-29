#include "stdafx.h"
#include "RoadSlice.h" 

#include "Materials/CrossyRoad/TerrainSliceMaterial.h"
#include "CrossyCar.h"

int RoadSlice::m_LeftWeight = 1;
int RoadSlice::m_RightWeight = 1;

RoadSlice::RoadSlice(int width, float minSpeed, float maxSpeed, float minDist, float maxDist)
	: m_Width{ width }
	, m_CarSpeed{}
	, m_SpawnInterval{}
	, m_SpawnTimer{ 0.f }
{
	//calculate car speed & interval variations
	m_CarSpeed = MathHelper::randF(minSpeed, maxSpeed);
	m_SpawnInterval = MathHelper::randF(minDist, maxDist) / m_CarSpeed;
	m_SpawnTimer = m_SpawnInterval;


	//calculate car direction
	if (rand() % (m_LeftWeight + m_RightWeight) < m_LeftWeight)
	{
		//direction is left (increace the chance for right direction for the next slice & reset the chance for the left direction)
		m_CarDir = static_cast<int>(CarDir::Left);
		m_RightWeight++;
		m_LeftWeight = 1;
	}
	else
	{
		//direction is right
		m_CarDir = static_cast<int>(CarDir::Right);
		m_LeftWeight++;
		m_RightWeight = 1;
	}
	
}

void RoadSlice::Initialize(const SceneContext&)
{
	ModelComponent* mc = AddComponent(new ModelComponent(L"Meshes/Slice.ovm", false));
	TerrainSliceMaterial* mat = MaterialManager::Get()->CreateMaterial<TerrainSliceMaterial>();

	float greyVal{ 0.4f };
	mat->SetColor(XMFLOAT4{ greyVal , greyVal, greyVal, 1.f });
	mat->SetWidth(m_Width + 0.5f);
	mc->SetMaterial(mat);

	XMFLOAT3 pos = GetTransform()->GetPosition();
	GetTransform()->Translate(pos.x, -0.08f, pos.z);
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
