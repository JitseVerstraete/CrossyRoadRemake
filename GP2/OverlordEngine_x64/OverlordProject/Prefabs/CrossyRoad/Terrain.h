#pragma once



enum class TerrainType
{
	Grass,
	Road,
	River,
	Rail
};

class Terrain : public GameObject
{
public:
	Terrain(GameObject* trackedCharacter, int slicesAhead, int width);
	~Terrain() override;

	Terrain(const Terrain& other) = delete;
	Terrain(Terrain&& other) noexcept = delete;
	Terrain& operator=(const Terrain& other) = delete;
	Terrain& operator=(Terrain&& other) noexcept = delete;

	bool TilePassable(int x, int z);
	GameObject* GetSlice(int z);
	void Reset();
	GameObject* GetPreviousSlice() { return GetSlice(m_currentSliceNumber - 1); }

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
	const int m_maxBlankSlices = 5;
	int m_NrBlankGrassSlices{};


	TerrainType m_PrevTerrainType{};

	//weights
	std::map<TerrainType, int> m_TerrainWeights{};
	int m_TotalWeight;


	//private func 
	void SpawnNextSlice();
};

