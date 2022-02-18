#pragma once


#include "GameScene.h"
class BouncingBallsScene final : public GameScene
{
public:
	BouncingBallsScene() :GameScene(L"BouncingBallsScene") {}
	~BouncingBallsScene() override = default;
	BouncingBallsScene(const BouncingBallsScene& other) = delete;
	BouncingBallsScene(BouncingBallsScene&& other) noexcept = delete;
	BouncingBallsScene& operator=(const BouncingBallsScene& other) = delete;
	BouncingBallsScene& operator=(BouncingBallsScene&& other) noexcept = delete;

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

	GameObject* m_pBall1{};
	GameObject* m_pBall2{};
	GameObject* m_pBall3{};


};

