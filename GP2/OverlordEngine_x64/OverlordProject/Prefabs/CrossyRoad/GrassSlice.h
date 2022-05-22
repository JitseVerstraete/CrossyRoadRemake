#pragma once




class GrassSlice final : public GameObject
{

public:
	GrassSlice(int obstacles, int maxWidth);
	~GrassSlice() override = default;

	GrassSlice(const GrassSlice& other) = delete;
	GrassSlice(GrassSlice&& other) noexcept = delete;
	GrassSlice& operator=(const GrassSlice& other) = delete;
	GrassSlice& operator=(GrassSlice&& other) noexcept = delete;

	bool IsPassable(int x);

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:

	//stores an obstacle &it's x value
	std::map<int, GameObject*> m_Obstacles{};
	int m_NrObstacles{};
	int m_MaxWidth{};

};

