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
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext & sceneContext) override;

private:

	std::map<int, GameObject*> m_pSliceMap;
	int m_SlicesAhead;
	int m_currentSliceNumber;
	int m_MaxWidth;

	GameObject* m_TrackedCharacter;

	void SpawnRandomSlice();

};

