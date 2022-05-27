#pragma once

class CrossyCarMaterial : public Material<CrossyCarMaterial>
{
public:
	CrossyCarMaterial();
	~CrossyCarMaterial() override = default;

	CrossyCarMaterial(const CrossyCarMaterial& other) = delete;
	CrossyCarMaterial(CrossyCarMaterial&& other) noexcept = delete;
	CrossyCarMaterial& operator=(const CrossyCarMaterial& other) = delete;
	CrossyCarMaterial& operator=(CrossyCarMaterial&& other) noexcept = delete;

	void SetDiffuseTexture(const std::wstring& path);
	void SetChassisMap(const std::wstring& path);
	void SetCustomColor(const XMFLOAT4& color);

protected:
	void InitializeEffectVariables() override;
	void OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* pModel) const override;

private:
	TextureData* m_pDiffuseTexture{};
	TextureData* m_pChassisTexture{};
};

