#pragma once
class TerrainSliceMaterial : public Material<TerrainSliceMaterial>
{
public:
	TerrainSliceMaterial();
	~TerrainSliceMaterial() override = default;

	TerrainSliceMaterial(const TerrainSliceMaterial& other) = delete;
	TerrainSliceMaterial(TerrainSliceMaterial&& other) noexcept = delete;
	TerrainSliceMaterial& operator=(const TerrainSliceMaterial& other) = delete;
	TerrainSliceMaterial& operator=(TerrainSliceMaterial&& other) noexcept = delete;

	void SetColor(const XMFLOAT4& color) const;
	void SetWidth(float width) const;

protected:
	void InitializeEffectVariables() override{}
	void OnUpdateModelVariables(const SceneContext&, const ModelComponent*) const override;

};

