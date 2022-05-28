#include "stdafx.h"
#include "Terrain.h"

#include <numeric>

Terrain::Terrain(GameObject* trackedCharacter, int slicesAhead, int width)
	:m_TrackedCharacter{ trackedCharacter }, m_SlicesAhead{ slicesAhead }, m_currentSliceNumber{ 0 }, m_MaxWidth{ width }, m_TotalWeight{}
{
	m_TerrainWeights.insert({ TerrainType::Grass, 5 });
	m_TerrainWeights.insert({ TerrainType::Road, 3 });
	m_TerrainWeights.insert({ TerrainType::River, 1 });

	for (auto pair : m_TerrainWeights)
	{
		m_TotalWeight += pair.second;
	}

	m_NrBlankGrassSlices = m_maxBlankSlices;
}

Terrain::~Terrain()
{

}

bool Terrain::TilePassable(int x, int z)
{
	GrassSlice* pGrass = dynamic_cast<GrassSlice*>(m_pSliceMap.find(z)->second);
	if (pGrass)
	{
		return pGrass->IsPassable(x);
	}

	return true;
}

GameObject* Terrain::GetSlice(int z)
{
	auto it = m_pSliceMap.find(z);
	if (it == m_pSliceMap.end())
	{
		return nullptr;
	}

	return it->second;
}

void Terrain::Reset()
{
	for (auto& pair : m_pSliceMap)
	{
		RemoveChild(pair.second, true);
	}
	m_pSliceMap.clear();


	m_currentSliceNumber = 0;
	m_NrBlankGrassSlices = m_maxBlankSlices;

	//first 5 slices before slice 0
	for (int i{ -5 }; i < 0; ++i)
	{
		GameObject* slice = nullptr;
		slice = AddChild(new GrassSlice(100, m_MaxWidth));
		m_pSliceMap.insert({ i, slice });
		slice->GetTransform()->Translate(0.f, 0.f, (float)i);
	}

}

void Terrain::Initialize(const SceneContext&)
{
	//inital terrain generation:a
	//first slice is alway grass with all trees
	//then a few grass slices guaranteed
	//after that, normal random generation starts:
	//	- only one river slice at a time
	//	- randomly selected road and grass slices


	//first 5 slices before slice 0
	for (int i{ -5 }; i < 0; ++i)
	{
		GameObject* slice = nullptr;
		slice = AddChild(new GrassSlice(100, m_MaxWidth));
		m_pSliceMap.insert({ i, slice });
		slice->GetTransform()->Translate(0.f, 0.f, (float)i);

	}

	srand((unsigned int)time(NULL));

	while (m_currentSliceNumber <= m_SlicesAhead)
	{
		SpawnNextSlice();
	}



}

void Terrain::Update(const SceneContext&)
{
	//update the terrain, spawn new slices when going forward, and despawn old slices when they go out of screen

	while (static_cast<int>(round(m_TrackedCharacter->GetTransform()->GetPosition().z)) + m_SlicesAhead >= m_currentSliceNumber)
	{
		SpawnNextSlice();
	}


}

void Terrain::SpawnNextSlice()
{

	GameObject* slice = nullptr;
	if (m_NrBlankGrassSlices > 0)
	{
		slice = new GrassSlice(0, m_MaxWidth);
		--m_NrBlankGrassSlices;

	}
	else
	{
		//generate random slice
		int totalWeight{ m_TotalWeight };

		//determine what slices to consider (no 2 rivers after each other)
		std::map<TerrainType, int> consideredSlices{};
		for (const auto& pair : m_TerrainWeights)
		{
			switch (pair.first)
			{
			case TerrainType::Grass:
				consideredSlices.insert(pair);
				break;
			case TerrainType::Road:
				consideredSlices.insert(pair);
				break;
			case TerrainType::River:
				if (m_PrevTerrainType == TerrainType::River)
				{
					totalWeight -= pair.second;
				}
				else
				{
					consideredSlices.insert(pair);
				}
				break;
			default:
				break;

			}
		}


		for (const auto& pair : consideredSlices)
		{

			if (rand() % totalWeight < pair.second)
			{
				switch (pair.first)
				{
				case TerrainType::Grass:
					slice = new GrassSlice(2, m_MaxWidth);
					m_PrevTerrainType = TerrainType::Grass;
					break;
				case TerrainType::Road:
					slice = new RoadSlice(m_MaxWidth, rand() % 2 == 0 ? CarDir::Left : CarDir::Right, 3.f, 2.f);
					m_PrevTerrainType = TerrainType::Road;
					break;
				case TerrainType::River:
					slice = new RiverSlice(3, m_MaxWidth);
					m_PrevTerrainType = TerrainType::River;
					break;
				default:
					break;
				}

				break;
			}
			else
			{
				totalWeight -= pair.second;
			}
		}
	}


	slice->GetTransform()->Translate(0.f, 0.f, (float)m_currentSliceNumber);
	AddChild(slice);

	m_pSliceMap.insert(std::pair<int, GameObject*>(m_currentSliceNumber, slice));
	++m_currentSliceNumber;


}
