#pragma once

#include "Prefabs/CrossyRoad/TerrainSlice.h"

class Terrain : public GameObject
{
public:
	Terrain(int amount);
	~Terrain() override = default;

	Terrain(const Terrain& other) = delete;
	Terrain(Terrain&& other) noexcept = delete;
	Terrain& operator=(const Terrain& other) = delete;
	Terrain& operator=(Terrain&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext & sceneContext) override;

private:

	std::vector<TerrainSlice*> m_pSlices;
	int m_InitialSlices;
	int m_currentSliceNumber;

};

