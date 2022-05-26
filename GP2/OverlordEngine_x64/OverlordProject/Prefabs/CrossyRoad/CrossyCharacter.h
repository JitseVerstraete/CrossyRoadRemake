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
	int GetScore() { return m_CurrentZ; };

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	int m_TargetPosX{};
	int m_TargetPosZ{};

	int m_CurrentX{};
	int m_CurrentZ{};

	int m_MaxWidth{};

	float m_CurrentRotY{};
	float m_TargetRotY{};

	const float m_JumpTime{ 0.1f };
	float m_JumpTimer{ 0.f };

	GameObject* m_ModelChild{};

	float m_SquishFactor{ 0 };
	float m_MaxSquishScale{ 0.6f };
	bool m_KeyPressed{ false };

	//not owner
	Terrain* m_pTerrain{};

	bool m_IsDead{ false };

	void SetTargetRot(float rot);

};

