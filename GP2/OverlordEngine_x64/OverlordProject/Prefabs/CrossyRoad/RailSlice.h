#pragma once

class CrossyTrain;
class CrossyCharacter;
class DiffuseMaterial_Shadow;

enum class TrainDir
{
	Left = -1,
	Right = 1
};

class RailSlice final : public GameObject
{

public:
	RailSlice(int width, float speed, float minSpawnTime, float maxSpawnTime, CrossyCharacter* trackeCharacter);
	~RailSlice() override = default;

	RailSlice(const RailSlice& other) = delete;
	RailSlice(RailSlice&& other) noexcept = delete;
	RailSlice& operator=(const RailSlice& other) = delete;
	RailSlice& operator=(RailSlice&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	int m_Width;
	int m_TrainDir;
	float m_TrainSpeed;


	float m_SpawnTime;

	float m_SpawnTimer;

	float m_RestX{};

	const int m_NrCarriages = 6;
	const float m_CarriageLength = 3.4f;
	std::vector<CrossyTrain*> m_pTrains;
	CrossyCharacter* m_pTrackedCharacter{};

	//warning light
	DiffuseMaterial_Shadow* m_SignMaterial{};
	bool m_WarningSet{ false };
	bool m_LightOn{ false };
	float m_LightTimer{ 2.f };
	FMOD::Sound* m_pWarningSound{};
	FMOD::Sound* m_pTrainSound{};
	FMOD::Channel* m_pWarningChannel{};
	FMOD::Channel* m_pTootChannel{};
	bool m_TootPlayed = false;


};

