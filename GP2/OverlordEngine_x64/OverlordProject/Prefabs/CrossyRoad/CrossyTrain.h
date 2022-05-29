#pragma once
class CrossyTrain : public GameObject
{
public:
	CrossyTrain(float speed, int dir, float restX);
	~CrossyTrain() override;

	CrossyTrain(const CrossyTrain& other) = delete;
	CrossyTrain(CrossyTrain&& other) noexcept = delete;
	CrossyTrain& operator=(const CrossyTrain& other) = delete;
	CrossyTrain& operator=(CrossyTrain&& other) noexcept = delete;

	void SetDriving(bool driving) { m_Driving = driving; }

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;


private:
	float m_Speed;
	int m_Direction;

	float m_RestX{};

	bool m_Driving{ false };

	GameObject* m_pCollider{};
};
