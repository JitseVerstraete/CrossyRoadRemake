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
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext & sceneContext) override;

private:
	int m_PosX{};
	int m_PosZ{};

};

