#pragma once
#include "GameScene.h"

class TorqueTestScene final : public GameScene
{
public:
	TorqueTestScene() :GameScene(L"TorqueTestScene") {}
	~TorqueTestScene() override = default;
	TorqueTestScene(const TorqueTestScene& other) = delete;
	TorqueTestScene(TorqueTestScene&& other) noexcept = delete;
	TorqueTestScene& operator=(const TorqueTestScene& other) = delete;
	TorqueTestScene& operator=(TorqueTestScene&& other) noexcept = delete;

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
