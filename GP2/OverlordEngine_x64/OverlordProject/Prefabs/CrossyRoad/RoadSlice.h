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

private:
	int m_Width;
	int m_CarDir;
	float m_CarSpeed;
	float m_SpawnInterval;

	float m_SpawnTimer;

	static int m_LeftWeight;
	static int m_RightWeight;


	std::vector<CrossyCar*> m_pCars;
};

