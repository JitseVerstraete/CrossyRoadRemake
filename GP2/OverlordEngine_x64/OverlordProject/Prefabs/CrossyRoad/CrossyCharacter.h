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
	ReleaseRight
};

class CrossyCharacter : public GameObject
{
public:
	CrossyCharacter() {};
	~CrossyCharacter() override = default;

	CrossyCharacter(const CrossyCharacter& other) = delete;
	CrossyCharacter(CrossyCharacter&& other) noexcept = delete;
	CrossyCharacter& operator=(const CrossyCharacter& other) = delete;
	CrossyCharacter& operator=(CrossyCharacter&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	int m_PosX{};
	int m_PosZ{};

	int m_MaxWidth{4};

	float m_CurrentRotY{};
	float m_TargetRotY{};

	const float m_JumpTime{ 0.1f };
	float m_JumpTimer{ 0.f };

	ModelComponent* m_ModelComp{};

	float m_SquishFactor{0};
	float m_MaxSquishScale{ 0.6f };
	bool m_KeyPressed{ false };

	void SetTargetRot(float rot);

};

