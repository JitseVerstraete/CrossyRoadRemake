#pragma once


class RiverSlice final : public GameObject
{

public:
	RiverSlice(int nrLilys, int width);
	~RiverSlice() override = default;

	RiverSlice(const RiverSlice& other) = delete;
	RiverSlice(RiverSlice&& other) noexcept = delete;
	RiverSlice& operator=(const RiverSlice& other) = delete;
	RiverSlice& operator=(RiverSlice&& other) noexcept = delete;

	bool HasLily(int x);

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	int m_NrLilys;
	int m_MaxWidth;
	std::map<int, GameObject*> m_pLilyPads;
};
