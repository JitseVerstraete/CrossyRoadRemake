#pragma once


enum class TerrainType
{
	Grass,
	Road,
	River
};

class TerrainSlice final : public GameObject
{

public:
	TerrainSlice(TerrainType type);
	~TerrainSlice() override = default;

	TerrainSlice(const TerrainSlice& other) = delete;
	TerrainSlice(TerrainSlice&& other) noexcept = delete;
	TerrainSlice& operator=(const TerrainSlice& other) = delete;
	TerrainSlice& operator=(TerrainSlice&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:

	TerrainType m_Type;

};

