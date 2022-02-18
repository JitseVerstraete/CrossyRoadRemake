#pragma once
#include "GameScene.h"

class ForceTestScene final : public GameScene
{
public:
	ForceTestScene() :GameScene(L"ForceTestScene") {}
	~ForceTestScene() override = default;
	ForceTestScene(const ForceTestScene& other) = delete;
	ForceTestScene(ForceTestScene&& other) noexcept = delete;
	ForceTestScene& operator=(const ForceTestScene& other) = delete;
	ForceTestScene& operator=(ForceTestScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

private:
	enum class InputIds
	{
		MoveRight,
		MoveLeft,
		MoveForward,
		MoveBack
	};

	GameObject* m_pCube{};


};
