#pragma once

class SpikyMaterial;
class SpikyScene : public GameScene
{
public:
	SpikyScene() :GameScene(L"SpikyScene") {}
	~SpikyScene() override = default;

	SpikyScene(const SpikyScene& other) = delete;
	SpikyScene(SpikyScene&& other) noexcept = delete;
	SpikyScene& operator=(const SpikyScene& other) = delete;
	SpikyScene& operator=(SpikyScene&& other) noexcept = delete;
private:

	void Initialize() override;
	void OnGUI() override;
	void Update() override;

	float m_Roatation{};
	GameObject* m_pBall{};
	SpikyMaterial* m_pMat{};
	float m_SpikeStrength{};
	float m_DiffuseColor[4]{};



};

