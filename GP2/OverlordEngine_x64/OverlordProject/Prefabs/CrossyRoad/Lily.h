
class Lily final : public GameObject
{
public:
	Lily();
	~Lily() override = default;

	Lily(const Lily& other) = delete;
	Lily(Lily&& other) noexcept = delete;
	Lily& operator=(const Lily& other) = delete;
	Lily& operator=(Lily&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;
private:
	float m_Rotation{};
	const float m_RotationSpeed = 10.f;
	int m_RotationDirection{};

};