#pragma once

enum InputIds
{
	MoveForward,
	MoveBackward,
	MoveLeft,
	MoveRight
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

	XMFLOAT3 m_TargetRot{};

	const float m_JumpTime{ 0.5f };
	float m_JumpTimer{ 0.f };

	ModelComponent* m_ModelComp{};

};

