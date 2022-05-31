#pragma once

class CrossyCar;

enum class CarDir 
{
	Left = -1,
	Right = 1
};

class RoadSlice final : public GameObject
{

public:
	RoadSlice(int width, float minSpeed, float maxSpeed, float minDist, float maxDist);
	~RoadSlice() override = default;

	RoadSlice(const RoadSlice& other) = delete;
	RoadSlice(RoadSlice&& other) noexcept = delete;
	RoadSlice& operator=(const RoadSlice& other) = delete;
	RoadSlice& operator=(RoadSlice&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;
	void Draw(const SceneContext& sceneContext) override;

private:
	int m_Width;
	int m_CarDir;
	float m_CarSpeed;
	float m_SpawnInterval;

	float m_SpawnTimer;

	static int m_LeftWeight;
	static int m_RightWeight;


	std::vector<CrossyCar*> m_pCars;

	//road stripes

	ID3DX11Effect* m_pStripesEffect{};
	ID3DX11EffectTechnique* m_pStripesTechnique{};
	ID3D11InputLayout* m_pStripesInputLayout{};
	ID3D11Buffer* m_pStripesVertexBuffer{};

	const float m_StripeLength{0.7f};
	const float m_StripeWidth{0.08f};
	const float m_StripesInterval{ 1.5f };

	std::vector<VertexStripe> m_Stripes;


};

