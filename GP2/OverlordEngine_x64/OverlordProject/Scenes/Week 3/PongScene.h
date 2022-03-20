#pragma once

class PongScene : public GameScene
{
public:
	PongScene() :GameScene(L"PongScene") {}
	~PongScene() override = default;

	PongScene(const PongScene& other) = delete;
	PongScene(PongScene&& other) noexcept = delete;
	PongScene& operator=(const PongScene& other) = delete;
	PongScene& operator=(PongScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;



private:
	const float m_ballVelocity = 20.f;

	GameObject* m_pLeftPallet;
	GameObject* m_pRightPallet;
	GameObject* m_pBall;

	bool m_DoReset = false;

	void Reset();
	XMFLOAT3 CalulateBallVelocity(float velocity);

	
};

