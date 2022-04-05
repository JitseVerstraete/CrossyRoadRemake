#pragma once
#include "C:\DAE_Local\GraphicsProgramming2\GP2\OverlordEngine_x64\OverlordEngine\Misc\Material.h"
class DiffuseMaterial : public Material<DiffuseMaterial>
{
public:
	DiffuseMaterial();
	~DiffuseMaterial() override = default;

	DiffuseMaterial(const DiffuseMaterial& other) = delete;
	DiffuseMaterial(DiffuseMaterial&& other) noexcept = delete;
	DiffuseMaterial& operator=(const DiffuseMaterial& other) = delete;
	DiffuseMaterial& operator=(DiffuseMaterial&& other) noexcept = delete;

	void SetDiffuseTexture(const std::wstring& color) const;

protected:
	void InitializeEffectVariables() override;

private:
	TextureData* m_pDiffuseTexture{};
};

