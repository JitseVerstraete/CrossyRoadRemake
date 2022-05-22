#include "stdafx.h"
#include "Terrain.h"

Terrain::Terrain(GameObject* trackedCharacter, int slicesAhead)
	:m_TrackedCharacter{ trackedCharacter }, m_SlicesAhead{ slicesAhead }, m_currentSliceNumber{ 0 }
{
}

void Terrain::Initialize(const SceneContext&)
{
	//inital terrain generation:
	//first slice is alway grass with all trees
	//then a few grass slices guaranteed
	//after that, normal random generation starts:
	//	- only one river slice at a time
	//	- randomly selected road and grass slices


	//first 5 slices before slice 0
	for (int i{ -5 }; i < 0; ++i)
	{
		GameObject* slice = nullptr;
		slice = AddChild(new GrassSlice());
		m_pSliceMap.insert({ i, slice });
		slice->GetTransform()->Translate(0.f, 0.f, (float)i);

	}


	srand((unsigned int)time(NULL));
	while (m_currentSliceNumber <= m_SlicesAhead)
	{
		SpawnRandomSlice();
	}



}

void Terrain::Update(const SceneContext&)
{
	//update the terrain, spawn new slices when going forward, and despawn old slices when they go out of screen

	if (static_cast<int>(round(m_TrackedCharacter->GetTransform()->GetPosition().z)) + m_SlicesAhead >= m_currentSliceNumber)
	{
		SpawnRandomSlice();
	}


}

void Terrain::SpawnRandomSlice()
{
	TerrainType sliceType = TerrainType(rand() % 3);
	GameObject* slice = nullptr;

	switch (sliceType)
	{
	case TerrainType::Grass:
		slice = AddChild(new GrassSlice());
		break;
	case TerrainType::Road:
		slice = AddChild(new RoadSlice());
		break;
	case TerrainType::River:
		slice = AddChild(new RiverSlice());
		break;
	default:
		break;
	}

	

	m_pSliceMap.insert(std::pair<int,GameObject*>(m_currentSliceNumber, slice));
	if (slice) slice->GetTransform()->Translate(0.f, 0.f, (float)m_currentSliceNumber);
	++m_currentSliceNumber;
}
