#pragma once

class SpikyMaterial : public Material<SpikyMaterial>
{
public:
	SpikyMaterial();
	~SpikyMaterial() override = default;

	SpikyMaterial(const SpikyMaterial& other) = delete;
	SpikyMaterial(SpikyMaterial&& other) noexcept = delete;
	SpikyMaterial& operator=(const SpikyMaterial& other) = delete;
	SpikyMaterial& operator=(SpikyMaterial&& other) noexcept = delete;

	void SetDiffuseColor(const XMFLOAT4& color);
	void SetSpikeLength(float length);


protected:
	void InitializeEffectVariables() override;

private:



};

