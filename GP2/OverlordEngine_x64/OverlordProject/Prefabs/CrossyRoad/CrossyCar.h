#pragma once
class CrossyCar : public GameObject
{
public:
	CrossyCar(float speed, int dir);
	~CrossyCar() override;

	CrossyCar(const CrossyCar& other) = delete;
	CrossyCar(CrossyCar&& other) noexcept = delete;
	CrossyCar& operator=(const CrossyCar& other) = delete;
	CrossyCar& operator=(CrossyCar&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;


private:
	float m_Speed;
	int m_Direction;

	GameObject* m_pCarCollider{};
};
