#pragma once


#include "GameScene.h"
class FrictionTestScene final : public GameScene
{
public:
	FrictionTestScene() :GameScene(L"FrictionTestScene") {}
	~FrictionTestScene() override = default;
	FrictionTestScene(const FrictionTestScene& other) = delete;
	FrictionTestScene(FrictionTestScene&& other) noexcept = delete;
	FrictionTestScene& operator=(const FrictionTestScene& other) = delete;
	FrictionTestScene& operator=(FrictionTestScene&& other) noexcept = delete;

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
		MoveLeft
	};

	GameObject* m_pCube1{};
	GameObject* m_pCube2{};
	GameObject* m_pCube3{};

	GameObject* m_pFloor1{};
	GameObject* m_pFloor2{};
	GameObject* m_pFloor3{};

};

