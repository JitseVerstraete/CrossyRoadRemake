#pragma once

enum InputIds
{
	PressForward,
	PressBackward,
	PressLeft,
	PressRight,
	ReleaseForward,
	ReleaseBackward,
	ReleaseLeft,
	ReleaseRight,
	Respawn
};

class Terrain;

class CrossyCharacter : public GameObject
{
public:
	CrossyCharacter(int width) : m_MaxWidth{ width } {};
	~CrossyCharacter() override = default;

	CrossyCharacter(const CrossyCharacter& other) = delete;
	CrossyCharacter(CrossyCharacter&& other) noexcept = delete;
	CrossyCharacter& operator=(const CrossyCharacter& other) = delete;
	CrossyCharacter& operator=(CrossyCharacter&& other) noexcept = delete;


	void SetTerrain(Terrain* pTer);
	bool IsDead() { return m_IsDead; }
	void Resapwn();
	int GetScore() { return m_PrevZ; };

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	int m_MaxWidth{};

	//movement vars
	int m_TargetPosX{};
	int m_TargetPosZ{};
	int m_PrevX{};
	int m_PrevZ{};
	const float m_JumpHeight{ 0.3f };
	float m_CurrentHeight;


	//rotation vars
	float m_PrevRotY{};
	float m_TargetRotY{};
	float m_RotTimer{};
	const float m_RotTime{0.08f};

	const float m_JumpTime{ 0.1f };
	float m_JumpTimer{ 0.f };

	GameObject* m_ModelChild{};

	float m_SquishFactor{ 0 };
	float m_MaxSquishScale{ 0.7f };
	bool m_KeyPressed{ false };

	//not owner
	Terrain* m_pTerrain{};

	bool m_IsDead{ false };

	//sound
	FMOD::Channel* m_pChannelJump{};
	FMOD::Sound* m_pJumpSound{};
	FMOD::Channel* m_pChannelSplash{};
	FMOD::Sound* m_pSplashSound{};
	FMOD::Channel* m_pChannelSplat{};
	FMOD::Sound* m_pSplatSound{};


	void SetTargetRot(float rot);

};

