#pragma once


#include "Prefabs/CrossyRoad/GrassSlice.h"
#include "Prefabs/CrossyRoad/RoadSlice.h"
#include "Prefabs/CrossyRoad/RiverSlice.h"


enum class TerrainType
{
	Grass,
	Road,
	River
};

class Terrain : public GameObject
{
public:
	Terrain(GameObject* trackedCharacter, int slicesAhead, int width);
	~Terrain() override = default;

	Terrain(const Terrain& other) = delete;
	Terrain(Terrain&& other) noexcept = delete;
	Terrain& operator=(const Terrain& other) = delete;
	Terrain& operator=(Terrain&& other) noexcept = delete;

	bool TilePassable(int x, int z);

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:

	GameObject* m_TrackedCharacter;

	std::map<int, GameObject*> m_pSliceMap;
	int m_MaxWidth;

	//terrain generation
	int m_currentSliceNumber;
	int m_SlicesAhead;
	int m_NrBlankGrassSlices{ 5 };
	void SpawnNextSlice();
	TerrainType m_PrevTerrainType{};

	//weights
	std::map<TerrainType, int> m_TerrainWeights{};
	int m_TotalWeight;
};

