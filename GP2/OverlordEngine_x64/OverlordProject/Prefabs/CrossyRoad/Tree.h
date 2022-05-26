
class Tree final : public GameObject
{
public:
	Tree() = default;
	~Tree() override = default;

	Tree(const Tree& other) = delete;
	Tree(Tree&& other) noexcept = delete;
	Tree& operator=(const Tree& other) = delete;
	Tree& operator=(Tree&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
private:
};